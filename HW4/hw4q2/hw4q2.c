/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>
/*=========================================================================
  Constants and definitions:
==========================================================================*/
#define POSITIVE {"amaz","delight","excit","good","great","lov","stun","wonderful"}
#define NPOS 8
#define NEGATIVE {"annoy","bad","bor","disappoint","hat","horribl","repulse"}
#define NNEG 7
#define INVERT {"isn't","not","opposite","wasn't"}
#define NINV 4
#define MAXWORD 31
/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
char upCase(char c)
/*In case of capital letter return the small letter*/
{
    if (c >= 'A' && c <= 'Z'){
        return c - 'A' + 'a';
    }
    return c;
}
int sameBegin(char *s1,char *s2)
/*Getting two words and check if the have the same begining if yes r
eturn 0 else retring which one is after in the dictionary*/
{
    while (*s1){//checking by the length of s1
        if(s1[0]>upCase(s2[0]))//return -1 if s1 is bigger
            return -1;
        if(s1[0]<upCase(s2[0]))//return 1 if s1 is smaller
            return 1;
        s1++;
        s2++;
    }
    return 0;//s2 begin with s1
}
bool matchList(char *str,char **wordList,int wordListLen)
{/*return true if the word is in the list else false*/
    int low=0, mid, high=wordListLen-1;
    while(low <= high){//searching with binaty search
        mid = (low + high) / 2;
        int lookDir=sameBegin(wordList[mid],str);
        //asking for dircation to lookin up or down
        if(lookDir<0)
            high = mid - 1;
        else
            if(lookDir>0)
                low = mid + 1;
            else
                return true;

    }
    return false;
}
void printResult(int g)
/*Print the review as expected*/
{
    printf("Sentiment score: %d; ",g);
    if(g>0)
        printf("Positive review\n");
    else
        if (g<0)
            printf("Negative review\n");
        else
           printf("Couldn't tell\n");
}
int main()
{
    char *pos[NPOS]=POSITIVE;
    char *neg[NNEG]=NEGATIVE;
    char *inv[NINV]=INVERT;
    char word[MAXWORD];//the word we want to evaluate
    int c_Pos=0, c_Neg=0, c_Inv=1;//counters
    printf("Enter a sentence to evaluate:\n");
    while(scanf("%s",word)!=-1){
        if(matchList(word,pos,NPOS))
            c_Pos++;
        else
            if(matchList(word,neg,NNEG))
                c_Neg++;
            else
                if(c_Inv==1&&matchList(word,inv,NINV))
                    c_Inv=-1;
    }
    int grade=(c_Pos-c_Neg)*c_Inv;
    printResult(grade);
  return 0;
}
