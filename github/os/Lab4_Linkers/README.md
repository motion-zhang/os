# Linker - "Respect the Linker"

In today's lab we will start by building a library with our compiler. Then we are going to exploit how the linker works to perform a little trick. This trick will also expose you briefly to the field of computer security, and just how fragile systems really are!

# Part 1 - Making a library

A linkers overall job is to 'glue' code together. With that in mind, let's make our first shared object file (i.e. a library).

1. First take a look at the *lottery.c* program located in this repository.
	- lottery.c is a program that generates the four random numbers used in the mega-millions lottery. 
	- This program is a top secret program! This program is so top secret, we would not want to let anyone know about how the random numbers are generated.
2. Next compile and run the program lottery to generate the mega-millions number.
	- `gcc lottery.c -o lottery`
3. Uh oh, *you should be getting some linker error messages like this* -- We forgot to link in our library!

```
/tmp/lottery-2362b1.o: In function main:
lottery.c:(.text+0x58): undefined reference to TopSecretGenerateRandomNumber
lottery.c:(.text+0x87): undefined reference to TopSecretGenerateRandomNumber
lottery.c:(.text+0xb6): undefined reference to TopSecretGenerateRandomNumber
lottery.c:(.text+0xe5): undefined reference to TopSecretGenerateRandomNumber
clang: error: linker command failed with exit code 1 (use -v to see invocation)
```

Let us investigate more closely the lottery.c file to see what is going on. Look for the function `TopSecretGenerateRandomNumber()` function near the top of the source code.

```
// This function is external to our
// code, but will be found by the linker
extern int TopSecretGenerateRandomNumber();
```

The `extern` means that the function is located externally to our current source code file. This is a promise to the compiler that this function will exist at some point, once the linker brings in all of the other libraries.

So instead of compiling and runnnig, let's simply generate a .o file with `gcc -c lottery.c`. Because we are only buildng the object file, this is okay. We will however confirm that external function (TopSecretGenerateRandomNumber) however is undefined(i.e. there is no code that defines what the function should do, only a function declaration).

## Objdump

1. Run `objdump -t lottery.o`
2. This will inspect the symbols found within the lottery.o file that was generated. 
	- Can you confirm TopSecretGenerateRandomNumber is not defined? 

```
0000000000000000         *UND*	0000000000000000 TopSecretGenerateRandomNumber
0000000000000000         *UND*	0000000000000000 fflush
0000000000000000         *UND*	0000000000000000 printf
0000000000000000         *UND*	0000000000000000 srand
0000000000000000         *UND*	0000000000000000 stdout
0000000000000000         *UND*	0000000000000000 time
```

Remember that the `-t` symbol is outputting the symbol table. This is a list of functions that are found in the object file. The meanings of each of the columns can be uncovered by running `man objdump` and then scrolling to see what **-t** means.

## Modularity (Shared object files (.so))

Okay, so perhaps some savvy programmers has defined this TopSecretGenerateRandomNumber function somewhere. Afterall, spitting your code into libraries and making your functions modular is good practice. And there are many lotteries after all, so they probably made it a shared library for others to borrow. Additionally, with something sensitive as a lottery, we would probably want to hide the TopSecretGenerateRandomNumber function so could not see all of the source code. 

Upon investigatating the contents of this folder, I find a file called libsecret.so (.so extension for shared object file). There is no source code however, so we'll do the next best thing. 

1. Run `objdump -t libsecret.so` to investigate. 
	- What are some of the functions you see being used in this library?

```
0000000000000000 g     F .text	0000000000000015 TopSecretGenerateRandomNumber
0000000000000000         *UND*	0000000000000000 rand
```
(The *g* means that the symbol is external, and the F .text means there is a function found in the .text section of the object file)

In order to create a shared object file such as libsecret.so, we would use:  `gcc -fPIC -shared secret.c -o libsecret.so`.  Once again however, no secret.c file to be found (Well, there is in the 'hidden' folder of this lab if you really want to look, but pretend it does not exist).

The good news is we were able to confirm a a function called TopSecretGenerateRandomNumber is available in libsecret.so. Perhaps we can link this in!

### Aside -- yet more tools (nm)

Another tool called *nm*  shows us the symbols within an executable as well (there is another tool called llvm-nm as well)

