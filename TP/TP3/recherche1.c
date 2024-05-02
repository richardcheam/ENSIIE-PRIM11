#include<stdio.h>

void test(int a, int ref[], int count)
{   
    int résultat;
    for(int i = 0; i < count; i++)
    {   
        if (a == ref[i]) résultat = 1;
    }
    if (résultat == 1) printf("Référencé\n");
    else printf("Pas de référence\n");
}

int main(int argc, char* argv[])
{
    int article = 130944;
    int length = 3;
    int ref[] = {104970, 104449, 130944};
    test(article, ref, length);
    return 0;
}