struct bucket {
    int value;
    struct bucket *next;
};

typedef struct bucket *list;

// for stack.c
/* @ requires an unsigned character and an address of a bucket
   @ assigns nothing
   @ ensures returns the address of a newly allocated bucket containing the given character
             and pointing toward the given bucket */
struct bucket* cons(int, struct bucket *);

/* @ requires an unsigned character and an address of a valid list
   @ assigns the list if it is empty, nothing otherwise
   @ ensures inserts the given character to the end of the given list */
void insert_end(int, list *);
