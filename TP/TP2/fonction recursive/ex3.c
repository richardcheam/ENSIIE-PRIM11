#include<stdio.h>

int puiss(int x, int p)
{
    if (p == 0) return 1;
    else if (p % 2 == 0) return ( puiss(x, p/2) * puiss(x, p/2) );
    else return x * ( puiss(x, (p-1)/2) * puiss(x, (p-1)/2) );
}

int main(int argc, char* argv[])
{
    printf("%i\n", puiss(2, 3)); 
    return 0;
}
