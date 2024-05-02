#include <stdio.h>
#include <stdlib.h>

struct bucket{
    int val;
    struct bucket *next;
};
typedef struct bucket *list;

list cons(list l, int v){
    list head = (list)malloc(sizeof(list));
    head -> val = v;
    head -> next = l; 
    return head;
}

void print_list(list l){
    while (l != NULL){
        printf("-> [%i] ", l -> val);
        l = l -> next;
    }
    printf("-> [NULL]\n");
}

//Q1
void insert_half(list l){
    while (l != NULL && l->next != NULL){
        l->next = cons(l->next, (l->val + l->next->val)/2);
        l = l->next->next;
    }
}

//Q2
list insert(list l, int value){
    list tmp;
    list new = (list)malloc(sizeof(list));
    new->val = value;
    new->next = NULL;
    int key = value;
    if (l == NULL || key < l->val){
        new->next = l;
        l = new;
    }
    else{
        tmp = l;
        while (tmp->next != NULL && tmp->next->val < key){
            tmp = tmp->next;
        }
        new->next = tmp->next;
        tmp->next = new;
    }
    return l;
    free(new);
}

void insert_copy(list *l, int n) { //insert without allocate any new memo
    if (NULL == *l) {
        *l = cons(NULL, n);
    } else {
        if (n <= (*l)->val) {
            *l = cons(*l, n);
        } else {
            list curr = *l;
            while (curr->next != NULL && curr->next->val < n) {
                curr = curr->next;
            }
            curr->next = cons(curr->next, n);
        }
    }

}

//Q3
list insertion_sort(list l) {
    list sorted = NULL;
    while (l != NULL) {        
        insert_copy(&sorted, l->val);
        l = l->next;
    }
    return sorted;
}

//Q4.1
list range(int a, int b) { 
    if (a == b) {
        return NULL;
    }
    return cons(range(a+1, b), a); //recursive fucntion here is to add value + 1 to l->next (see a+1 as l->next)
}
list two2n(int n) {    
    return range(2, n+1);
}

//Q4.2
void remove_multiples(list *l, int n){
    list current = *l;
    list prev = NULL;
    while (current != NULL){
        if(current->val % n == 0){
            if(prev == NULL){
                *l = current->next; //delete the first value cos previous was orginally equal to NULL
            }else{
                prev->next = current->next;
            }
            current = current->next;
        }
        else{
            prev = current;
            current = current->next;
        }
    }
}
 
//Q4.3
list eratosthene(int n){
    list a, b;
    a = two2n(n);
    b = a;
    while (b != NULL){
        remove_multiples(&b->next, b->val); //&b->next cos we want to keep the value 2 in the list
        b = b->next;
    }
    return a;
}

int main(){
    list l = NULL;
    l = cons(l, 10);
    l = cons(l, 20);
    l = cons(l, 30); 
    print_list(l);

    insert_half(l); 
    print_list(l);

    l = insert(l, 40); 
    l = insert(l, 13); 
    print_list(l);

    insert_copy(&l, 23); print_list(l);

    l = insertion_sort(l); print_list(l);

    list n;
    n = two2n(10); print_list(n);

    remove_multiples(&n, 2); print_list(n);

    list z;
    z = eratosthene(50); print_list(z);
    return 0;
}