#include "functions.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

//Hostname
void printHostname(){
	FILE* hostnameFile;
	char buffer[50];
	hostnameFile = fopen("/proc/sys/kernel/hostname","r");

	if(hostnameFile == NULL){
		printf("No hostname file found!");
		fclose(hostnameFile);
		return;
	}

   	char *hostname = fgets(buffer, 50, hostnameFile);
   	printf("\n Hostname: %s ",hostname);
	
	fclose(hostnameFile);

	return;
}

//Fecha y hora actual
void printDate(){
	time_t currentTime;
	currentTime = time(NULL);
	printf("\n Fecha y hora actuales: \n %s \n", ctime(&currentTime));

	return;
}

// Tipo y modelo de CPU
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
   		char *line = fgets(buffer, 60, cpuInfoFile);
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

//Versión del kernel
void printKernelVersion(){
	FILE* kernelFile;
	char buffer[100];
	kernelFile = fopen("/proc/version","r");

	if(kernelFile == NULL){
		printf("No kernel info file found!");
		fclose(kernelFile);
		return;
	}

	puts("\n Versión del kernel: ");
	char *line = fgets(buffer, 100, kernelFile);

	char *kernelVersion;
	const char delim[2] = "(";
	
	if((kernelVersion = strstr(line, "Linux version"))!= NULL){
		printf("   %s",strtok(kernelVersion, delim));
	}
	puts("\n");

	fclose(kernelFile);
	return;
}

//Cantidad de tiempo transcurrido desde que se 
//inició el sistema operativo (formato ddD hh:mm:ss)
void printUpTime(){
	FILE* upTimeFile;
	char buffer[50];
	upTimeFile = fopen("/proc/uptime","r");

	if(upTimeFile == NULL){
		printf("No up time info file found!");
		fclose(upTimeFile);
		return;
	}

	puts("\n Tiempo transcurrido desde que se inicio el sistema: ");
	char *upTime = fgets(buffer, 50, upTimeFile);
	const char delim[2] = ".";
	
	if((upTime = strtok(upTime, delim))!= NULL){
		int seconds = atoi(upTime);
		int minutes = 0;
		while(seconds > 59){
			minutes +=1;
			seconds -= 60;
		}

		int hours = 0;
		while(minutes > 59){
			hours +=1;
			minutes -= 60;
		}

		int days = 0;
		while(hours > 23){
			days += 1;
			hours -= 24;

		}		

		printf("   %02iD %02i:%02i:%02i",days,hours,minutes,seconds);
	}
	puts("\n");

	fclose(upTimeFile);
	return;
}

//Cantidad de sistemas de archivo soportados por el kernel
void printFileSystems(){
	FILE* fileSystemsFile;
	char buffer[50];
	fileSystemsFile = fopen("/proc/filesystems","r");

	if(fileSystemsFile == NULL){
		printf("No file systems file found!");
		fclose(fileSystemsFile);
		return;
	}

	int contador = 0;
	while(!feof(fileSystemsFile)) {
   		char *fileSystem = fgets(buffer, 50, fileSystemsFile);
		if(fileSystem==NULL) { break; }
		contador ++;
	}
	printf("\n Cantidad de sistemas de archivos soportados: %i", contador);
	puts("\n");
	fclose(fileSystemsFile);

	return;
}

void cpuTime(){
	FILE* statFile;
	char buffer[50];
	statFile = fopen("/proc/stat","r");

	if(statFile==NULL){
		printf("No file stat file found");
		fclose(statFile);
		return;
	}
	char *stat = fgets(buffer,50,statFile);
	int n=0;
	char *token= strtok(stat," ");
	while(token){
		if(n==1){
			printf("%s","Tiempo de CPU utilizado para usuarios: ");
			puts(token);}
		if(n==3){
			printf("%s","Tiempo de CPU utilizado para sistema: ");
			puts(token);}
		if(n==4){
			printf("%s","Tiempo de CPU utilizado para procesos idle: ");
			puts(token);}
	    token = strtok(NULL, " ");
	    n++;	
	}

	while(!feof(statFile)) {
		char *line = fgets(buffer, 50, statFile);
		if(line==NULL) { break; }

		char *contexto;
		if((contexto = strstr(line, "ctxt"))!= NULL){
			token=strtok(contexto," ");
			token= strtok(NULL, " ");
			printf("%s", "Cantidad de cambios de contexto: " );
			printf("%s", token); // corregir salto de linea
		}
	}
}

void initTime(void){

	FILE* upTimeFile;
	char buffer[50];
	upTimeFile = fopen("/proc/uptime","r");

	if(upTimeFile == NULL){
		printf("No up time info file found!");
		fclose(upTimeFile);
		return;
	}

	char *upTime = fgets(buffer, 50, upTimeFile);
	const char delim[2] = ".";
	
	if((upTime = strtok(upTime, delim))!= NULL){
		int seconds = atoi(upTime);

		time_t currentTime;
		currentTime = time(NULL);

		currentTime -= seconds;
		printf("\n La fecha de inicio del sistema es: \n      %s \n", ctime(&currentTime));
	}

	fclose(upTimeFile);

	return;
}

void procCreated(void){
	FILE* statFile;
	char buffer[50];
	statFile = fopen("/proc/stat","r");

	if(statFile==NULL){
		printf("No file stat file found");
		fclose(statFile);
		return;
	}
	while(!feof(statFile)) {
		char *line = fgets(buffer, 50, statFile);
		if(line==NULL) {
			break;
		}

		char *procesos;
		char *token;
		if((procesos = strstr(line, "processes"))!= NULL){
			token=strtok(procesos," ");
			token= strtok(NULL, " ");
			printf("%s", "Cantidad de procesos creados desde el inicio del sistema: " );
			printf("%s", token); // corregir salto de linea
		}
	}
}

void memStat(void){
	FILE* statMemory;
	char buffer[50];
	statMemory = fopen("/proc/meminfo","r");

	if(statMemory==NULL){
		printf("No file meminfo file found");
		fclose(statMemory);
		return;
	}
	while(!feof(statMemory)) {
		char *line = fgets(buffer, 50, statMemory);
		if(line==NULL) {
			break;
		}
		char *memtotal;
		if((memtotal = strstr(line, "MemTotal:"))!= NULL){
			printf("%s", memtotal );
		}

		char *memdispon;
		if((memdispon = strstr(line, "MemAvailable:"))!= NULL){
			printf("%s", memdispon );
			return;
		}		
	}

}

