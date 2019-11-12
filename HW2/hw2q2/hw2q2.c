/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>

/*=========================================================================
  Constants and definitions:
==========================================================================*/

#define MAX_GRADE 100
#define MIN_GRADE 0

/*-------------------------------------------------------------------------
Asking the user to enter size of two classes and grades of the students in those classes.
Print whether the class are twin if there is equal grades in the same classes
 -------------------------------------------------------------------------*/
int main()
{
    int seats=-1;
    printf("Please enter the class size:\n");
    scanf("%d",&seats);
    int count_Grades[MAX_GRADE-MIN_GRADE+1]={0};//Creating an arry with a range between the Max and the Min grades +1 to include the Min grade.
    printf("Please enter first class grades:\n");
    for(int i=0;i<seats;i++){//Asking to the first class grades
        int current;
        scanf("%d",&current);
        count_Grades[current-MIN_GRADE]++;//Adding 1 to the current index/grade.
    }
    printf("Please enter second class grades:\n");
    for(int i=0;i<seats;i++){//Asking to the second class grades
        int current;
        scanf("%d",&current);
        count_Grades[current-MIN_GRADE]--;//Removing 1 from the current index/grade.
    }
    //At that point if the class are twins the all counters should be 0
    int flag;
    for(flag=0;flag<MAX_GRADE+1;flag++)
        if (count_Grades[flag]) //When one of the arry counters is not 0 the if gets "true"
            break;// Get out the loop when it founds one counter that not 0
    (flag<MAX_GRADE+1)?printf("We dont have twins\n"):printf("We have twins!\n");// Checking if the loop ended before it checked all the counters.
  return 0;
}
