CC = gcc
CFLAGS = -Os -Wall -funwind-tables

APPS = unwind-pid unwind-local test-bsearch test-sleep test-strlen

all : $(APPS)

clean :
	$(RM) $(APPS) *.o

unwind-pid : unwind-pid.o die.o
	$(CC) $(CFLAGS) -o $@ $^ -lunwind-ptrace -lunwind-generic

unwind-local : unwind-local.o die.o
	$(CC) $(CFLAGS) -o $@ $^ -lunwind

test-bsearch : test-bsearch.o
	$(CC) $(CFLAGS) -o $@ $^

test-sleep : test-sleep.o
	$(CC) $(CFLAGS) -o $@ $^

test-strlen : test-strlen.o
	$(CC) $(CFLAGS) -o $@ $^

