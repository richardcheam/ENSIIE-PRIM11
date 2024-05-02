#include <stdio.h>
#include <math.h>
//point is the value of variable of the equation 
//poly is the coefficient of the equation
//i here is the degree of the equation (degre_au_plus)
int result(int degre, int poly[], int point) { 
    int r = 0;
    for (int i = 0; i < degre; i++) {
        r += poly[i] * pow(point, i);
    }
    return r;
}
int main() {
    int degre = 3;
    int poly[] = {4, 2, 3};
    int point = 1;
    printf("p(%i) = %i\n", point, result(degre, poly, point));
    return 0;
}