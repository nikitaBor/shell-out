all: main.o parse_execute.o redirect.o
	gcc -o shell_out main.o parse_execute.o redirect.o
main.o: main.c
	gcc -c main.c
parse_execute.o: parse_execute.c parse_execute.h
	gcc -c parse_execute.c
redirect.o: redirect.c redirect.h
	gcc -c redirect.c
clean:
	rm *.o
	rm shell_out
run: all
	./shell_out
