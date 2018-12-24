// Type in and try example1.c

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

