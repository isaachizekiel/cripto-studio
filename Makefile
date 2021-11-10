CC=gcc
CFLAGS=-I. -g -Wall

aes-test: aes.o aes-test.o

aes.o:
	$(CC) -c aes.c

aes-test.o:
	$(CC) -c aes-test.c


clean:
	rm -rf aes.o aes-test.o aes-test
