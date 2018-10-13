CFLAGS = -Wall -std=gnu99 -pedantic

baash : baash.o funciones.o
	gcc -o baash baash.o funciones.o

baash.o : baash.c
	gcc $(CFLAGS) -c baash.c

funciones.o : funciones.c funciones.h
	gcc $(CFLAGS) -c funciones.c

clean :
	rm -f *.o baash
