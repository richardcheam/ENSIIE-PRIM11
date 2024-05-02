#include<stdio.h>

int main(int argc, char* argv[])
{
    //retourne 1 si la valuer entrée est pair, 0 sinon.
    int a;
    printf("Entrez une valeur : "); scanf("%d", &a);
    if (a % 2 == 0) printf("1\n");
    else printf("0\n");
    return 0;
}