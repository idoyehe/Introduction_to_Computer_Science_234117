/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>



/*=========================================================================
  Constants and definitions:
==========================================================================*/
#define Letters 26

/*-------------------------------------------------------------------------
    The Algorithm is printnig a pyramid of letters printed by order of the ABC...
    the user choose the amount of levels and the first level letter.
 -------------------------------------------------------------------------*/
int main()
{
    int line=0 ,print_ch=1; //Initializing two intergers for numbers of line and how many letters to print.
    char ch='!'; // Initializing char interger.

    printf("Enter the size of the pyramid:\n"); //Loop for correct input of lines
    scanf("%d",&line);
    while(line>26||line<1)
    {
        printf("Invalid size. Try again:\n");
        scanf("%d",&line);
    }
    printf("Enter the first letter in the pyramid:\n");//Loop for correct input of letter
    scanf(" %c",&ch);
    while(ch>'z'||ch<'a')
    {
        printf("Invalid letter. Try again:\n");
        scanf(" %c",&ch);
    }

    for (int i=line;i>0;i--) //Loop for eah line
    {
        for(int j=i;j>1;j--){ // loop for spaces before letter
            printf(" ");
        }
        for(int p=1;p<=print_ch;p++){ //loop for printing letter
            printf("%c",ch);
        }
        printf("\n"); // Moving to the next line.
        print_ch+=2; // addind 2 to the number of the letters in the line for the next line.

        ch = (ch-'a');
        ch = (ch+1)% Letters;  /* Move to the next letter int the abc..
                            but if the letter is 'z' return to 'a' */
        ch += 'a';
    }
  return 0;
}
