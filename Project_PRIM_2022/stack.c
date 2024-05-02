#include "list.h"       // need bucket and cons
#include "stack.h"

#include <stdio.h>
#include <stdlib.h>


void push(int v, stack *p_st) {
    *p_st = cons(v, *p_st);
}

int pop(stack *p_st) {
    if (*p_st != NULL) {
        int n = (*p_st)->value;
        stack tmp = *p_st;
        *p_st = (*p_st)->next;
        free(tmp);
        return n;
    }
    return -1;
}

void delete_stack(stack *p_st) {
    stack tmp;
    while (*p_st != NULL) {
        tmp = *p_st;
        *p_st = (*p_st)->next;
        free(tmp);
    }
}