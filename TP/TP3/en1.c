#include<stdio.h>

struct rationnel{
    int num;
    int den;
};
typedef struct rationnel rationnel;

void print_ratio(rationnel a){
    printf("%i/%i\n", a.num, a.den);
}
int main()
{
    rationnel a;
    a.num = 1;
    a.den = 3;
    print_ratio(a);
    return 0;
}