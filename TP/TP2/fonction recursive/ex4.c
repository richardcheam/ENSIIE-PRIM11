#include<stdio.h>

int puiss(int x, int p)
{
    if (p == 0) return 1;
    else if (p % 2 == 0) return ( puiss(x, p/2) * puiss(x, p/2) );
    else return x * ( puiss(x, (p-1)/2) * puiss(x, (p-1)/2) );
}
int main(int argc, char* argv[])
{
    printf("%i\n", puiss(2, 300000)); 
    return 0;
}

/*
En ce cas, c'est la même chose que ex2.c, mais on a séparé la fonction récursive en deux, cest-à-dire 
on ne l'appelle trop de fois. Donc, il n'affiche pas SEGMENTATION FAULT, mais ce temps la valeur 0 à la
place.
/* 