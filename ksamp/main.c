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
	
	return 0;
	
}