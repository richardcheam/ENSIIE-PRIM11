#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

//Q1 return a pointer that points to the biggest double value
double *plus_grande(double a, double b){
    double *r = (double *)malloc(sizeof(double));
    if (a > b) r = &a;
    else if (a < b) r = &b;
    else printf("The values are equal\n");
    return r;
    free(r);
}

//Q2 return a pointer that points to the value of the difference between two arrays 
int *difference(int t1[], int t2[], int size){
    int *r = (int *)malloc(size * sizeof(int));
    for(int i = 0; i < size; i++){
        r[i] = (t1[i] - t2[i]);
    }
    return r;
    free(r);
}

//Q3 return the pointer points to the sorted array (using selection sort)
int *sort_array(int t[], int size){
    int *r = (int *)calloc(size, sizeof(int));
    for (int z = 0; z < size; z++){     //duplicate array for the usage in the next for loop
        r[z] = t[z];
    }
    int min;
    for (int i = 0; i < size; i++){
        min = i;            
        for (int j = i + 1; j < size; j++){
            if (r[min] > r[j]){         //if index[0] is bigger than index[1] then
                min = j;                //remember that the smallest value is at index[1] by storing it in the variable called min
            }
        }
        swap(&r[i], &r[min]);           //then swap the value of array from of index[0] and index[1]
    }
    return r;
    free(r);
}

int main(int argc, char* argv[]){
    printf("%lf\n",*plus_grande(10, 20)); 
    int a[] = {10, 3, 14, 8, 20};
    int b[] = {1, 2, 1, 4, 10};
    int size = 5;

    int *result = difference(a, b, size);
    for(int i = 0; i < size; i++){
        printf("%i ", result[i]);
    }
    printf("\n");
    int *sort = sort_array(result, size);
    for(int i = 0; i < size; i++){
        printf("%i ", sort[i]);
    }
    printf("\n");
    return 0;
}  