/*------------------------------------------------------------------------
  Include files:
-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>
/*========================================================================
  Constants and definitions:
=========================================================================*/
#define MAX_DIGITS 31//Because we want 30 digits but to include '\0' we need 31
#define MAX_OPERS 20
/*------------------------------------------------------------------------
Caculating Big Numbers
 ------------------------------------------------------------------------*/
int strLastDig(unsigned char sDigits[MAX_DIGITS])
/*getting string and return the index of the last digit*/
{
    int last=MAX_DIGITS-1;//assuming the string is 30 digits
    for(int i=0;i<MAX_DIGITS;i++){
        if(sDigits[i]=='\0'){
            last=i-1;//saving the index before the '\0'
            break;
        }
    }
    return last;
}
int numLastDig(unsigned int nDigits[MAX_DIGITS-1])
/*getting arrey of digits and return the index of the last digit*/
{
        for(int i=MAX_DIGITS-2;i>=0;i--){
            if(nDigits[i]!=0)
                return i;
    }
    return 0;
}
void cleanDigits(unsigned int nDigits[MAX_DIGITS-1])
/*Cleaning an arrey of digits into zeros*/
{
    for(int i=0;i<MAX_DIGITS-1;i++)
        nDigits[i]=0;
}

void intTOChar(unsigned int nDigits[MAX_DIGITS-1],unsigned char sDigits[MAX_DIGITS])
/*Getting arrey of digits and converts it into string from right to left*/
{
    int j=0;
    for(int i=numLastDig(nDigits);i>=0;i--){
        switch(nDigits[i]){
            case (0):sDigits[j]='0';break;
            case (1):sDigits[j]='1';break;
            case (2):sDigits[j]='2';break;
            case (3):sDigits[j]='3';break;
            case (4):sDigits[j]='4';break;
            case (5):sDigits[j]='5';break;
            case (6):sDigits[j]='6';break;
            case (7):sDigits[j]='7';break;
            case (8):sDigits[j]='8';break;
            case (9):sDigits[j]='9';break;
        }
        j++;
    }
    sDigits[j]='\0';
}
void chartoInt(unsigned char sDigits[MAX_DIGITS],unsigned int nDigits[MAX_DIGITS-1])
/*Getting string of digits and converts it
into arreys of digits from right to left*/
{
    int j=0;
    for(int i=strLastDig(sDigits);i>=0;i--){
        switch(sDigits[i]){
            case ('0'):nDigits[j]=0;break;
            case ('1'):nDigits[j]=1;break;
            case ('2'):nDigits[j]=2;break;
            case ('3'):nDigits[j]=3;break;
            case ('4'):nDigits[j]=4;break;
            case ('5'):nDigits[j]=5;break;
            case ('6'):nDigits[j]=6;break;
            case ('7'):nDigits[j]=7;break;
            case ('8'):nDigits[j]=8;break;
            case ('9'):nDigits[j]=9;break;
        }
        j++;
    }
}
bool summing(unsigned int oper_1[MAX_DIGITS-1],unsigned int oper_2[MAX_DIGITS-1])
/*Getting to arreys of digits in summing them by
changing the second, return true if the sum is over 30 digits*/
{
    unsigned int carry=0, sum=0;
    for (int i=0;i<MAX_DIGITS-1;i++){
        sum=oper_1[i]+oper_2[i]+carry;
        if(sum>9){//cheking if there is carry
            carry=1;//carry can be only 1 (because 9+9=18)
            sum%=10;//reducing sum
        }
        else
            carry=0;
        oper_2[i]=sum;//put sum in oper_2
        sum=0;
    }
    return carry;//if at the end there is carry it will return true
}
bool multiplication(unsigned int oper_1[MAX_DIGITS-1],unsigned int oper_2[MAX_DIGITS-1],unsigned int nResult[MAX_DIGITS-1])
/*Getting 2 arreys of digit calculating the multiplication of them,
and put it at the third ,return true if the sum is over 30 digits*/
{

    for (int i=0;i<numLastDig(oper_2)+1;i++){
        //goes over the digits of the second number
        unsigned int temp[MAX_DIGITS-1]={0};
        int carry=0, mul=0;
        int j;
        for(j=0;(i+j)<MAX_DIGITS-1&&j<numLastDig(oper_1)+1;j++){
            //goes over the digits of the first number
            mul= oper_1[j]*oper_2[i]+carry;
            if(mul>9){
                carry=mul/10;
                mul%=10;
            }
            else
                carry=0;
            temp[j+i]=mul;
            /*saving the result to new arrey but from the
            index of the digit the second number*/
            mul=0;
        }
            if((i+j)>MAX_DIGITS-2)//there is carry and no place to put it
                return true;
            temp[j+i]=carry;//put the carry in the next index.

        if(summing(temp,nResult))//summing the results into an arrey
            return true;
    }
    return false;//No over flow
}

void calcBig(char op,unsigned char operands[][MAX_DIGITS], int numOperands,unsigned char result[MAX_DIGITS], bool* overflow)
/*Using other functiions to do the suming and the multiplication*/
{
    unsigned int tResult[MAX_DIGITS-1]={0};//temporary result
    chartoInt(operands[0],tResult);
    //put the first number in temporary result
    int i=1;//
    if(op=='+'){
        while (!*overflow&&i<numOperands){
            unsigned int nOper[MAX_DIGITS-1]={0};
            chartoInt(operands[i],nOper);
            *overflow=summing(nOper,tResult);
            i++;
        }
    }
    if(op=='*'){
        while (!*overflow&&i<numOperands){
            unsigned int nOper[MAX_DIGITS-1]={0};
            unsigned int temp[MAX_DIGITS-1]={0};
            chartoInt(operands[i],nOper);
            *overflow=multiplication(tResult,nOper,temp);
            //saving to temp the result
            intTOChar(temp,operands[i]);
            //loding the result into the string
            cleanDigits(tResult);
            //clean nResult before loading it with new number
            chartoInt(operands[i],tResult);
            i++;
        }
    }
    if(*overflow==0)//no over flow loding the temporary result to result
        intTOChar(tResult,result);
}
int main()
{
    char op;
    int numOperands=0;
    unsigned char opers[MAX_OPERS][MAX_DIGITS], result[MAX_DIGITS];
    printf("Select operator:\n");
    scanf(" %c",&op);
    printf("How many operands:\n");
    scanf("%d",&numOperands);
    printf("Enter operands (seperated by new line):\n");
    for(int i=0;i<numOperands;i++)
        scanf("%s",opers[i]);
        //save the operands to matrix that each row is new operand
    bool overflow=false;//assumming no overflow
    calcBig(op,opers,numOperands,result,&overflow);
    (!overflow)?printf("result:\n%s",result):printf("result:\noverflow!");
  return 0;
}
