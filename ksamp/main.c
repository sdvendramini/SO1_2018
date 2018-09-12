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
	const char *optionL = "-l";

	if(argc > 1 ){  //https://poesiabinaria.net/2015/11/como-gestionar-los-parametros-de-nuestros-programas-con-getopt-en-c/
		if(strcmp(argv[1], optionS)==0){
			cpuTime();
			initTime();
			procCreated();
		}
		if(strcmp(argv[1], optionL)==0){
			cpuTime();
			initTime();
			procCreated();
			memStat();
		}
	}
	
	return 0;
	
}