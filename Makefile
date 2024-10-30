build:
	gcc -g -std=gnu11 -o tema3 main.c graf-L.c
run:
	./tema3
clean:
	rem tema3
valgrind:
	valgrind --leak-check=yes --track-origins=yes ./tema3