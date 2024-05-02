#include<stdio.h>
#include<math.h>

int main(int argc, char **argv)
{
    float x, dx;

    printf("x: "); scanf("%f", &x);
    printf("dx: "); scanf("%f", &dx);

    float de_sin = (sin(x + dx) - sin(x)) / dx;

    printf("Derivee de sinus: %f\n", de_sin);

    return 0;
}