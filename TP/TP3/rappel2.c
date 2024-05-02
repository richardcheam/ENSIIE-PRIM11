#include<stdio.h>

void increment(int *p, int e)
{
    *p += e;
}
int main()
{
    int n, i;
    printf("Entrée : "); scanf("%d", &n);
    printf("Incrément par : "); scanf("%d", &i);
    increment(&n, i);
    printf("%d\n", n);
}