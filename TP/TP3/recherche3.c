#include<stdio.h>

//Proposez une procédure qui affiche les références de tous les articles correspondant à un prix donné.

int main()
{
    int ref[] = {101, 102, 103, 104, 105, 106}; 
    int prix[] = {10, 10, 12, 10, 14, 12};
    int p;
    int arrcount = sizeof(ref) / sizeof(ref[0]);

    do
    {
        printf("Entrez un prix préféré : "); scanf("%d",&p);
    } while (p < 1);
    
    printf("Les références des articles correspondant au prix entré : ");

    for (int i = 0; i < arrcount; i++){
        if (p == prix[i]) printf("%d ", ref[i]);
    }

    printf("\n");
}