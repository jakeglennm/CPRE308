#include <stdio.h>
#include <pthread.h>

void * thread1(void * tid) {
	sleep(5);	
	printf("Hello from thread 1\n");
	//pthread_exit(NULL);
}

void * thread2(void * tid) {
	sleep(5);	
	printf("Hello from thread 2\n");
	//pthread_exit(NULL);
}

int main(int argc, char * argv[]) {
	pthread_t t1;
	pthread_t t2;
	
	pthread_create(&t1,NULL,thread1,NULL); //the thread runs the function thread1
	pthread_create(&t2,NULL,thread2,NULL); //the thread runs the function thread2

	pthread_join(t1,NULL); //main thread will wait until t1 terminates
	pthread_join(t2,NULL); //main thread will wait until t2 terminates

	printf("Hello from the main thread\n");
}
