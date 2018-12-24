# Process API

In today's lab, we are going to explore the process API to get familiar with launching processes from within our program. Provided in this lab are several code examples showcasing several ways to launch and control processses. 

# Part 1 - fork

Remember that when we use fork(), we are creating a child processes that is identical to the parent process. The child process gets a copy of everything that the parent had, but the memory is distinct, such that modificiations in either the parent or child do not effect each other.

Let us go ahead and try a simple example with fork.

## example1.c

The following program is our version of a "hello world" to the fork command.

```c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

	pid_t pid;
	int x = 1;

	pid = fork();

	if(pid==0){
		printf("child: x=%d\n",++x);
		return 0;	
	}

	// Parent
	printf("parent: x=%d\n", --x);

	return 0;
}

```

* Save, compile, and run the following program: `gcc example1.c -o example1`

Let's try another example this time:

## example2.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

	pid_t pid;
	int x = 1;

	pid = fork();

	if(pid==0){
		printf("Terminating Child, PID= x=%d\n",getpid());
		exit(0);	
	}else{
    	    // Run the parrent
	    printf("Running parent forever(pretend I am a server): pid=%d\n",getpid());
    	    while(1){
    	    }
  	}

	return 0;
}
```

* Save, compile, and run the following program: `gcc example2.c -o example2`

What happens when you compile and run this code? (Run with `./example2 &` the ampersand returns control back to shell.

You can type `ps` into the terminal. You will notice that one of the processes is labeled <defunct>, and that id will actually match our childs pid. What happened here, is that we have not reclaimed (or reaped) our children. Our child is said to be a zombie process, in that it is occupying and using resources, but not doing any useful work.
  
Let's get rid of our processes now. Type `kill somenumber` where somenumber is the pid of your parent and child process (Note that killing the parent should kill the child process as well).
  
Now what if we flip the scenario where our child runs forever?

## example3.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

	pid_t pid;
	int x = 1;

	pid = fork();

    if(pid==0){
    	printf("Running child forever now pid=%d\n",getpid());
    	while(1){
    	}
    }else{
	// Run the parrent
	printf("Terminating parent pid=%d\n",getpid());
	exit(0);
    }

	return 0;
}
```

* Save, compile, and run the following program: `gcc example3.c -o example3`

We will have the same problem, and we need to run the `ps` command again(to see which processes are running), and then the `kill #` command.

## Synchronization

Now this seems like a little problem, so what is one potential solution to fix this problem?

The answer is to use a synchronization function called `wait`. `int wait(int *child_status)` will make the parent wait to execute after one or more child process(es) has finished.

## example4.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){

    int child_status;

    if(fork()==0){
        printf("Child runs!\n");
        exit(0); // and exits properly
    }else{
        printf("Hello from parent\n");
        wait(&child_status);

        // If we want to do something with the child_status here is an example.
        // Typically we can wait(NULL), but within our parent we may want
        // to capture how the child exited(maybe it exited with some error code).
        // e.g. change 'exit(0)' to 'exit(5)' in the block of code executed by
        // the child.
        if(WEXITSTATUS(child_status)>=0){
            printf("Child exited with the following child_status %d\n",WEXITSTATUS(child_status));
        }
        printf("Child always is terminated by this point--parent resuming\n");
    }

    printf("This always prints last\n");

    // It is important to note that our parent should always wait for all
    // of its child processes to exit before proceeding.
    // If the parent ends first(i.e. forgetting to call wait), the
    // child process is 'orphaned' and becomes a zombie process that
    // cannot be otherwise terminated.

    return 0;
}
```

* Save, compile, and run the following program: `gcc example4.c -o example4`
* Take a moment to read about orphan and zombie processes here: http://linuxg.net/what-are-zombie-and-orphan-processes-and-how-to-kill-them/
	* (The important part being how to find and kill any zombie and orphan processes)

## execve

In order to execute other programs (i.e. a more specific process), we have the execve command.

It looks like the following:

`int execve(char* filename, char* argv[], char*envp[])`

- filename: This is the script or file we are going to execute (i.e. this is equivalent to typing it in the shell)
- argv: This is our argument list (which we are familiar with). argv[0] = filename.
- envp: These are any specific environment variables we want to set.
  - More information can be found here: [https://en.wikipedia.org/wiki/Environment_variable]

Let's try a simple example with 'ls'

## example5.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

	char* myargv[16];
	myargv[0]="/bin/ls";
	myargv[1]="-F";
	myargv[2]=NULL; // Terminate the argument list
	
	if(fork()==0){
		// Executes command from child then terminates our process
		execve(myargv[0],myargv,NULL);
		printf("Child: Should never get here\n");
		exit(1);
	}else{
		wait(NULL); // handy synchronization function again!
		printf("This always prints last\n");
	}
	
	return 0;
}
```

* Save, compile, and run the following program: `gcc example5.c -o example5`
* Go ahead and modify the above code and try to run some other processes like 'cat'.
* Will the code work if I change `myargv[0]="ls"`. Why do you think this is?
	* https://phoenixts.com/blog/environment-variables-in-linux/ 
	* https://www.cyberciti.biz/faq/linux-list-all-environment-variables-env-command/


# Part 2 - Terminal Programs

To get some practice with understand processes, run the following commands: 

- proc/
- top
- ps
- kill (yes, I know it is a rather aggressive command name--yikes!)

It will be further useful to read the `man` pages for each of the commands.

# Lab Deliverable

- Commit the source code for the 5 examples (example1.c example2.c exmample3.c example4.c example5.c).
- Write a small program(myprogram.c) using fork and/or execve to execute a series of at least 3 other commands/programs.
  - You are welcome to be as creative as you like!

# More resources to help

- https://www.networkworld.com/article/2693548/unix-viewing-your-processes-through-the-eyes-of-proc.html

# Going Further

- Investigate the different command shells: https://en.wikipedia.org/wiki/Comparison_of_command_shells
