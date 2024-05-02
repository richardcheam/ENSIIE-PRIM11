#include<stdio.h>

int moyenne(int tab[], int n){ //or int* tab
    int m = 0;
    for (int i = 0; i < n; i++)
    {
        m += tab[i];
    }
    m = m / n;
    return m;
}

int main()
{
    int tab[] = {5, 5, 5, 5, 5};
    int arrcount = sizeof(tab) / sizeof(tab[0]);
    printf("%d\n", moyenne(tab, arrcount));
}