#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

int main(int argc, char * argv[]) {
// Set the prompt
  char user_prompt[20] = "308sh"; //default prompt is "308sh"
char user_input;
 if(argc > 1){ //check if the user entered more than one argument
   if((strcmp(argv[1], "-p")==0)){ //if user specifies "-p", use what they enter immediately after
     strcpy(user_prompt,argv[2]);
   }
 }
// User input infinite loop
while(1) {
         printf("%s> ",user_prompt); //print out user_prompt at the start of each new command line

	 char user_input[50];
	 char *home = getenv("HOME"); //this is used for changing directories on line 56
	 // Get user input
       	 fgets(user_input,50,stdin); // get the user input and store into user_input
	 int length = strlen(user_input); //get the length of user_input
	 if(length > 1 && user_input[length-1] == '\n') user_input[length-1] = '\0'; //when using fgets, make sure you get rid of the '\n' so you can check built-in commands easier


	 	 // ---------- Builtin Commands -------------------------------


		   if (strcmp(user_input, "exit") == 0) { //if user enters "exit" then exit this shell program
	 	 	 return 0;
	 	 } else if (strcmp(user_input, "pid") == 0) { //if user enters "pid" print out the process id
	 	 	 printf("Shell Process ID: %d\n", getpid());
	 	 } else if (strcmp(user_input, "ppid") == 0) { //if user enters "ppid" print out the parent id
		         printf("Shell Parent Process ID: %d\n", getppid());
		 } else if (strcmp(user_input, "pwd") == 0) { //if user enters "pwd" then get the current working directory
		         char dir[256];
			 if (getcwd(dir, sizeof(dir)) != NULL) {
			   printf("%s\n", dir);
			 }

		 }else if (strncmp(user_input, "cd",2)==0) { //if the user enteres "cd" get the specified directory using strtok, otherwise change directory to HOME
			 char *ptr = strtok(user_input, " ");
			 char *argv[3];
			 int i = 0;

			  while(ptr!=NULL) {
			   argv[i] = ptr;
			    i++;
			   ptr = strtok(NULL," ");
			 }
			 argv[i] = '\0'; //store NULL to determine end of argv
			 if(argv[1]!=NULL) {
			   chdir(argv[1]);
			 } else {
			     chdir(home);
			 }
                 } else {
	 	 	 // ---------- Non-Builtin Commands--------------------------
	 	 	 nonBuiltIn(user_input); //use nonBuiltIn to run non-built in prorgrams using the execvp call
	 	 }
}


return 0;
}
// ----------------------------------- Helper Functions ----------------------------------
int nonBuiltIn(char input[]) {
  //break input[] passed from the while loop at spaces and store into an argv[] using strtok
  int status;
  char *ptr = strtok(input, " ");
  char *argv[5];
  int i = 0;

  while(ptr!=NULL) {
    argv[i] = ptr;
    i++;
    ptr = strtok(NULL," ");
}
  argv[i] = '\0'; //store NULL to determine end of argv

  //create a child using a pid_t variable and fork() call
  pid_t pid; //remember pid_t is just an int
  pid = fork();
  if(pid == 0) { //child process
    printf("[%d] %s\n",getpid(),argv[0]);
    execvp(argv[0],argv);
    //anything ran past this line means that exec failed and returned
    printf("Requested command failed\n");
    kill (getpid(), SIGTERM); //kill this child process if requested command fails
  }
  else { //parent process
    wait(&status);
    if(WIFEXITED(status)){
      printf("%s Exit %d\n",argv[0],WEXITSTATUS(status)); //print out the command ran and the exit status
  }
}

}
