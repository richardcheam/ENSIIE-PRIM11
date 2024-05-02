typedef struct bucket *stack;

/* @ requires an unsigned character and an address of a valid stack
   @ assigns the stack
   @ ensures pushes the unsigned character to the top of the stack */
void push(int, stack *);

/* @ requires an address of a valid stack
   @ assigns the stack
   @ ensures returns the topmost element of the stack and remove it from the stack */
int pop(stack *);

/* @ requires an address of a valid stack
   @ assigns the stack
   @ ensures deletes the stack and free allocated memory */
void delete_stack(stack *);