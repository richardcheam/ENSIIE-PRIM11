#include<stdio.h>

int main(int argc, char* argv[])
{
    //afficher un triangle d'étoiles

    int n;
    printf("Entrez : "); scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            printf("*");
        }
        printf("\n");
    }
}