#include <stdio.h>
#include <stdlib.h>

struct bucket{
    int val;
    struct bucket *next;
};
typedef struct bucket *list;

list cons(int v, list l){
    list head = (list)malloc(sizeof(list));
    head -> val = v;
    head -> next = l;
    return head;
}

void print_list(list l){
    while(l != NULL){
        printf("-> [%d] ", l -> val);
        l = l -> next;
    }
    printf("-> [NULL]\n");
}

list inverse_list(list l){
    list previous, current, tmp;
    previous = NULL;
    current = l;
    while (current != NULL){
        tmp = current -> next;
        current -> next = previous;
        previous = current;
        current = tmp;
    }
    l = previous;
    return l;
}

int main(){
    list l = NULL;
    l = cons(10, l);
    l = cons(20, l);
    l = cons(30, l);
    print_list(l);
    print_list(inverse_list(l));
    return 0;
}