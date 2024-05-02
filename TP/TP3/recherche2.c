#include<stdio.h>
//pas fini
void prix(int article, int reference_donnee[], int length)
{   
    int i, résultat;
    for( i = 0; i < length; i++)
    {   
        if (article == reference_donnee[i]) résultat = 1;
    }
    char* liste_de_prix[4];
    if (résultat == 1)
    {
        printf("%s\n",liste_de_prix[i]);
    }
}

int main(int argc, char* argv[])
{
    int article = 130944;
    int ref[] = {104970, 104449, 130944, 103127, 174612};
    char* liste_de_prix[] = {"15€", "25€", "12€", "20€", "11€"};
    prix(article, ref, sizeof(ref)/sizeof(ref[0]));
    return 0;
}