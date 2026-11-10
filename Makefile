CC = gcc
CFLAGS = -Wall -Wextra -O2 -g

enigma: enigma.c
	$(CC) $(CFLAGS) -o enigma enigma.c

clean:
	rm -f enigma
