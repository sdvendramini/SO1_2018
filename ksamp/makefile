CFLAGS = -Wall -std=gnu99 -pedantic  #puede ser gnu11
ksamp: main.o functions.o
	gcc -o ksamp main.o functions.o 
main.o: main.c 
	gcc $(CFLAGS) -c main.c
functions.o: functions.c functions.h
	gcc $(CFLAGS) -c functions.c 
clean:
	rm -f *.o ksamp
static:
	cppcheck functions.c main.c