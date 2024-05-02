#include<stdio.h>

struct rationnel
{
    int num;
    int den;
};
typedef struct rationnel ratio;

void add_ratio(ratio a, ratio b)
{
    ratio r;
    r.num = (a.num * b.den) + (b.num * a.den);
    r.den = (a.den * b.den);

    int resultat = r.num / r.den;
    int reste = r.num % r.den;

    printf("\n%i/%i + %i/%i = %i/%i = %i\nAvec la reste %i\n\n", a.num, a.den, b.num, b.den, r.num, r.den, resultat, reste);
}

int main()
{   
    ratio a;
    ratio b;
    a.num = 10; a.den = 2;
    b.num = 600; b.den = 23;
    add_ratio(a, b);
}