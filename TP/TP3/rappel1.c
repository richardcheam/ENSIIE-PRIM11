#include<stdio.h>

void increment(int *p)
{
    *p = *p + 1;
}
int main()
{
    int n;
    printf("Entrée: "); scanf("%d", &n);
    increment(&n);
    printf("%d\n", n);
}
