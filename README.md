libunwind-examples
==================

This repo is just a bunch of tools and test code to help understand
the behaviour of libunwind.

 * unwind-pid - remote unwind example that uses ptrace to unwind the
   stack of an alien process, identified by PID
 * unwind-local - local unwind example

Thanks to Eli Bendersky, whose blog post on libunwind is easy to find
with a search engine and whose example code was a great help to get
started.

Tests
-----

The tests in this repo are not a full test suite, just a couple of
simple smoke tests that check unwinding into, out of and through the
(dynamically linked) C library.

`test-bsearch` has a stack the originates in application code, but whose
stack includes a C library function before we reach main.

    sh$ ./test-bsearch &
    [1] 13219
    sh$ ./unwind-pid $!
    0x400502: (cmp+0xc)
    0x7fb4de093677: (bsearch+0x57)
    0x400556: (main+0x52)
    0x7fb4de07c401: (__libc_start_main+0xf1)
    0x40042a: (_start+0x2a)
    sh$ kill %1
    [1]+  Terminated              ./test-bsearch
    
`test-sleep` has a stack that originates in the C library code to make
a system call.
    
    sh$ ./test-sleep &
    [1] 13224
    sh$ ./unwind-pid $!
    0x7f5f3329a7b0: (__nanosleep_nocancel+0x7)
    0x7f5f3329a71a: (sleep+0x2a)
    0x40050f: (main+0x19)
    0x7f5f331ee401: (__libc_start_main+0xf1)
    0x40042a: (_start+0x2a)
    sh$ kill %1
    [1]+  Terminated              ./test-sleep

`test-strlen` has a stack that originates in regular C library code.

    sh$ ./test-strlen &
    [1] 13240
    sh$ ./unwind-pid $!
    0x7ffb6c47f09f: (strlen+0x13f)
    0x4005c3: (main+0x2d)
    0x7ffb6c412401: (__libc_start_main+0xf1)
    0x4004ca: (_start+0x2a)
    sh$ kill %1
    sh$ 
    [1]+  Terminated              ./test-strlen