Try running the command now to see. `nm -g libsecret.so`

## Linking two .o files

Let us now try to compile our lottery.c with the library that contains any functions definitions we need. This should ensure all of the functions are defined and available to be put into one final executable object file.

1. Try `gcc lottery.c libsecret.so -o lotto`
	- Ah ha, no errors! (Or at least none that were planned!)
2. Let us try to run `./lotto`
	- `./lotto: error while loading shared libraries: libsecret.so: cannot open shared object file: No such file or directory`
	- Hmm another error, but we can see libsecret.so within our current directory. I thought we did everything right?

### Introducing ldd

There is a nice tool that can help us debug linker errors called ldd. ldd prints out shared library dependencies. Investigate with `man ldd` to se the general description.

```
LDD(1)                                        Linux Programmer's Manual                                        LDD(1)

NAME
       ldd - print shared library dependencies
```

1. Let us go ahead and run `ldd ./lotto`
	- This will tell us what libraries were found and not found.
	- If we look below, we see lib.c for example (The standard C programming library) was found.
	- But unfortunately, no libsecret.so!
		- The good news however, is at least it is linked in--we just cannot find it.	
```
	linux-vdso.so.1 =>  (0x00007ffeec3df000)
	libsecret.so => not found
	libc.so.6 => /lib64/libc.so.6 (0x00007ffb2b93c000)
	/lib64/ld-linux-x86-64.so.2 (0x00007ffb2bd18000)
```

