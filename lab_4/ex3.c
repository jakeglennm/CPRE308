#include <signal.h>
#include <stdio.h>
void my_routine( );
int main() {
signal(SIGFPE, my_routine);
printf("Entering main\n");
/* the division needs to use a variable or gcc will not compile the instruction */
int a = 4;
printf("try to divide by zero...\n");
a = a/0;
}
void my_routine( ) {
printf("Caught a SIGFPE\n");
exit(0);
}

