#include<stdio.h>

int pgcd(int a, int b)
{
    int i, r, q = 0; //iteration, reste, quotient
    int pgcd; //plus grand commun diviseur
    do
    {
        i++;
        q = a / b;
        pgcd = r;
        r = a % b;
        a = b;
        b = r;
    } while (r != 0);
    printf("Iteration: %d\n", i);
    printf("Le pgcd est %d\n", pgcd);
    return i; 
    return pgcd;
}
int main()
{  
    pgcd(561, 357);
}

