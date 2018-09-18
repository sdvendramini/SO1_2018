#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include "functions.h"

int main( int argc, char *argv[])
{	

	printHostname();
	printDate();
	printCpuInfo();
	printKernelVersion();
	printUpTime();
	printFileSystems();	

	int c;
	int interval;
	int duration;
	/* variables globales de getopt */
	extern char* optarg;
	extern int optind;
	extern int optopt;
	extern int opterr;
	opterr = 0;

	while ((c = getopt (argc, argv, "sl")) != -1)
    	switch (c){
    	case 's':
    		cpuTime();
			initTime();
			procCreated();
        	break;
      	case 'l':      		
	      	
	      	duration = atoi(argv[optind]);
	      	interval = atoi(argv[++optind]);
	    	cpuTime();
			initTime();
			procCreated();			
			peticionesHDD();
			memStat();
			loadAvg();			
			do
			{
   				printf("Espere %i segundos.\n", duration);				
   				sleep(duration);				
				peticionesHDD();
   				memStat();
				loadAvg();			
				interval -= duration;
			} while ( interval > 0);
					   		   
        	break;
	}
	return 0;
	
}
