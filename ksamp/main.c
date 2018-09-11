#include <stdio.h>
#include <string.h>
#include "functions.h"

int main( int argc, char *argv[])
{	
	
	printHostname();
	printDate();
	printCpuInfo();
	printKernelVersion();
	printUpTime();
	printFileSystems();
	
	const char optionS[2] = "-s";	

	if(argc > 1 ){		
		if(strcmp(argv[1], optionS)==0){
			//reemplazar este printf por el llamado a las funciones de la parte C
			printf("%s\n","Opcion ingresada : -s ");
		}
	}
	return 0;
	
}