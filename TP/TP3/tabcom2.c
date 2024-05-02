#include<stdio.h>

void add(int degre, int p1[], int p2[], int p3[])  //ou int *p1, *p2, *p3
{
    for (int i = 0; i < degre; i++)
    {
        p3[i] = p1[i] + p2[i]; //*(p3 + i) = *(p1 + i) + *(p2 + i)
    }
}

int main(int argc, char* argv[])
{
    int degre = 3;
    int p1[] = {2, 2, 2};
    int p2[] = {2, 2, 2};
    int p3[3];
    add(degre, p1, p2, p3);

    for (int i = 0; i < degre; i++)
    {
        printf("%i ", p3[0]);
    }
    
    printf("\n");
    return 0;
}