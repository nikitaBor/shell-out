all: main.o parse_execute.o
	gcc -o shell_out main.o parse_execute.o
main.o: main.c
	gcc -c main.c
parse_execute.o: parse_execute.c
	gcc -c parse_execute.c
clean:
	rm *.o
	rm shell_out
run: all
	./shell_out
