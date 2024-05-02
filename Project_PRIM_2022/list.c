#include "list.h"

#include <stdio.h>
#include <stdlib.h>

struct bucket* cons(int v, struct bucket* n) {
    struct bucket *res = malloc(sizeof(struct bucket));
    res->value = v;
    res->next = n;
    return res;
}

void insert_end(int v, list *pl) {
    list x = cons(v, NULL);

    // if the list is empty
    if (*pl == NULL) {
        *pl = x;
    }
    // if the list is not empty
    else {
        list tmp = *pl;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = x;
    }
}