CC=clang
CFLAGS=-Wall -Wextra
DEBUG=-g -ggdb -O0 -march=native

build: main

main: ./main.o ./CircularDoublyLinkedList.o ./galactic_war_utils.o
	$(CC) $(CFLAGS) $(DEBUG) ./main.o ./CircularDoublyLinkedList.o ./galactic_war_utils.o -o main

./CircularDoublyLinkedList.o: ./CircularDoublyLinkedList.h ./CircularDoublyLinkedList.c
	$(CC) $(CFLAGS) $(DEBUG) ./CircularDoublyLinkedList.c -c -o ./CircularDoublyLinkedList.o

./galactic_war_utils.o: ./galactic_war_utils.h ./galactic_war_utils.c
	$(CC) $(CFLAGS) $(DEBUG) ./galactic_war_utils.c -c -o ./galactic_war_utils.o

./main.o: ./main.c
	$(CC) $(CFLAGS) $(DEBUG) ./main.c -c -o ./main.o

./main.o: ./main.c
	$(CC) $(CFLAGS) $(DEBUG) ./main.c -c -o ./main.o


run:
	./main

clean:
	rm ./*.o
	rm main

