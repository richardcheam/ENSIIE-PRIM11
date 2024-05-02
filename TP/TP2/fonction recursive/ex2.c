#include<stdio.h>
#include<stdlib.h>

int puiss(int x, int p)
{   
    if (p == 0) return 1;
    else return x * puiss(x, p-1);
}
int main(int argc, char* argv[])
{
    int* ptr = malloc(sizeof(int) * puiss(10, 10));
    printf("%i\n", puiss(10, 10));
    free(ptr);
    return 0;
}
/*
même si on utilise malloc/free, ça marche pas encore car la puissance est trop grande que la memoire ne 
pourrait pas stocker et également on applle la fonction puiss trop de fois en raison de l'utilisation la 
fonction récursive.
*/

