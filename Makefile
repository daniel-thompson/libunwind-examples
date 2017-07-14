CC = gcc
CFLAGS = -Os -Wall -funwind-tables
CXX = g++
CXXFLAGS = $(CFLAGS)

APPS = unwind-pid unwind-local test-bsearch test-cxx test-sleep test-strlen

all : $(APPS)

clean :
	$(RM) $(APPS) *.o

unwind-pid : unwind-pid.o die.o
	$(CC) $(CFLAGS) -o $@ $^ -lunwind-ptrace -lunwind-generic

unwind-local : unwind-local.o die.o
	$(CC) $(CFLAGS) -o $@ $^ -lunwind

test-bsearch : test-bsearch.o
	$(CC) $(CFLAGS) -o $@ $^

test-cxx : test-cxx.cxx
	$(CXX) $(CXXFLAGS) -o $@ $^

test-sleep : test-sleep.o
	$(CC) $(CFLAGS) -o $@ $^

test-strlen : test-strlen.o
	$(CC) $(CFLAGS) -o $@ $^

