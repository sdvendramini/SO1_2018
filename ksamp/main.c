#include <stdio.h>
#include "functions.h"

int main()
{
	// parsear /proc/sys/kernel/hostname 
	printHostname();
	printDate();
	printCpuInfo();
	
	return 0;
}


