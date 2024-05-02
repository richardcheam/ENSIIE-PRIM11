#include<stdio.h>

void permutation(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(int argc, char* argv[])
{
    int x, y;
    printf("Entrez deux valeurs\n");
    printf("x : "); scanf("%d", &x);
    printf("y : "); scanf("%d", &y);
    permutation(&x, &y);
    printf("Après la permutation entre deux valeurs, alors on obtient: \nx : %d\ny : %d\n", x, y);

    return 0;
}