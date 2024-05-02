#include<stdio.h>
#include<math.h>

int main(int argc, char* argv[])
{
    int c1, c2, h;
    c1 = 4;
    c2 = 3;
    h = 5;

    int test;
    if (h == sqrt(pow(c1, 2) + pow(c2, 2)))
    {   
        test = 1;
        printf("Ils peuvent représenter les longueurs des côtés d'un triangle rectangle d'hypoténuse de longueur h = %d.\n", h);
    }
    else
    {
        test = 0;
        printf("Ils ne peuvent pas représenter les longueurs des côtés d'un triangle rectangle d'hypoténuse de longueur h = %d.\n", h);
    }
    return 0;
}