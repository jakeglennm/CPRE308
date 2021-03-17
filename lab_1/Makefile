output: lab1.o message.o
	gcc lab1.o message.o -o output

lab1.o: lab1.c
	gcc -c lab1.c

message.o: message.c message.h
	gcc -c message.c

clean:
	rm *.o output
