# Allocators

In today's lab, you are going to start getting familiar with some of the tools used to implement a memory allocator. A memory allocator in the C programming language, is more broadly 'a set of functions that support requests to allocate or deallocate memory'. 

Remember, part of this class is building a concrete mental model of what is really going on inside of a machine (So that there is "no more magic" when you see a computer running). We have looked at how memory is managed by the operating system and hardware, launching processes (with fork and exec), understanding a processes memory spaces, and now allocating memory--we are getting very low level!

# Logistics

For this lab, you must login into the servers through `your_ccis_name@login.ccs.neu.edu` to complete the assignment. The reason is because the examples I will provide below are compiled strictly for our machines architecture, and this is where your submission will be graded.

## Part 1 - Using malloc, calloc, and free

Lets first refresh on how to use our current memory allocator which lives in [stdlib.h](http://www.unix.org/version2/sample/stdlib.h.html). Below is an example of using some of the functions.

```c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){

    // Dynamically allocate some amount of memory
    char* message = (char*)malloc(sizeof(char)*11);

    // Check if memory allocation failed (i.e. we do not have enough bytes
    if(NULL == message){
        printf("Allocation failed\n");
        exit(0);
    }
    
    // If it did not fail, then copy a string into
    // our allocated memory.
    // Function signature: char* strcpy(char* dest, const char* src);
    strcpy(message, "Hello Mike\n");

    printf("%s",message);

    // Lets now free our memory
    free(message);

    // If we are working with data, it can sometimes be nice to zero everything
    // out.
    // You'll notice the parameters are a little flipped here.
    // This is asking for '57' blocks of memory that are the sizeof(int).
    // So we are getting 57*sizeof(int) pieces of memory).
    int* numberData = (int*)calloc(57,sizeof(int));    
    int i;
    // Let's confirm it is all zeroed out memory    
    for(i =0; i < 57; ++i){
        printf("%d ",numberData[i]);
    }

    // Lets free our data
    free(numberData);

    return 0;
}
```

## Part 2 - Background Reading on Memory Allocators

Take a moment to read the Cexcerpt.pdf (2 pages ~5 minutes reading) to get a basic understanding of how allocators work. 

**Discuss:** with your partner and write why you think `typedef long Align` was used. 

**Write a 1-2 sentence answer here:**

## Part 3 - Allocator building blocks

A few of the key system calls that we will need to understand are the following (My professors use to always say "read the man pages", so I will echo that in honor of them).

* Type in `man sbrk` in the terminal. Read the description of what sbrk does .

```
BRK(2)                                                       Linux Programmer's Manual                                                      BRK(2)

NAME
       brk, sbrk - change data segment size

```

* Type in `man mmap` in the terminal next.

```
MMAP(2)                                                          Linux Programmer's Manual                                                         MMAP(2)

NAME
       mmap, munmap - map or unmap files or devices into memory
```

* Type in `man mlock` next.

```
MLOCK(2)                                                         Linux Programmer's Manual                                                        MLOCK(2)

NAME
       mlock, mlock2, munlock, mlockall, munlockall - lock and unlock memory
```

What do you think mlock is good for? This article discusses some of the tradeoffs nicely: https://eklitzke.org/mlock-and-mlockall

**Discuss** with your partner.

**Write a 1-2 sentence answer here:**

## Part 4 - The simplest memory allocator

We can actually write a very simple implementation of a memory allocator. The allocator below just gives us however many bytes of memory we request. 

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void *mymalloc(size_t size) {
  void *ptr = sbrk(0);
  void *request = sbrk(size);
  if (request == (void*) -1) {
    return NULL; 
  }
  
  return ptr;
}

void setupProgram(){
	// Memory leak! But why?
	mymalloc(2);
	mymalloc(4);
	mymalloc(8);
	mymalloc(16);
	mymalloc(32);
	mymalloc(64);
	mymalloc(128);
	mymalloc(256);
}

int main(){

	setupProgram();

	return 0;
}
```

However, the problem with this allocator is that we do not have any notion over where that memory is. We also do not really know how much memory needs to be freed(or rather, could be reused rather than asking for more memory). This means we need some sort of data structure to keep track of our heap size.

**Discuss** with your partner what data structures you might use to keep track of memory. Record at least one below, but try to think of at least two in your discussion.

**Write a 1-2 sentence answer here:**

**Discuss** with your partner, do you think you will be able to use valgrind to monitor your custom memory allocator to detect potential memory leaks? 

**Write a 1-2 sentence answer here:**

## Part 5 - strace

Compile and run the sbrk.c program. Then run `strace ./sbrk`

strace is a program that intercepts system calls. You should be able to directly see where sbrk for instance has been called. Take a few moments to read the man pages.

```
STRACE(1)                                                   General Commands Manual                                                  STRACE(1)

NAME
       strace - trace system calls and signals

DESCRIPTION
       In the simplest case strace runs the specified command until it exits.  It intercepts and records the system calls which are called  by
       a  process  and  the  signals  which  are  received by a process.  The name of each system call, its arguments and its return value are
       printed on standard error or to the file specified with the -o option.
```

**Discuss** with your partner how many 'sbrk' system calls you see, and write your answer below.

**Write a 1-2 sentence answer here:**

## Lab Deliverable

1. Edit the readme and fill in the discussion points above in the appropriate spaces.
2. Fill in the 'sbrk.c' file and commit to the repository.

## More Resources to Help

* From the previous lecture we talked a bit about virtual memory. Containers and virtualization are a big topic in computer science. It is worth knowing about Docker https://docs.docker.com/get-started/ and how to get setup! (Probably a more appropriate tool for a software engineering class, but now you'll know how the internals work!)

## Going Further

* Take a look at malloc.c. You can skim around and read some of the comments to see how the libc library performs memory allocation!
  * https://code.woboq.org/userspace/glibc/malloc/malloc.c.html
* Another nice resource is the GNU C Allocator described in great detail here: https://www.gnu.org/software/libc/manual/html_node/Memory-Allocation.html
