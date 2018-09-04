ksamp: main.o functions.o
	gcc $(CFLAGS) -o ksamp main.o functions.o
main.o: main.c 
	gcc $(CFLAGS) -c main.c
functions.o: functions.c functions.h
	gcc $(CFLAGS) -c functions.c
clean:
	rm -f *.o ksamp