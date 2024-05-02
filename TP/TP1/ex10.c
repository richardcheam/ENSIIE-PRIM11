#include<stdio.h>

int main(int argc, char** argv)
{
    int n;
    
    do
    {
        printf("Nombre de carottes: "); scanf("%d", &n);
    } while(n < 0);

    if (n == 0) printf("Il n'y a pas de carotte.\n");
    else if (n == 1) printf("Il y a une carotte.\n");
    else printf("Il y a %d carottes.\n", n);

    return 0;
}