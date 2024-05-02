#include<stdio.h>
#include<stdlib.h>

typedef struct rationnel{
    int num;
    int den;
}
ratio;

int pgcd(int a, int b)
{
    while (a != b)
    {   
        if (a > b) a -= b;
        else b -= a;
    }
    return a; 
    return b;
}

int ppcm(int a, int b)
{   
    return abs(a * b) / pgcd(a, b);
}

void add_ratio(ratio a, ratio b)
{
    ratio r;
    r.num = (a.num * b.den) + (b.num * a.den);
    r.den = (a.den * b.den);

    int reduisant;
    //while(r.num % r.den == 0)
    //{
        reduisant = ppcm(a.den, b.den);
    //}
    printf("%i/%i + %i/%i = %i/%i\nAprès la reduction: %i/%i\n", a.num, a.den, b.num, b.den, 
    r.num, r.den, r.num/reduisant, r.den/reduisant);
}

int main()
{
    ratio a; ratio b;
    a.num = 2; a.den = 3;
    b.num = 4; b.den = 10;
    add_ratio(a, b);
}
