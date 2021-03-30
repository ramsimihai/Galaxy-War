CC=clang
CFLAGS=-Wall -Wextra
DEBUG=-g -ggdb -O0 -march=native

build: galactic_war

galactic_war: ./galactic_war.o ./CircularDoublyLinkedList.o
	$(CC) $(CFLAGS) $(DEBUG) ./galactic_war.o ./CircularDoublyLinkedList.o -o galactic_war

./CircularDoublyLinkedList.o: ./CircularDoublyLinkedList.h ./CircularDoublyLinkedList.c
	$(CC) $(CFLAGS) $(DEBUG) ./CircularDoublyLinkedList.c -c -o ./CircularDoublyLinkedList.o

./galactic_war.o: ./galactic_war.c
	$(CC) $(CFLAGS) $(DEBUG) ./galactic_war.c -c -o ./galactic_war.o

./galactic_war.o: ./galactic_war.c
	$(CC) $(CFLAGS) $(DEBUG) ./galactic_war.c -c -o ./galactic_war.o


run:
	./TestCircularDoublyLinkedList

clean:
	rm ./*.o
	rm TestCircularDoublyLinkedList

