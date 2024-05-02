#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int rand_up_to(int max) {
  int r;
  do
    r = rand();
  while (r >= RAND_MAX - (RAND_MAX % (max + 1)));
  return r % (max + 1);
}

//1 create type matrix
typedef int ** matrix; //pointer points to another pointer

//2 squre matrix m
matrix create_matrix(int m){                       //allocate memory for rows (pointer points to another memo)
    matrix a = (matrix)malloc(m * sizeof(matrix)); //typecasting (matrix) here is not neccessary
    for (int i = 0; i < m; i++){          //allocate memory for column (each bloc of memory that got pointed by)
        a[i] = calloc(m, sizeof(matrix)); //OR a[i] = malloc(m * sizeof(matrix)); 
    }
    return a;
}

//3 affiche matrix a size m
void print_matrix(matrix a, int m){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < m; j++){
            printf("%3d", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//4 affiche l'address de la matrice a size m
void print_address_matrix(matrix a, int m){
    for (int i = 0 ; i < m ; i++){
        for (int j = 0 ; j < m ; j++){
            printf("%p  ", &a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//5 saisie la taille de matrice comme l'utilisateur veut
void ask_for_size(){
    int t;
    printf("Entrez la taille de matrice : ");
    scanf("%d", &t);
}

//6 remplir la matrice au harsard de la valeur entre 0 et n - à la matrice a de taille m
void rand_matrix(matrix a, int m, int n){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < m; j++){
            a[i][j] = rand_up_to(n);
        }
    }
}

//7 l'addtion de deux matrix a et b de la même taille m
matrix add_matrix(matrix a, matrix b, int m){
    matrix r = create_matrix(m);
    for (int i = 0 ; i < m ; i++){
        for (int j = 0 ; j < m ; j++){
            r[i][j] = a[i][j] + b[i][j];
        }
    }
    return r;
}

//8 free created matrix
void free_matrix(matrix a, int m){
    for (int i = 0 ; i < m; i++){
        free(a[i]);
    }
    free(a);
}

//9 la multiplication de deux matrices A et B de même taille m
matrix mul_matrix(matrix a, matrix b, int m){
    matrix r = create_matrix(m);
    for(int i = 0; i < m ; i++){
        for(int j = 0; j < m; j++){
            for (int k = 0; k < m; k++){
                r[i][j] = r[i][j] + (a[i][k] * b[k][j]);
            }
        }
    }
    return r;
}

//10 trace de matrice
int tr_matrix(matrix a, int m){
    int tr = 0;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++){
            if(i == j){
                tr += a[i][j];
            }
        }
    }
    return tr;
}

//11 matrice transposée de matrice a taille m
matrix matrix_transpose(matrix a, int m){
    matrix tmp = create_matrix(m);
    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++){
            for(int k = 1 ; k < m; k++){
                tmp[i][j] = a[i][j];
                a[i][j] = a[j][i];
                a[j][i] = tmp[i][j];
            }
        }
    }
    return tmp;
}
matrix matrix_trans(matrix a, int m){
    matrix t = create_matrix(m);
    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++){
            t[i][j] = a[j][i];
        }
    }
    return t;
}

//12 matrix éléments du triangle de Pascal (triangulaire inférieure)
matrix matrix_pascale(matrix a, int m){
    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++){
            if(j > i){
                a[i][j] = 0;
            }
        }
    }
    return a;
}

int main(){
    //ask_for_size();
    int t, tr;
    printf("Entrez la taille de matrice : ");
    scanf("%d", &t);

    matrix A = create_matrix(t);
    matrix B = create_matrix(t);
    matrix R = create_matrix(t); //add matrix
    matrix M = create_matrix(t); //mul matrix
    matrix T = create_matrix(t);

    rand_matrix(A, t, 5);
    rand_matrix(B, t, 5);

    print_matrix(A, t);
    print_matrix(B, t);
    //print_address_matrix(A, t);

    R = add_matrix(A, B, t);
    print_matrix(R, t);

    M = mul_matrix(A, B, t);
    print_matrix(M, t);

    tr = tr_matrix(M, t);
    printf("Trace de la matrix = %d\n\n",tr);

    T = matrix_trans(M, t);
    print_matrix(T, t);

    T = matrix_pascale(T, t);
    print_matrix(T, t);

    free_matrix(A, t);
    free_matrix(B, t);
    free_matrix(R, t);
    
    return 0;
}