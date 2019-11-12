#include <stdio.h>
#include <stdbool.h>

/*========================================================================
  Constants and definitions:
=========================================================================*/
#define N 10 //Size of Boards
#define N_BS 4 //number of battleships
#define DIM 2
#define B_SHIPS {3,3,4,5}//Sizes of Battleships
#define D_BS 5//data per battleships
#define D_BITS N_BS*D_BS //Size of data of all battleships
/*------------------------------------------------------------------------
Battelship Game. User against the computer
 ------------------------------------------------------------------------*/
void printWelcome(void);
int seedAsking(void);
void srand_range (unsigned int);
int rand_range (int, int);
void cleanBorads(char [][N],char [][N],char [][N],char [][N]);
int levelDiff(void);
void printBoard(char [N][N]);
int locatingUserships(char [N][N],int[D_BITS]);
int locatingONEShip(char [N][N],int,int[D_BS]);
int canbeLocated(char [N][N],int,int[D_BS]);
int gettingIndexes(int [DIM]);
int gettingDirXY(int [DIM]);
void printBship(char[N][N],int,int,int,int,int);
int clearPath(char [N][N],int ,int ,int , int , int );
void transferData(int[DIM],int[DIM],int[D_BS]);
void transferData2(int[D_BITS],int[D_BS],int);
void locatingCompShips(char [N][N],int[D_BITS]);
void locatingONECompShip(char[N][N],int,int[D_BS]);
void copyboard(char[N][N],char[N][N]);
int runningGame(char[][N],char[][N],char[][N],char[][N],int,int[D_BITS],int[D_BITS]);
int userTurn(char[N][N],char[N][N]);
void oneCompTurn(char [N][N]);
void doTheAttack (char [N][N],char [N][N],int[DIM]);
int drownedBattleship(char [N][N],int [D_BITS]);
void drownedComp(char [N][N],int[D_BITS]);
void drownedUser(char [N][N],int[D_BITS]);
void printingStatus (char[N][N],char[N][N]);
int winner (char[N][N],char[N][N],char[N][N],char[N][N]);
bool compereBoards(char[N][N],char[N][N]);

int main()
{
    //Length: 13 Rows
    printWelcome();
    if(seedAsking()==-1)
        return 0;
    char userB [N][N],userF [N][N], compB [N][N],compF[N][N];
    int dataC[D_BITS]= {0}, dataU[D_BITS]= {0};
    cleanBorads(userB,userF,compB,compF);
    int level=levelDiff();
    if(level==-1||locatingUserships(userB,dataU)==-1)
        return 0;
    locatingCompShips(compB,dataC);
    copyboard(userB,compF);
    runningGame(userB,userF,compB,compF,level,dataU,dataC);
    return 0;
}
void printWelcome(void)
/*printing welcome message
Length: 1 Row*/
{
    printf("Welcome to Battleship!\n");
}
void cleanBorads(char b1[][N],char b2[][N],char b3[][N] ,char b4[][N])
/*Clean the board from trash and put spaces
Length: 6 Rows*/
{
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
        {
            b1[i][j]=' ';
            b2[i][j]=' ';
            b3[i][j]=' ';
            b4[i][j]=' ';
        }
}
int seedAsking(void)
/*Asking the user to enter a seed and put it in "strand range"
Length: 7 Rows*/
{
    printf("Please enter seed:\n");
    unsigned int seed;
    if(!scanf("%u",&seed))
    {
        printf("Error: Invalid input!\n");
        return -1;
    }
    srand_range(seed);
    return 1;
}
void srand_range (unsigned int seed)
/*Length: 2 Rows*/
{

    for (int i = 0; (unsigned int)i < seed; i++)
    {
        rand_range(i,i+1);
    }
}
int rand_range (int low, int high)
/* RAND_MAX assumed to be 32767
Length: 3 Rows*/
{
    static unsigned int next = 1;
    next = next * 1103515245 + 12345;
    return ((unsigned int)(next/65536) % 32768) % (high - low + 1) + low;
}

