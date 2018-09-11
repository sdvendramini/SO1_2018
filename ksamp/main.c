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
	
	const char *optionS = "-s";	

	if(argc > 1 ){
		if(strcmp(argv[1], optionS)==0){
			cpuTime();
		}
	}
	
	return 0;
	
}