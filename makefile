CFLAGS = -std=gnu99 -Wall
CC = gcc $(CFLAGS)
OUTPUT = unix


all: $(OUTPUT)

$(OUTPUT): main.o sheel.o
	$(CC) -o $(OUTPUT) main.o sheel.o

main.o: main.c sheel.o
	$(CC) -c main.c

sheel.o:
	$(CC) -c sheel.c

clean:
	rm -f *.o $(OUTPUT)
	echo Clean done
