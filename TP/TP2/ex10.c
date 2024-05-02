#include<stdio.h>
#include<stdlib.h>

void pgcd_ppcm(int a, int b, int* pgcd, int* ppcm)
{   
    int c = a; //we need initial value of  a and b to compute ppcm (ligne 16)
    int d = b;
    while(a != b)
    {
        if (a > b) a -= b;
        else b -= a;
    }
    if (a > b) *pgcd = a;
    else *pgcd = b;
    *ppcm = abs(c * d) / c;
}

int main(int argc, char* argv[])
{   
    int x, y, pgcd, ppcm;
    x = 561; y = 357;
    pgcd_ppcm(x, y, &pgcd, &ppcm);
    printf("PGCD = %i\nPPCM = %i\n", pgcd, ppcm);
    return 0;
}