CC=gcc -Wall

prog: main.o list.o stack.o function.o
	$(CC) -o $@ $^ -lm

main.o: main.c list.h stack.h function.h
	$(CC) -o $@ -c $<

function.o: function.c define.h stack.h function.h
	$(CC) -o $@ -c $< 

list.o: list.c list.h
	$(CC) -o $@ -c $<

stack.o: stack.c stack.h list.h
	$(CC) -o $@ -c $<

# $@ = rule name (left of :)
# $^ = all dependencies (right of :)
# $< = first dependency