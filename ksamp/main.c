#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include "functions.h"

int main( int argc, char *argv[])
{	
	int c;
	int interval;
	int duration;
	/* variables globales de getopt */
	extern char* optarg;
	extern int optind;
	extern int optopt;
	extern int opterr;
	opterr = 0;

	parteB();
	while ((c = getopt (argc, argv, "sl")) != -1){
    	switch (c){
    	case 's':
    		parteC();
        	break;
      	case 'l':      		
	      	
	      	duration = atoi(argv[optind]);
	      	interval = atoi(argv[++optind]);
	    	parteC();
	    	parteD();
			do
			{
   				printf("[Espere %i segundos]\n", duration);				
   				sleep(duration);				
				parteD();			
				interval -= duration;
			} while ( interval > 0);		   		   
        	break;
        default:
        	printf("Las opciones posibles del programa son -s y -l con tiempos de duracion e intervalo.");
		}
	}
	return 0;
	
}
