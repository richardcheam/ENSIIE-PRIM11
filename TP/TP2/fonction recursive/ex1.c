#include<stdio.h>

int puiss(int x, int p)
{   
    if (p == 0) return 1;
    else return x * puiss(x, p-1);
}

int main(int argc, char* argv[])
{
    
    printf("%i\n", puiss(2, 4));
    return 0;
}
