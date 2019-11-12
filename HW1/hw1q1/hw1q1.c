/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>

/*=========================================================================
  Constants and definitions:
==========================================================================*/

#define EQUAL 0.00001

/*-------------------------------------------------------------------------
Asking for sizes from the user and return if they can form a real triangle.
if they form a right one, it will print it's area.
At the end if the user form right triangles it will print the sum of
their areas and the average of the areas
 -------------------------------------------------------------------------*/

int main()
{
    double a,b,c;
    double sum_area=0;
    int count_right=0; //Count how many right triangle will be.
    printf("Enter the sides' sizes:\n");
    scanf("%lf %lf %lf",&a,&b,&c);
    while(a>0||b>0||c>0){ //the loop will stop when the user enter 0 0 0
        if (a+b>c&&a+c>b&&b+c>a){ //chacking if the sizes can form a real triangle
            printf("The given sizes form a valid triangle\n");
            double temp, area;
            if (a>b&&a>c){   //in case a is the bigger one
                temp=a;
                b=b;
                a=c;
                c=temp;
            }
                else{
                    if (b>c&&b>a){   //in case b is the bigger one
                        temp=b;
                        a=a;
                        b=c;
                        c=temp;
                    }
                } //At this point integer c peresent the biggest side.
                if(-EQUAL<=((c*c)-((a*a)+(b*b)))&&((c*c)-((a*a)+(b*b)))<=EQUAL){ //cheking if the triangle is a right on.
                    count_right++;//adding 1 to the counter of right triangles
                    area=(a*b/2);//caculating the area.
                    sum_area+=area;//suming the area.
                    printf("This is a right triangle with the area of %.2f\n",area);//printing the area.
                }
        }
        else    //the sizes cannot form a real triangle
            printf("The given sizes don't form a valid triangle\n");

    printf("Enter the sides' sizes:\n");    //asking for new sizes
    scanf("%lf %lf %lf",&a,&b,&c);
    }
    if(count_right>0){       //chacking if had been a right triangle in the input
        printf("Area sum of right triangles: %.2f\n",sum_area);
        printf("Area average of right triangles: %.2f\n",(sum_area/count_right));
}
return 0;
}
