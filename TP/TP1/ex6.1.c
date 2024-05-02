#include<stdio.h>

int main(int argc, char** argv)
{
    int n;
    printf("Entre: "); scanf("%d",&n);
    if (n % 2 == 0) printf("1\n");
    else printf("0\n");
    return 0;
}