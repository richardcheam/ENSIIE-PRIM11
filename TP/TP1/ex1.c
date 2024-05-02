#include <stdio.h>

int main(int argc, char **argv) {
    int a = 4;
    int b = 3;
    int tmp;

    printf("Original:\n");
    printf(" a = %i\n", a);
    printf(" b = %i\n", b);

    tmp = a;
    a = b;
    b = tmp;

    printf("Apres la permutation:\n");
    printf(" a = %i\n", a);
    printf(" b = %i\n", b);

    return 0;
}