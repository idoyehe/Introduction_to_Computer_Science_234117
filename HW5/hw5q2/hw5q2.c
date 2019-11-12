/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
void getScores(int*,int);
bool allTeamed(bool[],int);
void unTeamed(bool[],int );
void coverPair(int[], int);
void pairUp(int[],bool[],int,int*,int,int,int*);
int calcScore(int [],int ,int ,int);
void pariUp (int[],bool[],int,int*,int,int,int*);

int main()
/*Length: 10 Rows*/
{
    int size=0;
    printf("How many workers are there?\n");
    scanf("%d",&size);
    int *pref=(int*)malloc(size*size*sizeof(int));
    if(pref!=NULL){
        //malloc succeed to allocate memory
        printf("What are their preferences?\n");
        getScores(pref,size);
        coverPair(pref,size);
    }
    free(pref);
  return 0;
}
void getScores(int pref[],int size)
/*Getting the matrix and the number of wrokers and put the date in the matrix
Length: 6 Rows*/
{
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++){
            if(i==j){
                pref[size*i+j]=0;//put zeros on the prime diagonal
                continue;
            }
            scanf("%d",&pref[size*i+j]);
        }
}
void coverPair(int pref[], int size)
/*Cover fo the recursive funcation summon it with initialized parametrs
Length: 10 Rows*/
{
    bool* teamed=(bool*)malloc(size*sizeof(bool));
    if(teamed!=NULL){
        //malloc succeed to allocate memory
        unTeamed(teamed,size);
        int current=0, score=0,howmany=0,max=0;
        int *m=&max;
        int*h=&howmany;
        pairUp(pref,teamed,size,m,current,score,h);
        printf("There are %d optimal pairings,\n",howmany);
        printf("with a total score of: %d\n",max);
    }
    free(teamed);
}
void pairUp(int pref[], bool teamed[], int size,int* max,int current, int score, int* howmany)
/*Check All the possibile pairs: "searching in the tree"
Length: 22 Rows*/
{
    if (allTeamed(teamed,size)){//All the pairs are teamed
        if(score>*max){//New max
            *max=score;
            *howmany=1;
        } else if(score==*max)
                    (*howmany)++;//Count one more opitimal way
        return;
    }
    if (teamed[current]){//already paired
        current++;//step forward
        pairUp(pref, teamed, size,max,current,score,howmany);
        return;
    }
    for(int i=0;i<size;i++)
    {
        if(teamed[i] || (i==current))continue;
        teamed[i] = true;//signed as paird
        teamed[current] = true;//signed as paird
        score += calcScore(pref,size,current,i);//summing the scores
        current++;//step forward
        pairUp(pref, teamed, size,max,current,score,howmany);
        current--;//step backward
        score -= calcScore(pref,size,current,i);//removing the score
        teamed[current] = false;//unpaird
        teamed[i] = false;//unpaird
    }
}
int calcScore(int pref[],int size,int current,int j)
/*Calculating the score between two workers
Length: 1 Row*/
{
    return pref[size*current+j]+pref[size*j+current];
}
void unTeamed(bool teamed[],int size)
/*put false in the teamed arrey
Length: 1 Row*/
{
    for(int i=0;i<size;i++)teamed[i]=false;
}
bool allTeamed(bool teamed[],int size)
{
    for(int i=0;i<size;i++)
        if(!teamed[i])
            return false;
    return true;
}
















