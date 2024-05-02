#include<stdio.h>

int main(int argc, char* argv[])
{
    //afficher un triangle d'étoiles

    int n;
    printf("Entrez : "); scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        for (int j = n; j > i; j--)
        {
            printf("*");
        }
        printf("\n");
    }
}