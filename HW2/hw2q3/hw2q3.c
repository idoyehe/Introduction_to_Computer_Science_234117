/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>

/*=========================================================================
  Constants and definitions:
==========================================================================*/

#define N 4
#define SQRT_N 2

/*-------------------------------------------------------------------------
Sudoku of 4X4
This Code was bulit in order to check solution of Sudoku size 4X4
 -------------------------------------------------------------------------*/
bool checkRow (int table[N][N], int row, int num)
/*checking that a number appears one time in a row*/
{
    int count=0;
    for(int j=0;j<N;j++)
       count+=(table[row][j]==num);

    if (count==1)
        return true;
    return false;
}

bool checkColumn (int table[N][N], int column, int num)
/*checking that a number appears one time in a column*/
{
    int count=0;
    for(int i=0;i<N;i++)
       count+=(table[i][column]==num);

    if (count==1)
        return true;
    return false;
}
bool checkCube (int table[N][N], int start, int num)
/*checking that a number appears one time in a cube on the prime diagonal in the table */
{
    int count=0;
    for(int i=0;i<SQRT_N;i++)
        for(int j=0;j<SQRT_N;j++)
            count+=(table[start+i][start+j]==num);

    if (count==1)
        return true;
    return false;
}

int main()
{
    int sudoku [N][N];//Genterint the Sudoku Table
    bool flag=true;//Flag that indicate if the solution is good.

    printf("Please enter your solution:\n");
    for(int i=0;i<N;i++)// Saving The solution in the the table.
            for(int j=0;j<N;j++){
                int current;
                scanf("%d",&current);
                sudoku[i][j]=current;
            }

        for (int i=0;flag&&i<N;i++){
            for (int dig=1;flag&&dig<N+1;dig++){
                if (!(i%SQRT_N)) //index of a row that start new small [SQRT_N]X[SQRT_N] cube on the prime diagonal
                    flag=checkCube(sudoku,i,dig);  /*checking that each digit appear one time in the [SQRT_N]X[SQRT_N] cubes on the prime diagonal*/

                if(flag)
                    flag=checkRow(sudoku,i,dig);
                if(flag)
                    flag=checkColumn(sudoku,i,dig);
            }
        }

    (flag)?printf("Valid solution!"): printf("Bad solution!");
    return 0;
}
