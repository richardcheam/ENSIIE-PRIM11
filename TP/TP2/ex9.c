#include<stdio.h>

int puiss(int n, int p, int r) //nombre, puiss, résultat
{
    r  = 1;
    for(int i = 0; i < p; i++)
    {
        r *= n;
    }
    int *pr; pr = &r;
    return *pr;
}

int main() 
{
    int x, y, r;
    printf("Entrez deux valeurs: \n");
    printf("x : "); scanf("%d", &x);
    printf("y : "); scanf("%d", &y);
    printf("%d\n", puiss(x, y, r));
    return 0;
}