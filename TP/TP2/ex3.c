#include<stdio.h>

int puiss(int a, int b);

int main(int argc, char* argv[])
{
    //créer une fonction qui utilise comme la fonction pow() dans library math.h
    int x, y, résultat;
    x = 2;
    y = 30;
    résultat = puiss(x , y);
    printf("%d\n", résultat);
    return 0;
}

int puiss(int a, int b)
{   
    int n = 1;
    for (int i = 1; i <= b; i++)
    {
        n *= a;
    }
    return n;
}