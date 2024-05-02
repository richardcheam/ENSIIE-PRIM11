#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define epsilon 1e-20
// Question 1

struct node {
    double data;
    struct node *next; //self referential structure (just another pointer that points to another node - pointer to struct node)
};
typedef struct node *node;

node cons(node l, double val){
    node head = malloc(sizeof(node)); //allocate memory for a pointer called head to point to the first node l
    head -> data = val;
    head -> next = l; //head here is the pointer of the first node which points to another node l, next here is an arrow
    return head;
}

void print_node(node l){
    while (l != NULL){
        printf("--> [%lf] ",l -> data);
        l = l -> next;
    }
    printf(" --> [NULL]\n");
}

// Q2

int length_node(node l){
    int count = 0;
    if (l == NULL)
        printf("La liste est NULL");
    while (l != NULL){
        count++;
        l = l -> next;
    }
    return count;
}

// Q3

double sum_node(node l){
    double sum;
    while(l != NULL){
        sum += (l -> data);
        l = l -> next;
    }
    return sum;
}

// Q4 

node inverse_node(node *l){
    node previous, current, tmp;
    previous = NULL;
    current = *l;
    while (current != NULL){
        tmp = current -> next;
        current -> next = previous;
        previous = current;
        current = tmp;
    }
    *l = previous;
    return *l;
}

// Q5

double search(node l, double e){
    while (l != NULL){
        if (fabs((l -> data) - e) < epsilon){
            return l -> data;
            printf("oui");
        }
        else l = l -> next;
    }
    return 1; 
}

//Q6

void remove(node *l, double e){
    node tmp;
    while (*l != NULL){
        if (fabs((*l -> data) - e) < epsilon){
            
        }
        else *l = *l -> next;
    }
    return 1; 
}

int main(){
    node l = NULL;
    l = cons(l, 20);
    l = cons(l, 10);
    l = cons(l, 5);
    print_node(l);

    printf("La longeure de la liste = %d\n", length_node(l));
    
    printf("La somme de la liste = %lf\n",sum_node(l));

    print_node(inverse_node(&l));

    search(l, epsilon);
    return 0;
}