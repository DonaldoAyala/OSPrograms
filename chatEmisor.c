/*
	Programa Emisor de un chat entre procesos
	Implementado mediante tuberías con nombre
	El chat es entre dos procesos (Emisor y Receptor) sin parentesco
	Como la comunicación es bidireccional se necesitan 2 tuberias
*/

#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() 
{ 
	int fd12,fd21; // Variables que serviran como descriptores de ficheros
    char * myfifo12 = "/tmp/myfifo12"; // Se indica la dirección de la tubería con nombre emisor-receptor
    char * myfifo21 = "/tmp/myfifo21"; // Se indica la dirección de la tubería con nombre receptor-emisor
    mkfifo(myfifo12, 0666);	// Se crea la tubería emisor-receptor con permisos de lectura y escritura
	mkfifo(myfifo21, 0666); // Se crea la tubería receptor-emisor con permisos de lectura y escritura
  	fd12 = open(myfifo12, O_WRONLY); // Se abre la tubería emisor-receptor para escritura
  	fd21 = open(myfifo21, O_RDONLY); // Se abre la tubería receptor-emisor para lectura
    char arr1[80];
    while (1) 
    { 
        printf("Escriba el mensaje para Usuario 2\n");
        fgets(arr1, 80, stdin);
        write(fd12, arr1, strlen(arr1)+1);  // El emisor escribe primero, espera hasta que el 
											//receptor abra la tubería para leer
        									// Se usa la variable fd12 que es el descriptor de 
											// fichero de la tuberia emisor-receptor de escritura
		if(strcmp(arr1,"0\n") == 0){
			printf("Fin del programa\n");
			break;
		}
        printf("Esperando mensaje\n");
        read(fd21, arr1, sizeof(arr1));		//Espera hasta que se reciba un mensaje del proceso receptor
        									//Se usa la variable fd21 que es el descriptor de fichero de
        									//la tubería receptor-emisor de lectura
        if(strcmp(arr1,"0\n") == 0)
        	break;
        printf("Mensaje del Usuario 2: %s\n", arr1);
    }
    write(fd21,"0\n", strlen("0")+1);
    close(fd12);// Se cierran los descriptores de ficheros
    close(fd21);
    return 0; 
}
