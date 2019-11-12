/*-------------------------------------------------------------------------
  Include files:
-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*========================================================================
  Constants and definitions:
=========================================================================*/
#define DEAD -1

/*------------------------------------------------------------------------
Get two grops of soliers and return how many victories you can get
 ------------------------------------------------------------------------*/
void rem_sort(int[],int[], int);
void internal_msort(int[],int, int[], int[],int[]);
void merge(int[],int,int[],int,int[],int[],int[],int[]);
void copyArreys(int[],int[],int);
void gettingArrey(int[],int[],int);
void strike(int[],int[],int[],int[],int);
int victories(int[],int);
void printVicts(int[],int);

int main()
/*Length: 20 Rows*/
{
    int size=0;
    printf("How many soldiers in each team?\n");
    scanf("%d",&size);
    int *att = malloc(sizeof(int) * size);
    int *def = malloc(sizeof(int) * size);
    int *indexAtt = malloc(sizeof(int) * size);
    int *indexDef = malloc(sizeof(int) * size);
    if(att!=NULL&&def!=NULL&&indexAtt!=NULL&&indexDef!=NULL){
        //malloc succeed to allocate memory
        printf("And what are their powers?\n");
        gettingArrey(att,indexAtt,size);
        gettingArrey(def,indexDef,size);
        rem_sort(att,indexAtt,size);//sorting atteckes arrey
        rem_sort(def,indexDef,size);//sorting defenders arrey
        strike(att,indexAtt,def,indexDef,size);
        printVicts(att,size);
    }
    free(att);
    free(def);
    free(indexAtt);
    free(indexDef);
    return 0;
}
/*Part A*/
void rem_sort(int a[],int index[], int n)
/*Cover funcation for the sorting
Length:5 Rows*/
{
    int *tmp_array = malloc(sizeof(int) * n);
    //Generate a temp arrey to the sorting
    int *tmp_array2 = malloc(sizeof(int) * n);
    //Generate a temp arrey to save the indexes
    if(tmp_array!=NULL&&tmp_array2!=NULL)
    //malloc succeed to allocate memory
        internal_msort(a, n, index,tmp_array,tmp_array2);
    free(tmp_array);
    free(tmp_array2);
}
void copyArreys(int output[],int input[], int n)
/*Getting 2 arreys and copy one to other
Length:1 Row*/
{
    for (int i=0;i<n;i++)output[i]=input[i];
}

void internal_msort(int a[], int n, int index[], int helper_array[],int helper_array2[])
/*Getting an arrey and sorting it from the highset number to the smallest
as well save the indexes
Length:9 Rows*/
{
    int left = n/2;
    int right=n-left;
    if (n < 2)
        return;
    internal_msort(a, left,index, helper_array,helper_array2);
    internal_msort(a + left, right,index+left, helper_array,helper_array2);
    merge(a, left, a + left, right, helper_array,index,index+left,helper_array2);
    copyArreys(a, helper_array, n);
    copyArreys(index, helper_array2,n);
}
void merge(int a[], int na, int b[], int nb, int c[],int in_right[],int in_left[],int d[])
/*getting two sorted arreys and sorting them into a new arrey
Length:13 Rows*/
{
    int ia, ib, ic;
    for(ia = ib = ic = 0; (ia < na) && (ib < nb); ic++){
        if(a[ia] > b[ib]){
            c[ic] = a[ia];
            d[ic]=in_right[ia++];
        }
        else{
            c[ic] = b[ib];
            d[ic]=in_left[ib++];
        }
    }
    for(; ia < na; ia++, ic++){
        c[ic] = a[ia];
        d[ic]=in_right[ia];
    }
    for(; ib < nb; ib++, ic++){
        c[ic] = b[ib];
        d[ic]=in_left[ib];
    }
}
/*Part B*/
void gettingArrey(int a[],int b[], int n)
/*Getting from the user numbers and put into an arrey
as well put indexes in second arrey Length: 5 Rows*/
{
    if(!n)
        return;
    gettingArrey(a,b,n-1);
    scanf("%d",&a[n-1]);
    b[n-1]=n;
}
void strike(int att[], int indexAtt[], int def[], int indexDef[], int size)
/*Do the strike while compering the att arrey to def arrey
Length: 7 Rows*/
{
    if(!size)
        return;
    if(att[0]>def[0]){
        printf("Attacker #%d should strike defender #%d\n",indexAtt[0],indexDef[0]);
        //printing the indexes
        att[0]=DEAD;//Signed deadsoliders with -1
        strike(att+1,indexAtt+1,def+1,indexDef+1,size-1);
    }
    else
        strike(att,indexAtt,def+1,indexDef+1,size-1);
}
int victories(int att[],int size)
/*Retruning how many soliders had been dead while checking how many -1 is in the arrey
Length: 3 Rows*/
{
    if(!size||att[size-1]==DEAD)
        return size;
    return victories(att,size-1);
}
void printVicts(int att[],int size)
/*print the number of Victories
Length: 2 Rows*/
{
    int victs=victories(att,size);
    (victs>0)?printf("Total victories: %d\n",victs):printf("No victories!");
}


