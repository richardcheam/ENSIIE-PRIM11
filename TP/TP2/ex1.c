#include<stdio.h>

int plusgrand(int a, int b);

int main(int argc, char* argv[])
{
    //retoure le plus grand de type int

    int a, b;
    printf("Entrez deux valeurs\n");
    printf("a : "); scanf("%d", &a);
    printf("b : "); scanf("%d", &b);
    plusgrand(a , b);
    return 0;

}

int plusgrand(int a,int  b)
{
    if(a > b) 
    {
        printf("%d\n",a);
        return a;
    }
    else if(b > a)
    {
        printf("%d\n",b);
        return b;
    }
    else 
    {
        printf("Il faut que deux valeurs sont différentes!!\n");
        return a;
        return b;
    }
}