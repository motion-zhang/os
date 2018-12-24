#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#define COMMAND_SIZE 80
#define ARGUMENT_SIZE 20

// A linked list structure 
struct command_list {
   char *arg[ARGUMENT_SIZE];  
   struct command_list *next;
};

struct command {
   struct command_list *first;
};

// Create a signal handler
void sigint_handler(int sig){
     write(1, "Terminating through singal handler\n", 35);
     exit(0);
}

void shell_cd(char *path) {
   if (chdir(path) < 0) {
     printf("No such file or directory\n");
   }
}

// Read the input line and check if the line has the correct length
char* shell_read_line() {

    int pos = 0;
    char *line = malloc(sizeof(char) * COMMAND_SIZE);
    char c;

    while (pos <= COMMAND_SIZE) {
        c = getchar();
        if (c == EOF || c == '\n') {
            line[pos] = '\0';
            return line;
        } else {
            line[pos] = c;
        }
        pos++;
        if (pos >= COMMAND_SIZE) {
           printf("length greater than 80\n");
           exit(0);
        }
    }
}

struct command* parse_to_command(char *line){
    struct command* command = (struct command*)malloc(sizeof(struct command));
    struct command_list* current;
    struct command_list* new;
    command->first = (struct command_list*)malloc(sizeof(struct command_list));
    current = command->first;
    char* copy = line;

    // parse the line into a command link list
    // the line taken in might contain "|"
    // Seprate it into different arguments
    char* temp;
    temp = strsep(&copy, "|");
    int i = 0;
    while (i < ARGUMENT_SIZE && (current->arg[i] =  strtok(temp, " ")) != NULL) {
        temp = NULL;
        i++;
    }
    current->arg[i] = NULL;
    int j = 0;
    while((temp = strsep(&copy, "|")) != NULL) {
        new = (struct command_list*) malloc(sizeof(struct command_list));
        current->next = new;
        while (j < ARGUMENT_SIZE && (current->arg[j] = strtok(temp, " ")) != NULL) {
            temp = NULL;
            j++;
        }
        current->arg[i] = NULL;
    }
    current->next = NULL;
    return command;
}


// execute the command by firstly checking the pipe
int execute_command(struct command *command) {
    int status = 1;
    struct command_list* first;
    struct command_list* next;

    first = command->first;
    status = execute_command_list(first,0);
    //check if there is a pipe
    if (first->next != NULL) {
       next = first->next;
       status = execute_command_list(next, 0);
    }

    return status;


}

int execute_command_list(struct command_list *clist) {
    int status = 1;
    int index = 0;
  //  int fork = -1;
   
    if (strcmp(clist->arg[0], "cd") == 0) {
       shell_cd(clist->arg[1]);
       index = 1;
    }
    else  if (strcmp(clist->arg[0], "ls") == 0) {
       index = 3;
    }
    else if (strcmp(clist->arg[0], "exit") == 0) {
       printf("mini-shell terminated\n");
       index = 0;
    }
    else if (strcmp(clist->arg[0], "help") == 0) {
       index = 1;
    }
    else if (strcmp(clist->arg[0], "history") == 0) {
       index = 2;
    }
    else {
       printf("Command not found\n");
       index = -1;
    }

    if (index == 0) {
      return -1;
    }
    else if (index == 2) {
      return 2;
    }
    else if (index = 3) { 
       
      char* myargv[16];
      myargv[0]="/bin/ls";
      myargv[1]="-F"; 
      myargv[2]=NULL;
      
      if (fork() != 0) {
        wait(NULL);
      }
      else {
        execve(myargv[0],myargv,NULL);
        exit(1);
      } 
    }
    else {
      return 1;
    }
}


int main(int argc, char **argv) {

    char *line;                       // every line user typed in
    struct command *command;          // command to store the command
    struct command_list *current;      // command_list store the current command you typed in
    char history[1024] = "";          // Array store all the history of commands
    int i = 0;
    int j = 0;

    int status = 1;

    signal(SIGINT, sigint_handler);

    while (status >= 0) {


      // print "mini-shell"    
      printf("mini-shell> ");
      // read one line from terminal
      line = shell_read_line();
      // store this line of command into history
      strcat(history, line);
      strcat(history, "\n");
      // parse the line into command structure
      command = parse_to_command(line);
      // Output the history if the current command you typed in is "history"
      // Command execution not implemented yet. It is just manually ouputting
      status = execute_command(command);
      if (status == 2) printf("%s", history);


    }
    return 0;
}


