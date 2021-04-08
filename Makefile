CC=gcc
CFLAGS=-Wall -Wextra -std=c99

build: main

main: ./main.o ./CircularDoublyLinkedList.o ./galactic_war_utils.o
	$(CC) $(CFLAGS) ./main.o ./CircularDoublyLinkedList.o ./galactic_war_utils.o -o main

./CircularDoublyLinkedList.o: ./CircularDoublyLinkedList.h ./CircularDoublyLinkedList.c
	$(CC) $(CFLAGS) ./CircularDoublyLinkedList.c -c -o ./CircularDoublyLinkedList.o

./galactic_war_utils.o: ./galactic_war_utils.h ./galactic_war_utils.c
	$(CC) $(CFLAGS) ./galactic_war_utils.c -c -o ./galactic_war_utils.o

./main.o: ./main.c
	$(CC) $(CFLAGS) ./main.c -c -o ./main.o

run:
	./main

clean:
	rm ./*.o
	rm main

