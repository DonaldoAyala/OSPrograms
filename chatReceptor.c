/*
	Programa Receptor de un chat entre procesos
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
    char arr[80];
    /*
    	No es necesario crear las tuberías con nombre de nuevo
    	puesto que las tuberías ya han sido creadas por el emisor,
    	solo es necesario abrirlas
    */
    fd12 = open(myfifo12,O_RDONLY); // Se abre la tubería emisor-receptor para lectura
    fd21 = open(myfifo21,O_WRONLY); // Se abre la tubería receptor-emisor para escritura
    while (1) 
    { 
    	printf("Esperando mensaje del Usuario 1\n");
        read(fd12, arr, 80);	//El receptor lee primero
        						// Se usa la variable fd12 que es el descriptor de 
								// fichero de la tuberia emisor-receptor de lectura
        printf("Mensaje del Usuario 1: %s\n", arr);
        if(strcmp(arr,"0\n") == 0){
			printf("Fin del programa\n");
			break;
		}
        printf("Escriba el mensaje para el Usuario 1\n");
        fgets(arr, 80, stdin);
        write(fd21, arr, strlen(arr)+1); 	// Se escribe el mensaje en la tubería receptor-emisor
        									// Se usa la variable que es el descriptor de fichero
        									// de la tubería receptor emisor de escritura
        if(strcmp(arr,"0\n") == 0)
        	break;
    }
    write(fd21,"0\n", strlen("0")+1);
    close(fd12);
    close(fd21);
    return 0; 
}
