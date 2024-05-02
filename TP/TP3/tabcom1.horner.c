#include<stdio.h>

int horner(int poly[], int degre, int r) {
    if (degre == 1) {
        return poly[0];
    }
    int poly_n[degre-1]; //poly si le degré de n n'est pas égale à 0
    for (int i = 0; i < degre-1; i++) {
        poly_n[i] = poly[i+1];
    }
    return r * horner(poly_n, degre-1, r) + poly[0]; //recursive function
}
int main()
{   
    int r = 1, degre = 3; //le résultat est forcément appliqué quand le point est égal à 1
    int poly[] = {2, 2, 2};
    printf("%d\n", horner(poly, degre, r));
    return 0;
}