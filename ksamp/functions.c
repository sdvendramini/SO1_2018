#include "functions.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

/* Imprime en pantalla el Hostname del dispositivo*/
void printHostname(){
	FILE* hostnameFile;
	char buffer[50];
	char *hostname;
	hostnameFile = fopen("/proc/sys/kernel/hostname","r");

	if(hostnameFile == NULL){
		printf("No hostname file found!");
		fclose(hostnameFile);
		return;
	}

   	hostname = fgets(buffer, 50, hostnameFile);
   	printf("\n Hostname: %s ",hostname);
	fclose(hostnameFile);
	return;
}

/*Imprime en pantalla fecha y hora actual*/
void printDate(){
	time_t currentTime;
	currentTime = time(NULL);
	printf("\n Fecha y hora actuales: \n %s \n", ctime(&currentTime));
	return;
}

/**
*	Imprime en pantalla tipo y modelo de CPU
*/
void printCpuInfo(void){
	FILE* cpuInfoFile;
	char buffer[50];
	cpuInfoFile = fopen("/proc/cpuinfo","r");

	if(cpuInfoFile == NULL){
		printf("No cpuinfo file found!");
		fclose(cpuInfoFile);
		return;
	}

	puts("Informacion del procesador: ");
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
			break;
		}
	}	
	fclose(cpuInfoFile);
	return;
}

/**
*	Imprime en pantalla la versión del kernel
*/
void printKernelVersion(){
	FILE* kernelFile;
	char buffer[100];
	kernelFile = fopen("/proc/version","r");

	if(kernelFile == NULL){
		printf("No kernel info file found!");
		fclose(kernelFile);
		return;
	}

	puts("Versión del kernel: ");
	char *line = fgets(buffer, 100, kernelFile);

	char *kernelVersion;
	const char delim[2] = "(";
	
	if((kernelVersion = strstr(line, "Linux version"))!= NULL){
		printf("   %s\n",strtok(kernelVersion, delim));
	}
	fclose(kernelFile);
	return;
}

/**
* Cantidad de tiempo transcurrido desde que se 
* inició el sistema operativo (formato ddD hh:mm:ss)
*/
void printUpTime(){
	FILE* upTimeFile;
	char buffer[50];
	upTimeFile = fopen("/proc/uptime","r");

	if(upTimeFile == NULL){
		printf("No up time info file found!");
		fclose(upTimeFile);
		return;
	}

	puts("Tiempo transcurrido desde que se inicio el sistema: ");
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

		printf("   %02iD %02i:%02i:%02i\n",days,hours,minutes,seconds);
	}
	fclose(upTimeFile);
	return;
}

/**
*Imprime la cantidad de sistemas de archivo soportados por el kernel
*/
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
	printf("Cantidad de sistemas de archivos soportados: %i\n", contador);
	fclose(fileSystemsFile);
	return;
}

/**
*	Imprime en pantalla el tiempo del cpu usado en usuarios, sistema y para procesos idle. Asi como
*	tambien la cantidad de cambios de contexto.
*/
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
			printf("%s", token);
		}
	}
}

/**
*	Imprime en pantalla la fecha de inicio del sistema
*/
void initTime(void){

	FILE* upTimeFile;
	char buffer[50];
	upTimeFile = fopen("/proc/uptime","r");

	if(upTimeFile == NULL){
		printf("No uptime info file found!");
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
		printf("La fecha de inicio del sistema es: %s", ctime(&currentTime));
	}
	fclose(upTimeFile);
	return;
}

/**
*	Imprime la cantidad de procesos creados al momento de ejecucion.
*/
void procCreated(void){
	FILE* statFile;
	char buffer[50];
	statFile = fopen("/proc/stat","r");

	if(statFile==NULL){
		printf("No stat file found");
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
			printf("Cantidad de procesos creados desde el inicio del sistema: " );
			printf("%s", token); // corregir salto de linea
		}
	}
}

/**
*	Imprime en pantalla los valores de la memoria total del dispositivo y la memoria disponible en el momento de ejecucion.
*/
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
		if((memtotal = strstr(line, "MemTotal:"))!= NULL){ //Busca linea por linea el valor de MemTotal
			printf("%s", memtotal );
		}

		char *memdispon;
		if((memdispon = strstr(line, "MemAvailable:"))!= NULL){ //Busca linea por linea el valor de MemAvailable
			printf("%s", memdispon );
			return;
		}		
	}

}

/**
 * Imprime la cantidad de pedidos a disco. Abarca las lecturas y las escrituras a disco.
 */
void peticionesHDD(){
	FILE* pedidosHDD =fopen("/proc/diskstats", "r");
	char buffer[256];
	char* matched;
	unsigned int lecturas, escrituras, pedidos;
	
	if(pedidosHDD==NULL){
		printf("No file diskstats found");
		fclose(pedidosHDD);
		return;
	}
	while(!feof(pedidosHDD)) {
		char* line=fgets(buffer, 256, pedidosHDD);
		if(line==NULL) {
			break;
		}
		if((matched= strstr(line,"sda"))!=NULL){ //busca la linea que contenga el caracter sda, y luego se suman las lecturas y las escrituras totales.
			break;
		}
	}
	sscanf(matched, "sda %u", &lecturas);
	sscanf(matched, "sda %*u %*u %*u %*u %u", &escrituras);
	pedidos = escrituras + lecturas;
	printf("Cantidad de pedidos al disco: %u\n", pedidos);	
	return;
}

/**
 * Imprime el promedio de carga en un minuto
 */
void loadAvg(){
	FILE* promCarga =fopen("/proc/loadavg", "r");	
	float carga;
	
	if(promCarga==NULL){
		printf("No file loadavg found");
		fclose(promCarga);
		return;
	}
	fscanf(promCarga, "%f", &carga); //Extrae de la primera columna el valor en punto flotante del promedio en un minuto.
	printf("Promedio de carga de un minuto: %f\n", carga);
	fclose(promCarga);
	return;
}

void parteB(){
	printHostname();
	printDate();
	printf("----------Información del Equipo----------\n");
	printCpuInfo();
	printKernelVersion();
	printUpTime();
	printFileSystems();
	printf("------------------------------------------\n");
}

void parteC(){
	cpuTime();
	initTime();
	procCreated();
	printf("------------------------------------------\n");
}

void parteD(){
	peticionesHDD();
	memStat();
	loadAvg();
	printf("\n");
}