Okay, so let us add our library to a *path* where it can be found (it is in the same folder afterall though...) When our linker is trying to find shared libraries at runtime, our linker searches in a few directories for shared libraries. One of the directories that it looks at, is set by an [environment variable](https://en.wikipedia.org/wiki/Environment_variable) from the system (An environment variable is essentially a global variable the entire system knows about, and is often used for various configuration settings). In this case the environment variable we care about is called LD_LIBRARY_PATH (i.e. "Load Library Path"). 

1. Now where we want to look, is in the current directory.
2. So if we run: `LD_LIBRARY_PATH=. ./lotto`
	- Notice the subtle "." right after the equals sign.
3. Then tada! Finally we see our output!
	- What the command does is loads any libraries in the current path(the single dot at the start is the path.) for the current program. 
	- Run this line a few times when you are confident it will work, and then continue onwards.

## Next problem -- I have never win the lottery

Now the lottery folks are protecting this `./lotto` program that I have shared with you. It is very secret. Unfortunately, I have never won the lottery, and today I would like to win. With what we have learned about linkers, we can hack the lottery!

1. Write a program called hack.c that is the following.
	```
	#include <stdlib.h>

	// Our version of the random number generator
	int TopSecretGenerateRandomNumber(){
		return 42;
	}
	```
2. Compile it as a shared library: `gcc -shared -fPIC hack.c -o libhack.so`
	- Note: the `-fPIC` creates position independent code
	- `-shared` makes this a shareable library as opposed to static
3. Now here is the trick.
	- The order in which the linker searches for shared libraries starts by the searching the previous command we used (i.e. LD_LIBRARY_PATH). However, we can point the linker (i.e. force the linker to follow our search order) to load some libraries first. As when the linker searchers, it will be satisfied once it finds all of the libraries it needs when resolving undefined references.

## LD_PRELOAD -- the hack

Let us preload our 'hack' library to help us win the lottery.

1. What we are doing is exporting another environment variable on the terminal. 
	- Note that with export, this preserves a change in our environment.
2. On the current terminal type: `export LD_PRELOAD=$PWD/libhack.so lotto`
3. (Build the hack source code into a library if you have not previously done so.)
4. Now run again once again with: `LD_LIBRARY_PATH=. ./lotto`
```
	And the winning numbers are...
	42
	42
	42
	42
	42 42 42 42...who would have guessed!
```
**Wait a second as the audience gasps...it looks like something is wrong with the lottery!**

So as we are noticing, the linker is quite powerful! But this also teaches us one of the weaknesses of shared libraries, because they are allowed to be preloaded before runtime. This trick can often be quite handy for debugging purposes as well (i.e. maybe we want to try a test function when debugging that prints additional information).

This little hack is quite powerful in the sense that we can redefine the behavior of any C-library function. We could for example write our own memory allocator by overriding the malloc and free functions. And there is really no guareentee our malloc even allocates memory, maybe it does something else?

## Final Step

1. Run `echo $LD_PRELOAD` to see the environment variables you have set. We will want to clean up our environment back to where we started.
2. Run `unset LD_PRELOAD` to get rid of any exported variables and return to our default environment (You can test this works by doing `echo $LD_PRELOAD` to ensure this is empty).

## Check your understanding

1. Understand we can save compile time by only compiling the libraries we change or the files we have source code for.
2. Understand how the linker helps find the code needed for our executable. The code does not live altogether in one executable.
3. (Some example is provided below) Try compiling a small program with g++ and the -g option. That is, using the c++ programming language instead of C (g++ is the GNU C++ compiler). What do you notice that is different about the functions(*Hint* search for foo)? Do we have some information that could be useful for LD_PRELOAD?

```
// compile with: g++ -g -c hello.cpp
// Investigate with:  objdump -t hello.o 
int foo(int a, int b){
	return a+b;
}

int main(){

	foo(1,2);	

	return 0;
}
```

## Part 2 - Compiler Hooks

With our linker trick, we have replaced an existing function that we knew about (or could otherwise decipher if we have additional debugging information). (**Another word of caution** never distribute commercial software compiled with the debugging symbols.)

However, we have learned that compilers at some point have to touch every part of a code base. They are after all, responsible for compiling all of the code! This can make them quite powerful tools, especially if we want to instrument programs and uncover more information. The term *instrument* here means to add additional functionality to some function.

The GCC Compiler in particular has some neat compiler hooks specifically for instrumentation. These *hooks* allow us to add in our own functions and probe a programs behavior.

1. Navigate to the `trace/` folder with `cd trace/` in your terminal.
2. Within it, you will see two files `main.c` and `trace.c`. Both are quite small, investigate them now.
	- What you will see in the trace.c is some oddly named functions--two to be exact. 
	- Each of these functions has an attribute marked on them to not be instrumented (__attribute__((no_instrument_function))
). This notation is specific to the gcc compiler. 
	- Why that is the case? Well, these functions are going to be called at the start and end of every other function that is called in a program. That is, our compiler will automatically inject these functions into every other function call made (This is a similar analogy to a linker injecting some code from a shared library into our project).

1. First compile our main program in the trace folder: `gcc -finstrument-functions -g -c -o main.o main.c `
   1. We have passed an additional flag that leaves 'stubs' for our instrumentation with the `-finstrument-functions` flag.
2. Next, let us compile our trace file: ` gcc -c -o trace.o trace.c `
3. When we have both of our object files, we can then compile them into a single executable binary: `gcc main.o trace.o -o main`
4. Finally, run `./main ` and observe the output.

# Your Deliverable

Your task now, is to take these compiler hooks and do something more useful. 

1. Find some sample c program you can modify, or continue to use the main.c provided.
2. Modify the trace.c program to count the total number of functions called.
3. Next, investigate time.h.
	1. Use the time functions to calculate the start and stop time of each function [Example](https://www.tutorialspoint.com/c_standard_library/c_function_difftime.htm). This will help you determine which functions you spend time in.
	2. Note, if your time returns '0', it may be because there is so little work to do, and the computer is so fast '0' is returned. Think about adding more work to some test functions, and investigating different resolution timers.
4. Commit your new `trace.c` file to the repository.

# More resources to help

1. Linkers and tools https://llvm.org/docs/CommandGuide/llvm-nm.html
2. https://rafalcieslak.wordpress.com/2013/04/02/dynamic-linker-tricks-using-ld_preload-to-cheat-inject-features-and-investigate-programs/
3. http://amir.rachum.com/blog/2016/09/17/shared-libraries/#compiling-a-shared-library
4. https://jvns.ca/blog/2014/11/27/ld-preload-is-super-fun-and-easy/
5. Compiler Hooks https://balau82.wordpress.com/2010/10/06/trace-and-profile-function-calls-with-gcc/

# Going Further

(Optional) This programmer was waiting for you 9 years ago to finish this task early so you could read his 20 part linker series. [https://lwn.net/Articles/276782/]
