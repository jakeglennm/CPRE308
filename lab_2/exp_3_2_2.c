#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
fork();
fork();
usleep(1);
printf("Process %d’s parent process ID is %d\n", getpid(), getppid());
return 0;
}

