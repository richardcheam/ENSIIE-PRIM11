#include<stdio.h>

int square(int a);
int check(int a, int b, int h);

int main(int argc, char* argv[])
{
    int c1, c2, c3;
    printf("Entrée n'mporte quel nombre c1: "); scanf("%d",&c1);
    printf("Entrée n'mporte quel nombre c2: "); scanf("%d",&c2);
    printf("Entrée n'mporte quel nombre c3: "); scanf("%d",&c3);
    check(c1, c2, c3);
    return 0;
}

int square(int a)
{
    int sqr = a * a;
    return sqr;
}

int check(int a, int b, int h) //h est hypotenuse
{   
    int test;
    if (square(h) == square(a) + square(b))
    {
        test = 1;
        printf("Ça marche !\n");
        return 1;
    }
    else
    {
        test = 0;
        printf("Ça marche pas !\n");
        return 0;
    }
}