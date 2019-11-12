/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>



/*=========================================================================
  Constants and definitions:
==========================================================================*/

#define DECIMAL 10

/*-------------------------------------------------------------------------
 Multiply the digits of the number untill it gets one digits and check if it is even.
 -------------------------------------------------------------------------*/
int main()
{
    int num=0, m_digits;
    printf("Please enter a number:\n");
    scanf("%d",&num);// Asking the user to enter a round number.
    do{
        m_digits=1;//Initializing m_digits to be 1 that to multiplay the digits with it
        do{
           m_digits*=(num%DECIMAL);//multiply the right digit of the number in m_digits.
           if(!m_digits)//if one of the digits is 0 the number is zero and no need to continue.
                break;
           num/=DECIMAL;//Removing the right digit by dividin in DECIMAL.
        }
        while (num>0);
        num=m_digits;//Put the value of m_digits in num in order to do the process once again
    }
    while (num>DECIMAL);//stoping the process when the new number is one digit.

    (num%2) ?printf("The number is NOT Multiplication-Even.\n")
            :printf("The number is Multiplication-Even.\n");
  return 0;
}
