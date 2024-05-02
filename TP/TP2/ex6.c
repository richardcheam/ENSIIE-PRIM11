#include<stdio.h>

int main(int argc, char* argv[])
{   
    int i;
    printf("%8c", 73);
    for ( i = 1; i <= 10; i++)
    {
        printf("%4d", i);
    }
    
    printf("\n");
    int j;
    for ( j = 0; j <= i; j++)
    {
        printf("-----");
    }

    printf("\n");
    for (int a = 1; a <= 10; a++)
    {
        printf("%4d%4c", a, 73);
        for (int b = 1; b <= 10; b++)
        {
            printf("%4d", b*a);
        }
        printf("\n");
    }
}