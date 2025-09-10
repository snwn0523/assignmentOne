CC = gcc
CFLAGS = -Wall -Wextra -std=c11

a1: main.c
	$(CC) $(CFLAGS) -o a1 main.c

clean:
	rm -f a1