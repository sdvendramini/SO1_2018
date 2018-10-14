#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "funciones.h"

int main () {
	int argC;
	char cmd[300];
	char cmdFile[300];
	char *paths[20];
	char *argV[300];
	
	parsePath (paths);

	while (1) {
		prompt ();
		fgets (cmd, 300, stdin);
		argC = leerCmd (argV, cmd);

		if (argC == 0) {
			printf("Escriba un comando\n");
			continue;
		}

		else {
			if (!strcmp (cmd, "exit"))
				return 0;
			if (!strcmp (cmd, "cd")) {
				//printf("%s\n",argV[1] );
				//printf("%s\n", argV[0]);
				int i = chdir (argV[1]);
				if (i != 0)
					printf ("El directorio no es correcto.\n");
				continue;
			}
			buscarCmd (argV[0], paths, cmdFile);
			if (cmdFile[0] == 'X')
				printf("Comando no encontrado\n");
			else 
				crearProc(cmdFile, argV);
		}
	}
	return 0;
}