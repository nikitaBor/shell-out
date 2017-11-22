all: main.o
	gcc -o shell_out main.o
main.o: main.c
	gcc -c main.c
clean:
	rm *.o
	rm shell_out
run: all
	./shell_out
