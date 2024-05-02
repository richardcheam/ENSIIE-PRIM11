#include<stdio.h>

int main(int argc, char** argv)
{
    int n;
    printf("Entre: "); scanf("%d",&n);
    if (n % 2 == 0) printf("Pair\n");
    else printf("Impair\n");
    return 0;
}