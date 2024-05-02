#include<stdio.h>
#include<math.h>

int main()
{
    // definir pi = 3.14 sans utiliser M_PI
    // const float PI = 4 * atan(1);
    double v;
    int r = 1;
    v = (4 * M_PI * pow(r, 3)) / 3;
    printf("%lf\n", v);
    return 0;
}