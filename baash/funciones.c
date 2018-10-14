#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "funciones.h"

void prompt () {
	char hostname[25];
	gethostname(hostname, 25);

	printf("[%s@%s:%s]$ ", getlogin(), hostname, getcwd(NULL,300)); //hay que comprobar si el path no devuelve un array mayor a los 300 que le damos
}

void parsePath (char* f[]) {
	char* var = getenv("PATH");
	f[0] = strtok(var, ":");
	int i = 1;
	while (f[i-1] != NULL) {
		f[i] = strtok (NULL, ":");
		//printf("%s\n",f[i-1]);
		i++;
	}
}

int leerCmd (char* argv[], char* input) {

	argv[0] = strtok(input, " \n");
	//printf("%s\n", input);

	int i = 1;
	while (argv[i-1] != NULL) {
		argv[i] = strtok (NULL, " \n");
		i++;
	}
	return --i;
}

void buscarCmd(char* argv, char* paths[], char* cmdFile) {
	int result;
	char dirActual[300];
	char* archivo;
	//printf("argv:%s\n",argv);

	if (argv[0] == '/' || (argv[0] == '.' && argv[1] == '.' && argv[2] == '/')) {
		char* dir;
		char* nextDir;

		dir = strtok(argv, "/");
		printf("argv:%s\n", argv);
		//printf("Dentro de  ../ o /, esto es dir:%s\n",dir );
		nextDir = strtok(NULL, "/");
		//printf("Esto es nextdir:%s\n",nextDir);
		//printf("Esto es argv[0]:%c\n",argv[0]);
		if (argv[0] == '/'){
			strcpy (dirActual, "/");
			strcat(dirActual, dir);
		}else{
			strcpy (dirActual, "..");
		}

		//printf("Esto es dirActual:%s\n",dirActual );

		while (nextDir != NULL) {
			dir = nextDir;
			nextDir = strtok(NULL, "/");
			strcat(dirActual, "/");
			if (nextDir != NULL)
				strcat(dirActual, dir);
		}
		archivo = dir;
	} 

	else if (argv[0] == '.' && argv[1] == '/') {
		getcwd(dirActual, 300);
		strcat(dirActual, "/");
		archivo = strtok(argv, "/");
		archivo = strtok(NULL, "/");
	}

	else {
		char aux[150];

		int i = 0;
		while (paths[i] != NULL) {
			strcpy(aux, paths[i]);
			strcat(aux, "/");
			strcat(aux, argv);

			result = access(aux, F_OK);

			if (!result) {
				strcpy(cmdFile, aux);
				return;
			}
			i++;
		}
		cmdFile[0] = 'X';
		return;
	}
	strcat(dirActual, archivo);
	//printf("%s\n",dirActual );
	result = access(dirActual, F_OK);
	//printf("%d\n",!result);
	if (!result){
		strcpy(cmdFile, dirActual);
	}
	else
		cmdFile[0] = 'X';
}

void crearProc (char* cmdFile, char* argV[]) {
	int pid, wait;
	int isConcurrent = 0;
	int i;
	
	for (i = 0; argV[i] != NULL; i++);
	{printf("argumentos del comando:%i\n",i );}
	
	for(int z=0;argV[z]!=NULL;z++)
		{printf("no se que es:%s\n",argV[z]);}
	
	if (!strcmp(argV[i-1], "&")){
		printf("Soy concurrente\n");
		isConcurrent = 1;
	}

	pid = fork();
	if (pid < 0) {
		perror("Error - Child creation");
		exit(1);
	}
	else if (pid == 0) {
		execv(cmdFile, argV);
		perror(cmdFile);
		exit(1);
	}
	else if (isConcurrent)
		return;
	waitpid (pid, &wait, 0);
}