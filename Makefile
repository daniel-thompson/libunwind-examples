CC = $(CROSS_COMPILE)gcc
CFLAGS = -Os -Wall
CXX = $(CROSS_COMPILE)g++
CXXFLAGS = $(CFLAGS)
STRIP = $(CROSS_COMPILE)strip

APPS = unwind-pid unwind-local $(TESTS)
TESTS = test-bsearch test-cxx test-sleep test-strlen

all : $(APPS)

strip :
	$(STRIP) $(APPS)

clean :
	$(RM) $(APPS) *.o

test :
	for i in $(TESTS); \
	do \
		echo "./$$i &"; \
		./$$i & \
		pid=$$!; \
		sleep 0.1; \
		./unwind-pid $$pid; \
		kill $$pid; \
		echo; \
	done

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