int levelDiff(void)
/*Asking the user to enter a level of difficulty
as well check if the user enter a positive number
Length: 6 Rows*/
{
    int l;
    printf("Please enter level:\n");
    if(!scanf("%d",&l)||l<0) //in case of invalid input
    {
        printf("Error: Invalid input!\n");
        return -1;
    }
    return l;
}
void printBoard(char b [N][N])
/*Printing the boardas as expected
Length: 12 Rows*/
{
    for(int i=N-1; i>=0; i--)
    {
        printf("%d | ",i);
        for(int j=0; j<N; j++)
            printf("%c ",b[i][j]);
        printf("\n");
    }
    printf("    ");
    for(int i=0; i<N; i++)
        printf("- ");
    printf("\n    ");
    for(int i=0; i<N; i++)
        printf("%d ",i);
    printf("\n");
}
int locatingUserships(char b[N][N],int data [D_BITS])
/*Locating all the battleships of the user by using other functions
As well saving the paramerts the user entered into an arrey
Length: 9 Rows*/
{
    int shipsSizes[N_BS]=B_SHIPS; //Getting the sizes of the battleships
    int dataXY[D_BS]= {0};
    for(int i=0; i<N_BS; i++)
    {
        printBoard(b);//Print the board before locating
        int shipSize=shipsSizes[i];
        if(locatingONEShip(b,shipSize,dataXY)==-1)
        {
            return -1;//Invalid parameters
        }
        data[i*D_BS]=shipSize;//put the Ships' sizes in index that %D_BS=0
        transferData2(data,dataXY,i*D_BS);
//transfer the data of one ship to an arrey that include the data of all
    }

    printf("All battleships have been located successfully!\n");
    return 1;
}
int locatingONEShip(char b[N][N],int shipSize,int xy[D_BS])
/*Locating one battleship with spacific size by using other functions
As well saving the paramerts the user entered to "xy" arrey
Length: 8 Rows*/
{
    printf("Enter location for Battleship of size %d:\n",shipSize);
    int flag;
    do
    {
        flag=canbeLocated(b,shipSize,xy); //Use the funcations to locate it
        if(flag==1) //The battleship has been located
            return 1;
    }
    while(flag==0);//The parameters are not good and it will ask for new
    return -1; //Invalid Parameters
}
int canbeLocated(char b[N][N],int shipSize,int dataXY[D_BS])
/*Check with the other funcations if the battleship
can be located and located it if it is possible
Length: 13 Rows*/
{
    int dirXY[DIM]= {0},indexes[DIM]= {0};
    //Two arreys os size 2 in order to save the parameters
    int f1=gettingIndexes(indexes), f2=gettingDirXY(dirXY);
    if (f1==-1||f2==-1)  //In case the parameters are invalid
    {
        printf("Error: Invalid input!\n");
        return-1;
    }
    int f3=clearPath(b,shipSize,indexes[0],indexes[1],dirXY[0],dirXY[1]);
    //Checking the path of the battleship
    if (!f1||!f2||!f3)
    {
        printf("Error: Incorrect parameters! Please enter location");
        printf(" for the Battleship size %d again:\n",shipSize);
        return 0; //the parameters generates bad path
    }//At this point the battleship can be located
    transferData(indexes,dirXY,dataXY);
    //transfer the data from the small two arreys to a bigger one
    printBship(b,shipSize,indexes[0],indexes[1],dirXY[0],dirXY[1]);
    return 1;
}
int gettingIndexes(int xy[DIM])
/*Asking the user to enter a row index and a colmun index
And check if it is good parameters by value and syntactic
Length: 6 Rows*/
{
    //xy[0] is index of x dir_X and xy[1] is index of y
    if(scanf("%d,%d",&xy[0],&xy[1])==2)
    //In case the input is  two round numbers
    {
        for(int i=0; i<DIM; i++)
        {
            if(0>xy[i]||xy[i]>N)
            //Check the if the parameters are good by value
                return 0;
        }
        return 1;//the input is good
    }
    return -1;//invalid parameters
}
int gettingDirXY(int dirXY[DIM])
/*Asking the user to enter a dircations indexes
And check if it is good parameters by value and syntactic
Length: 8 Rows*/
{
    //dirXY[0] is dir_X and dirXY[1] is dir_Y
    if(scanf("%d,%d",&dirXY[0],&dirXY[1])==2)
    //In case the input is  two round numbers
    {
        for(int i=0; i<DIM; i++)
        {
            if(dirXY[i]<-1||dirXY[i]>1)
            //In case the input is not between -1 to 1
                return 0;
        }
        if(dirXY[0]==0&&dirXY[1]==0)
            return 0; //In case both dirations are 0
        return 1; //The dircations are good
    }
    return -1;//invalid parameters
}
int clearPath(char b[N][N],int shipSize,int m,int n, int x, int y)
/*Check if the path of the dircation is not out of the board
or other battleship in the path
Length: 6 Rows*/
{
    for(int c=0; c<shipSize; c++)
    {
        int i=n+(y*c);
        int j=m+(x*c);
        if(i<0||i>N-1||j<0||j>N-1||b[i][j]=='*')
        //In case the battleship is out of the board or the one in the path
            return 0;
    }
    return 1;
}
void locatingCompShips(char b[N][N],int data[D_BITS])
/*Use the funcation of locatingONECompShip in order to locate
all the computer's battleships
Length: 7 Rows*/
{
    int shipsSizes[N_BS]=B_SHIPS;
    int dataXY[D_BS]= {0};
    for(int i=0; i<N_BS; i++)
    {
        int shipSize=shipsSizes[i];
        data[i*D_BS]=shipSize;
        //put the battleship's size in the index%D_BS==0 indexes.
        locatingONECompShip(b,shipSize,dataXY);
        transferData2(data,dataXY,i*D_BS);
        //i*D_BS start new series of data to new battleship
    }
}
void locatingONECompShip(char b[N][N],int shipSize,int xy[D_BS])
/*Computer is choosing random locations
in order to to locate the battleship
Length: 12 Rows*/
{
    do
    {
        xy[0]=shipSize;
        xy[1]=rand_range(0,N-1);//saving index X
        xy[2]=rand_range(0,N-1);//saving index Y
        xy[3]=rand_range(-1,1);//saving dircation X
        xy[4]=rand_range(-1,1);//saving dircation Y
    }
    //Check if the parametrs are good and if it is create clear path
    while((xy[3]==0&&xy[4]==0)||
           !clearPath(b,shipSize,xy[1],xy[2],xy[3],xy[4]));
    //At this point the battleship can be located
    printBship(b,xy[0],xy[1],xy[2],xy[3],xy[4]);
}
void transferData(int location[DIM],int dirXY[DIM],int data[D_BS])
/*Transfer two arreyes of size 2 to arrey size 4
In order to save the data of each battleship
Length 4 Rows*/
{
    data[1]=location[0];
    data[2]=location[1];
    data[3]=dirXY[0];
    data[4]=dirXY[1];
}
void transferData2(int data [D_BITS],int dataXY[D_BS],int start)
/*Tranfer the data of the indexes of the battleships to abigger arrey
that index%D_BS==0 will start new battleship data
Length: 9 Rows*/
{
    for(int i=1; i<D_BS; i++)
    {
        if((i+start)%D_BS==1)
            data[(i+start)]=dataXY[1];
        if((i+start)%D_BS==2)
            data[(i+start)]=dataXY[2];
        if((i+start)%D_BS==3)
            data[(i+start)]=dataXY[3];
        if((i+start)%D_BS==4)
            data[(i+start)]=dataXY[4];
    }
}
void printBship(char b[N][N],int size,int indexX,int indexY,int dirX,int dirY)
/*Get good parameters and print the battleship on the board
Length: 4 Rows*/
{
    for(int c=0; c<size; c++)
    {
        int i=indexY+(dirY*c);
        int j=indexX+(dirX*c);
        b[i][j]='*';
    }
}
void copyboard(char b1[N][N],char b2 [N][N])
/*copy the board of the player to the Computer following Board
Length: 3 Rows*/
{
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            b2[i][j]=b1[i][j];

}
int runningGame(char b1[][N],char b2[][N],char b3[][N],char b4[][N],int l,int d1[D_BITS],int d2[D_BITS])
/*Using other funcations and run the attackes by the order
As well checking after each turn the status of the game
Length: 13 Rows*/
{
    int flag;
    do
    {
        printingStatus(b2,b4);//printing status of the game after the turns
        if(userTurn(b2,b3)==-1)//in case the user enter invalid parameters
            return -1;
        drownedComp(b2,d2);
        flag=winner(b3,b2,b1,b4);
        //Check if the user win after his turn if not let the computer play
        for (int i=0; !flag&&i<l; i++)
        {
            oneCompTurn(b4);
            drownedUser(b4,d1);
            flag=winner(b3,b2,b1,b4);
            //Checking if the computer win after his turn
        }
    }
    while(!flag);//if on of them win the game will stop
    return 1;
}
void printingStatus (char b1[N][N],char b2[N][N])
/*printing the status of the boards
Length: 4 Rows*/
{
    printf("Your following table:\n");
    printBoard(b1);
    printf("The computer's following table:\n");
    printBoard(b2);
}
int userTurn(char b1[N][N],char b2[N][N])
/*Asking the user to enter coordinates to attack in the computer board
Length: 13 Rows*/
{
    printf("It's your turn!\nEnter coordinates for attack:\n");
    int flag,xy[2]= {0}; // XY[0] its index X and XY[1] its index Y
    do
    {
        flag=gettingIndexes(xy);//asking for indexes
        if(flag==-1) //in case of in valid parameters
        {
            printf("Error: Invalid input!\n");
            return-1;
        }
        if(flag==0||b1[xy[1]][xy[0]]!=' ')//In case of incorrect parameters
        {
            printf("Error: Incorrect parameters! ");
            printf("Please enter coordinates for attack again:\n");
        }
    }
    while(flag==0||b1[xy[1]][xy[0]]!=' ');
    doTheAttack(b1,b2,xy);//call the function in order to print the attack
    return 1;
}
void oneCompTurn(char b[N][N])
/*The computer choose randoms coordinates to attack in the user board
Length: 6 Rows*/
{
    int xy[2]; //XY[0] its index X and XY[1] its index Y
    do
    {
        xy[0]=rand_range(0,N-1);//saving index X
        xy[1]=rand_range(0,N-1);//saving index Y
    }
    while (b[xy[1]][xy[0]]=='X'||b[xy[1]][xy[0]]=='V');
    //in case the computer choose a spot that already been attacked
    doTheAttack(b,b,xy);
}
void doTheAttack (char b1[N][N],char b2[N][N],int xy[DIM])
/*Get currect attack parameters and print the attack on the board
Length: 3 Rows*/
{
    //XY[0] its index X and XY[1] its index Y
    if(b2[xy[1]][xy[0]]=='*') //if the attack is on a battleship
        b1[xy[1]][xy[0]]='V';
    else
        b1[xy[1]][xy[0]]='X';//if the attack is not on a battleship
}
void drownedComp(char b[N][N],int data[D_BITS])
/*Checking if one of the computer battleship has been drowned
Length: 7 Rows*/
{
    int shipSize;
    do
    {
        shipSize=drownedBattleship(b,data);
        if(shipSize!=-1) //if there one of bettaleship that drowned
        {
            printf("The computer's battleship of size");
            printf(" %d has been drowned!\n",shipSize);
        }
    }
    while(shipSize!=-1);
}
void drownedUser(char b[N][N],int data[D_BITS])
/*Checking if one of the user battleship has been drowned
Length: 7 Rows*/
{
    int shipSize;
    do
    {
        shipSize=drownedBattleship(b,data);
        if(shipSize!=-1) //if there one of bettaleship that drowned
        {
            printf("Your battleship of size");
            printf(" %d has been drowned!\n",shipSize);
        }
    }
    while(shipSize!=-1);
}
int drownedBattleship(char b[N][N],int dataXY [D_BITS])
/*Check if there is a sequence  of 'V' that indiciate of drowned battleship
Length: 13 Rows*/
{
    for(int s=0; s<D_BITS; s+=D_BS) //check the indexes that index%D_BS==0
    {
        if(dataXY[s]!=-1) //if the battleship hasn't been attacked
        {
            int c=0;
            for(c=0; c<dataXY[s]; c++) // dataXY[s]=the ship size
            {
                int i=dataXY[s+2]+(dataXY[s+4]*c);
                // dataXY[s+2]=the Y location, dataXY[s+4]=the Y dircation
                int j=dataXY[s+1]+(dataXY[s+3]*c);
                // dataXY[s+1]=the x location, dataXY[s+3]=the x dircation
                if(b[i][j]=='*'||b[i][j]==' ')
                    break;//no sequence  of 'V'
            }
            if(c==dataXY[s]) //there is a sequence  of 'V'
            {
                int shipSize=dataXY[s];
                dataXY[s]=-1;//sign that the battleship has been dronwed
                return shipSize;
            }
        }
    }
    return -1;//non battleship has been drowned
}
int winner (char b1[N][N],char b2[N][N],char b3[N][N],char b4[N][N])
/*Return 1 if the user is the winner or -1 if the computer is the winner
and 0 if there is no winner yet
Length: 7 Rows*/
{
    if(compereBoards(b1,b2))
    {
        printf("Congrats! You are the winner!");
        return 1;
    }
    if(compereBoards(b3,b4))
    {
        printf("Game over! You lost...");
        return -1;
    }
    return 0;
}
bool compereBoards(char b1[N][N],char b2[N][N])
/*Getting two table and check that where is '*'
in the first there is 'V' in the second
Length: 5 Rows*/
{
    for (int i=0; i<N; i++)
        for(int j=0; j<N; j++)
        {
            if (b1[i][j]=='*'&&b2[i][j]!='V')
                return false;
        }
    return true;
}
