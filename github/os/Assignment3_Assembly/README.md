# Due Date: October 4, 2018 at 11:59 PM.

TODO Please edit the following information in your assignment

- Name: Liangmou Zhang
- How many hours did it take you to complete this assignment? 60
- Did you collaborate with any other students/TAs/Professors? Only a short period of office hours. 
- Did you use any external resources? (Cite them below)
  - Sources given in piazza and class
  - https://www.youtube.com/watch?v=8nIilb2kiSU
  - https://www.youtube.com/watch?v=a8l8PwCzw20
  - https://www.testbytes.net/blog/dynamic-testing-and-static-testing/
- (Optional) What was your favorite part of the assignment?
  - Doing the parsing is interesting, but too many bugs. Probably because of not familiar with C.
- (Optional) How would you improve the assignment?
  - Do more time on reviewing lectures and other resources. But the time is really limited for me, since my other three 
    class also have a lot of works to do. I will try to attend more office hours but I really can't make so much time.


# Introduction

For this assignent you are going to be practicing some [Assembly programming](https://en.wikipedia.org/wiki/Assembly_language) and learning other low level skills! Note that, in the past when teaching assembly, I have noted that this can be a more difficult assignment for the following reasons:

1. You cannot simply dive into the code without a plan.
2. You really should do the readings, or at least study an assembly cheat sheet before and while you are attempting the assignment.
3. You should use the [compiler generated assembly](https://godbolt.org/) as a helper--but only use really really small examples to test your understanding (It will be obvious if you write your code in C, and submit the assembly--you may not do that). 
4. Luckily--for this assignment we are taking a small jump into the assembly. In future courses, you may write some assembly from scratch!

**Note** It is important that you work on the assignment on the ccis servers (That is where you are testing, and your personal machine may have a different architecture!). I recommend using a text editor like vim, nano, or emacs while working remotely. Practicing using these tools over time will help you streamline an optimal workflow weather you are working remotely or on your local desktop.

# Part 1 Assembly - Writing Functions in Assembly

We have previously looked at some examples of assembly code. And we additionally have an understanding of how the stack stores data in memory by pushing in data. "Removing" data is then done by manipulating the stack pointer which is stored in the %rsp register (remember, %rsp always points to the top of the stack). There are some concerns however that you may have in your mind:

- How do I write 'functions' in assembly to make assembly code writing *easier* and more *maintainable*.?
- If we only have 16 registers, how can I write functions with a lot of arguments?
- How do I jump into a function and return back to where I left off?

You might have yet more questions even--and that is wonderful! Remember, assembly programming is sort of similar to solving a puzzle and getting everything to fit just right. Let me however remind you to the jobs of a procedure/function/method to orient you with what we must achieve:

1. Pass control
	- Start executing from start of procedure.
	- Return back to where we called from.
2. Pass data
	- Procedure arguments and return value are passed.
3. Memory management
	- Memory allocated in the procedure, and then deallocated on return.
4. Try to do this in the most minimal way.

## Background on functions

<img align="right" width="400px" src="http://www.cs.virginia.edu/~evans/cs216/guides/stack-convention.png" alt="Stack from http://www.cs.virginia.edu/~evans/cs216/guides/x86.html">

Writing a function in assembly almost follows a 'design recipe', and it is very useful to draw a picture of the stack (an example is shown to the right) as you write your function. Think of a function as broken into three different parts.

1. The setup - Sets up our stack
2. The body - Does the work
3. The finish/return - Pops things off the stack so we can resume execution to where we left off.

### The setup

This is where we are starting the execution of our function. Typically, it looks something like this

```asm
pushq %rbp
movq %rsp, %rbp
pushq %rbx
```

### The body

This is where the work is done.

### The finish/return

This is where we have to pop our stack, because we are done with our temporary (i.e. local) variables. Our temporaries or local variables are things like the arguments of a function that were passed in. Typically this looks something like this:

```asm
movq -8(%rbp),%rbx
movq %rbp, %rsp
popq %rbp
ret
```

## Assembly Example 1

I want to provide a few assembly examples, so you can see how the work is done. Try these examples first before jumping straight into assembly programming. This first example is of using a subroutine, or a sort of 'function call' with no arguments. This is a nice way to keep our code relatively clean.

```asm
# Assemble with
# 1.) gcc - c funcion.s
# 2.) ld function.o -o function
# 3.) ./function
.global _start

# Here we have a label, and we directly place some ASCII text
# into our program.
.welcome:
    .ascii "Welcome to this example\12" # A 24 character long
                                        # string. Note the \12
                                        # at the end is a 'line feed'
.text

# _printWelcome is a subroutine (i.e. a block of code we can execute)
# This is one way to 'modularize' our code.
_printWelcome:
    movq $1, %rax
    movq $1, %rdi
    leaq .welcome,%rsi # Load effective address, is a
    movq $24, %rdx
    syscall
    ret


# A subroutine to exit the program
_exit:
    movq $60, %rax
    xor %rdi, %rdi
    syscall

# The entry point into our program
_start:

    call _printWelcome
    call _exit
```

## Assembly Example 2

Here is an example of a simple function that is provided by a nice set of videos: https://www.youtube.com/watch?v=S-ZDUYMoy3Y&list=PLHMcG0zmCZcj7hKyHgQGGEZ41UWKaISKU See if you can follow along! I recommend watching all of the videos to truly understand the work being done--they might be helpful for Task 1!

## Task 1

Your task is to write two assembly functions--an `long add(long, long)` and `long subtract(long,long)` function in a file called *function.s*. A user will select which of the two functions to execute before terminating. A sample of the output from your program should look something like the following.

```
Select an operation
1 - add
2 - subtract
1
6
5
11
```

Here is the same output with my comments (To make it clear)

```
Select an operation # Use a syscall to write this out
1 - add		    # Use a syscall to write this out
2 - subtract        # Use a syscall to write this out
1 		    # The user selected '1'
6                   # The first input
5                   # The second input
11                  # 6+5 = 11, so print out '11' 
                    # Note: if this had been subtraction 
		    # (i.e. user selected '2' at the start), it would be 6-5 = 1                   
```

Some things I foresee in this assignment that may be tricky are:

- How to get user input.
- Think about if we read in a '1' is that stored as a *long with a value of 1* or some other representation of the ascii 1.
	- What if we sum to relatively large numbers, like 5000 and 6000? How would we output them, and would it be useful to have a function to do so?

# Part 2 - Cycle Count Tool

You may be wondering how good are compilers at generating assembly from our C code (Similar to the way you may have a good and bad translator when communicating in different languages)? How can we be sure that our compiler is generating efficient assembly? There are afterall, many different ways to write a program that generates the same output.

Part of being a good systems programmer, is the ability to build tools that measure. In this case, you are going to write a small parser in C that counts the number of instructions and counts how many instructions are needed to run that program from top to bottom.

As an example, if an assembly program had the following code:

```asm
MOVQ a, %rax
MOVQ b, %rbx
ADDQ %rbx, %rax
IMULQ %rbx
MOVQ %rax, c
```

Your tool will report a summary of the total Instructions(i.e. ADDQ, MOVQ, IMUQ, etc.) found. Additionally, you will estimate the total cycles needed for hardware to execute this code.

```asm
ADDQ 1
MOVQ 3
IMULQ 1

Total Instructions = 5
Total Cycles = ???
```

* Your tool should read in a file name through the command line arguments for what file is being analyzed (e.g. ./tool barbones.s)
  * (hint, investigate what argc and argv are).
* barebones.s is provided to be used as an example input file for your tool.
  * Within barebones, there are some questions for you to answer. Modify the source file with your answers.
* You will modify a file called tool.c which you will implement your tool in. 
  * At the very least, your program should output counts for: ADD, SUB, MUL, DIV, MOV, LEA, PUSH, POP, RET.
    * i.e. For your analysis (and for the sake of simplicity), consider ADDQ, ADDB, ADDL, etc. each as an 'ADD' instruction.
* You may find https://fresh2refresh.com/c-programming/c-strings/c-strcat-function/ helpful for learning some string processing in C.
* Use the Agner Fog's instruction table (http://www.agner.org/optimize/instruction_tables.pdf) to estimate how many cycles the program will run. That is, take an instruction like MOV which typically takes 1 cycle, and sum them together and output the result.
  * Note that this is again an estimate (MOV with different data types itself takes different number of cycles! So your answer will be an approximation. I am expecting there to be some variance, even within the class--attempt something reasonable).
 
## Static Analysis 
 
Our Cycle Count Tool is what we call a 'static analysis'. That is, it uncovers information about our programs before it is running (during compile-time). Given that our tool uncovers information before the program, what is (at least) one pro of this, and one con you can think of?

Pro:
1. Have a cohesive program, identify potential software issues, dectects codes needed to refactored.

Con:
1. Problems only when software is published may not be detected. Need a lot of times.

## Dyanmic Analysis

The opposite of a static analysis is a dynamic analysis. Dynamic analysis tools record and return information about programs that are in the process or have finished executing. An example of a dynamic analysis tool is [valgrind](http://valgrind.org/). What do you think a pro and con of dynamic analysis would be?

Pro:
1. Test code in real life, detect subtle code bugs, identify weak areas, can be applied to any applications.

Con:
1. May give false conclusion, may have security issue. 

# Part 3 - GDB Introduction 

GDB is a debugger for the programs that we are compiling with the GCC compiler. It helps us search and step through programs and track down errors in our program. Learning how to debug errors through a debugger is an essential skill for all computer scientists!

1. Watch the following video from Greg Law: *Give me 15 minutes and I'll change your view of GDB* https://www.youtube.com/watch?v=PorfLSr3DDI
2. Next browse this tutorial to get a little more familiar with GDB: https://www.cs.cmu.edu/~gilpin/tutorial/ 
3. Then follow the walkthrough below based on the video to get some practice.

## GDB Walkthrough with a sample program

Enter the following program below and save it somewhere (It is the same one from the Greg Law video).
```c
#include <stdio.h>

int main(void){
        int i =0;
	printf("Hello, world\n");
        printf("i is %d\n",i);
	i++;
	printf("i is now %d\n",i);

        return 0;
};
```

Compile the program with debug symbols(The *-g* flag does this).
`gcc hello2.c -g -o hello2`

`gdb ./hello2`

## GDB TUI (Text User Interface)

Here are the instructions for the TUI part of the video roughly written out. Practice using them with the program above.

- Type: `start`
- Type: `list`
- You can type 'next' to move line by line.
- Then press [Ctrl+x a] (Press Ctrl and x at the same time, then press 'a' key after)
  - (Pressing [Ctrl+x a] again will bring you back to just the gdb terminal)
- Typing in 'next' again moves another line (or simply hit 'enter' which repeats the previous command).
- Ctrl+L will clear the screen after the text prints to clean it up.
- Now try hitting [Ctrl+x 2]
  - You will now see multiple windows with the assembly and the source code.
  - Pressing [Ctrl+x o] will cycle between the windows.
  - Hitting [Ctrl+x 2] a couple of times will cycle through the windows to show what is in the registers.
    - Typing `tui reg` will give some options to see specific registers.
      - For example, `tui reg float` shows the floating registers.
      - For example, `tui reg general` displays the general purpose registers.
 - Hit [Ctrl+x 1] to go back to the first view and see your source code.
   - Typing in some commands like 'layout src' will bring you back to your source view.
     - Typing in 'layout asm' will show you the assembly.
- More: https://sourceware.org/gdb/onlinedocs/gdb/TUI-Commands.html#TUI-Commands
- More: https://sourceware.org/gdb/onlinedocs/gdb/TUI-Keys.html#TUI-Keys
- More resources on GDB TUI: https://sourceware.org/gdb/onlinedocs/gdb/TUI.html
  
## (Optional) GDB Python	

From the Greg Law Video, he demonstrates using an the Python programming langauge within the GDB Tool. Python is a general purpose scripting langauge--perhaps you have even used it! What is neat about Python is that the languages interpreter can be embedded into other tools (and even other programming languages!) as has been shown with GDB.

Here are some of the Python commands written out for your convenience. 
	
- Try the following within GDB:
  - Type: `python print("hello gdb")`
  - Type: `python import os`
  - Type: `python print("my pid is %d" % os.getpid()) # pid = process id`
  - If you have inserted any breakpoints:
    - (Create one with `b main`)
    - Type: `python print(gdb.breakpoints())`
    - Type: `python print(gdb.breakpoints()[0].location)`
    - With Python, you can even create breakpoints!
      - `python gdb.Breakpoint('7')`
    
- Finally typing in `quit` will exit gdb when you are done.

## Small exercise

Run gdb on the program *prog1* that is included in this repository.

It has been compiled with debugging symbols(*-g*) so you may investigate and view the source. Answer the following questions below.

## **TODO (Add your answers here)**

In a brief sentence or two.

1. What was the bug?            Segmentation Fault. Attempts to access a memory that is not allowed. 
2. What line did the bug occur? Line 15.
3. What is the fix for the bug? When initialzing, allocates the spaces to store the values. 

## Aside: Core dump

In the Greg Law video, he begins to investigate a Core dump file. What exactly is a coredump?

Read here: https://wiki.archlinux.org/index.php/Core_dump

# Rubric

- 40% Part 1 - Does your function.s work.
  - 10% for a correct output.
  - 10% for a correct add function
  - 10% for a correct subtract function
  - 10% for structure of program (no weird formatting, no wasteful instructions)
- 50% Part 2 - Cycle Count Tool
  - 10% Did you modify the comments and answer the questions in barebones.s
  - 30% Does your cycle count tool work? 
  	- i.e. no memory leaks
	- Number of instructions are correctly counted
	- *Some* approximation of the cycles is given.
  - 10% Did you answer the questions on the static analysis and dynamic analysis?
- 10% Part 3 - GDB
  - Did you modify the README with the correct answers to what the bug was in prog1?

# Resources to help

- A full 90+ minutes of GDB debugging: https://www.youtube.com/watch?v=713ay4bZUrw

# Feedback Loop

(An optional task that will reinforce your learning throughout the semester)

- Continue using the Compiler Explorer as you write your C code. https://godbolt.org

