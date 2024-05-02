#include<stdio.h>

int main(int argc, char** argv)
{
    int n;
    printf("Entre: "); scanf("%d",&n);
    if (n % 2 == 0) printf("L'entier %d est pair.\n", n);
    else printf("L'entier %d est impair.\n", n);
    return 0;
}