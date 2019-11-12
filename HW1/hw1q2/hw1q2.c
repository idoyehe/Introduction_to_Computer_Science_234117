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
  Upagradin Caesr cipher.
 -------------------------------------------------------------------------*/
int main()
{
    int ofst; //Creating integer for offset
    char org_c;//Initiate new character
    printf("Enter the offset:\n");
    scanf("%d",&ofst);
    while (ofst!=999)//The loop continues until the user insert ofset of 999
    {
    printf("Enter the enciphered message:\n");
    scanf(" %c",&org_c);
    while(org_c!='!') //The loop continues until the user insert '!'
        {
                switch (org_c){  // the user insert a digit
                case ('0'):
                case ('1'):
                case ('2'):
                case ('5'):
                case ('6'):
                case ('7'):
                case ('9'):org_c=' ';break;
                case ('3'):org_c='E';break;// put 'E' instead of 3
                case ('4'):org_c='A';break;// put 'A' instead of 4
                case ('8'):org_c='B';break;// put 'B' instead of 8
                }
                if(org_c!=' ')//incase org_c is a letter
                {
                    org_c-=ofst;
                    org_c+=Letters*(org_c<'A');
                }
                printf("%c",org_c);//printing the encrypted letter
                scanf("%c",&org_c);//insert a new character from the user
            }
        printf("\n");//begin new decoding process
        printf("Enter the offset:\n");
        scanf("%d",&ofst);
    }
  return 0;
}

