#include "functions.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

void printHostname(){
	FILE* hostnameFile;
	char buffer[50];
	hostnameFile = fopen("/proc/sys/kernel/hostname","r");

	if(hostnameFile == NULL){
		printf("No hostname file found!");
		fclose(hostnameFile);
		return;
	}

	while(!feof(hostnameFile)) {
   		char *hostname = fgets(buffer, 50, hostnameFile);
		if(hostname==NULL) { break; }
   		printf("\n Hostname: %s ",hostname);
	}
	
	fclose(hostnameFile);

	return;
}

void printDate(){
	time_t currentTime;
	currentTime = time(NULL);
	printf("\n Fecha y hora actuales: \n %s \n", ctime(&currentTime));

	return;
}

void printCpuInfo(void){
	FILE* cpuInfoFile;
	char buffer[50];
	cpuInfoFile = fopen("/proc/cpuinfo","r");

	if(cpuInfoFile == NULL){
		printf("No cpuinfo file found!");
		fclose(cpuInfoFile);
		return;
	}

	puts("\n Informacion del procesador: ");
	while(!feof(cpuInfoFile)) {
   		char *line = fgets(buffer, 50, cpuInfoFile);
		if(line==NULL) { break; }

		char *cpuType;
		if((cpuType = strstr(line, "vendor_id"))!= NULL){
			printf("   %s",cpuType);
		}
		char *cpuModel;
		if((cpuModel = strstr(line, "model name"))!= NULL){
			printf("   %s",cpuModel);
			break;		//el break debe quedar en el ultimo parseo para que no se repita con cada nucleo.
		}
	}
	puts("\n");

	
	fclose(cpuInfoFile);

	return;
}