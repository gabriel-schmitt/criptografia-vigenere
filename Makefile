CC = gcc
CFLAGS = -Wall -Wextra -O2 -g

vigenere: vigenere.c
	$(CC) $(CFLAGS) -o vigenere vigenere.c

clean:
	rm -f vigenere
