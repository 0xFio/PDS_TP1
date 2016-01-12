CFLAGS = -std=gnu99 -Wall
CC = gcc $(CFLAGS)
OUTPUT = unix


all: $(OUTPUT)

$(OUTPUT): main.o shell.o
	$(CC) -o $(OUTPUT) main.o shell.o

main.o: main.c shell.o
	$(CC) -c main.c

shell.o:
	$(CC) -c shell.c

clean:
	rm -f *.o $(OUTPUT)
	echo Clean done
