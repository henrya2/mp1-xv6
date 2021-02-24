# xv6 MP1: Adding a system call

## Objectives

In this first xv6 machine problem you will be modifying and adding code to a
number of different files that implement the kernel. Along the way you'll learn
how to build the kernel and test/debug your work, and will hopefully acquire a
working knowledge of some essential kernel tasks and modules. You won't be
adding much source code; rather, the goal is to get you comfortable with the
workflow so that future assignments requiring more extensive changes to the
codebase won't be too intimidating!

## Obtaining the repository

As with the previous (and all subsequent) machine problems, you will claim your
private repository using the GitHub invitation link found in the assignment list
on the course homepage. Accept the invitation and clone your repository on the
computer where you'll be doing your work. 

Next, edit the "AUTHOR" file in your repository -- in it you will find an honor
pledge that you should sign with your information and today's date. Do this NOW
so you don't forget!


## Running xv6

If you successfully set up the development environment as instructed in the
previous machine problem, this part should be smooth sailing. First, make sure
you have the most recent version of the container image with the command:

    docker pull cs450/xv6

Next, spin up the container where you'll build/test your work:

- On Mac/Linux, run the command `make docker`.

- On Windows, do a `vagrant up` followed by a `vagrant ssh` to get into the
  Virtual machine. There, run the command `make docker`.

You should now be at a prompt that looks something like:

    root@0cc7df74917f:/mp#

Now you can compile and build xv6. To do so, just run the command `make`. This
will take a little while, and should end with output that looks like:

    ./mkfs fs.img README _cat _echo _forktest _grep _init _kill ...
    nmeta 59 (boot, super, log blocks 30 inode blocks 26, ...
    balloc: first 702 blocks have been allocated
    balloc: write bitmap block at sector 58

Now you can boot up xv6 in the QEMU emulator with the command `make qemu-nox`.
This should end in the following output:

    Booting from Hard Disk..xv6...
    cpu1: starting 1
    cpu0: starting 0
    sb: size 1000 nblocks 941 ninodes 200 nlog 30 logstart 2 ...
    init: starting sh
    $

You're now in xv6! You can explore a bit, and when you're ready to exit the xv6
session use the key sequence "`^a x`" (i.e., hit the 'a' key while holding down
the control key, then release both and hit the 'x' key) --- `^a` is a special
prefix key used to send the emulator an interrupt sequence.


## Working on xv6

The nice thing about using Docker/Vagrant is that changes to files on the host
machine (in your Mac/Linux/Windows file system) will automatically be
sychronized with the guest container. You can do all your coding with tools
installed on your host, and switch over to the container for testing purposes.

To re-build xv6, it's often a good idea to do a "`make clean`" before running
"`make`", as weird errors may arise otherwise. Get in the habit of just running
the commands together with "`make clean ; make`".

If you wish to debug (e.g., step through and set breakpoints in) the kernel, you
can use "`make qemu-nox-gdb`" to run the emulator in a mode that allows you to
attach a gdb session to it. After doing this you'll need to start another shell
in the same container to run gdb. You can do this with the command:

    docker exec -it cs450xv6 bash

This assumes that the container was started with the name "cs450xv6", which the
`make docker` command does for you. In the second shell, you can then run `gdb`
to start debugging the running kernel -- this should result in output like the
following:

    [f000:fff0]    0xffff0: ljmp   $0x3630,$0xf000e05b
    0x0000fff0 in ?? ()
    + symbol-file kernel
    warning: A handler for the OS ABI "GNU/Linux" is not built into this configuration
    of GDB.  Attempting to continue with the default i8086 settings.

    (gdb)

Enter "quit" at the gdb prompt to quit the debugger. As before, use the key
sequence `^a x` to exit xv6 in the emulator.


## Adding a system call

For this lab you'll add a new system call called `getcount` to xv6, which, when
passed a valid *system call number* (listed in the file "`syscall.h`") as an
argument, will return the number of times the system call was invoked by the
current process.

E.g., consider this test program:

    #include "types.h"
    #include "user.h"
    #include "syscall.h"

    int
    main(int argc, char *argv[])
    {
        int rc;
        printf(1, "hello world\n");
        rc = getcount(SYS_write);
        printf(1, "%d\n", rc);
        exit();
    }

The above program will produce the following output (note that xv6's `printf`
implementation invokes the `write` system call for each individual output
character):

    hello world
    12

Note that these counts are reset each time a process terminates, so they will be
consistent from run to run.

### Details

You will need to modify a number of different files for this exercise, though
the total number of lines of code you'll be adding is quite small. At a minimum,
you'll need to alter "syscall.h", "syscall.c", "user.h", and "usys.S" to
implement your new system call (try tracing how some other system call is
implemented, e.g., `uptime`, for clues). You will likely also need to update
`struct proc`, located in "proc.h", to add a syscall-count tracking data
structure for each process. To re-initialize your data structure when a process
terminates, you may want to look into the functions found in "proc.c".

Chapter 3 of the
[xv6 book](http://pdos.csail.mit.edu/6.828/2012/xv6/book-rev7.pdf) contains
details on traps and system calls (though most of the low level details won't be
necessary for you to complete this machine problem).

## Testing and Scoring

To manually test your implementation, you can place your test code in the file
"tester.c" (e.g., you can paste the test program shown above in there after you
finished adding your system call). During the build process this code will be
compiled to the program `tester`, which you can run when booted into xv6.

We also include an automated test suite for you, which you can run with the
command `make test-mp1`. The test source files (which you should not alter ---
we'll be using our own pristine copies in any case) can be found in the
"tests/mp1/ctests" directory if you're interested. If you pass all the tests,
you'll see results like the following:

    Summary:
    test build PASSED
    (build xv6 using make)

    test getcount1 PASSED (10 of 10)
    (call getcount(SYS_exec))

    test getcount2 PASSED (10 of 10)
    (call getcount after opening/reading from a file)

    test getcount3 PASSED (10 of 10)
    (call getcount in parent and child processes)

    Passed 4 of 4 tests.
    Overall 4 of 4
    Points 30 of 30

If a test fails, it'll stop immediately with an error report. If you want to
continue running all tests even after hitting a failure, do `make test-mp1-cont`
instead.

---

Each test is worth 10 points, for a maximum of 30 points. If your code fails to
build, you will not earn any points at all. If you do not pass a test, you will
not earn any points for it.

## Submission

Make sure that you edited the "AUTHOR" file in your repository and signed the
honor pledge with your student information. If you don't do this we won't be
able to associate your submission with you!

To submit your work, simply commit all your changes and push your work to your
GitHub repository.
