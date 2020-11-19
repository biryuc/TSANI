//
//  main.c
//  1111
//
//  Created by Мария Ульянова on 22.09.2020.
//



#include <stdio.h>
#include <math.h>

void CalculateRoots(float a, float b, float c, float *pd, float *x1, float *x2)
{
    float d;
    pd = &d ;
    d = b * b - 4 * a * c;
    if(d < 0)
    {
        d = -d;
        printf("d=%g, x1= %g, x2=%g \n",-d,(-b)/(2*a),sqrt(d)/(2*a));
    }
    else
    {
        if(d == 0)
        {
            printf("d = 0 x= %g \n", -b/(2*a));
        }
        else
        {
            printf("d=%g,  x1= %g, x2= %g \n",d,(-b+sqrt(d))/(2*a),(-b-sqrt(d))/(2*a));
        }
    }
}

//#include <stdlib.h>
int main (int argc, char *argv[])
{
   
    //while(GetKey()!='q')
    while(1)
    {
        
        float a,b,c;
        float d,x1,x2;
        float x,y;
        printf("enter a, b, c: ");
        scanf("%f %f %f", &a, &b, &c);
        if(a == 0)
        {
            if(b == 0)
            {
                if(c == 0)
                {
                    printf("x - anythingnumber\n");
                }
                else
                {
                    printf("nosolution\n");
                }
            }
            else
            {
                printf ("is not quartumequation : x = %g\n", (-c/b));
            }
        }
        else
        {
            CalculateRoots(a,b,c,&d,&x1,&x2);
            x = -b/(2*a);
            y = a*x*x +b*x+c;
            printf("coordinates of apexof the parabola: (%g%g)\n",x,y);
        }
        getchar();
        char ch  = getchar();
        if(ch == 'q') break;
     //   KeyHit();
    }
 return 0;
 }




