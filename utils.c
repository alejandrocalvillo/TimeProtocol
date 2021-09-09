#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

char* time;

void fromSecstoCEST(int secs){

    time="Patata";

}

void printTime(){

    printf("%s\n", time);

}

void printMan(){
    printf("\n");
    printf("-s serverhost: nombre del servidor TIME al que se conectará el programa para obtener la fecha y hora actual. Este argumento es obligatorio sólo si el programa se lanza en modo consulta, es decir, con -m cu o -m ct");
    printf(" \n");
    printf("\n");
    printf("-m: para indicar el modo de ejecución del programa:\n");        printf("        cu: el programa arranca en modo consulta funcionando como cliente UDP.\n");
    printf("        ct: el programa arranca en modo consulta funcionando como cliente TCP.\n");
    printf("        s: el programa arranca en modo servidor.\n");
    printf("-p port: para indicar el número de puerto. \n");
    printf("        Si se arranca en modo consulta, indica que el servidor TIME al que nos conectamos escucha en un puerto diferente al 37.\n");
    printf("        Si se arranca en modo servidor, indica el puerto en el que quedará a la escucha el servidor. Si no se especifica se usará el puerto por defecto, es decir, 37.\n");
    printf(" \n");
    printf("\n");
    printf("-d: modo depuración. Mostrará trazas adicionales para la depuración del programa.\n");
}

void startingArg(int argc, char *argv[], char *servername, char *mode, int port){
    for(int i =1; i<argc; i++){

        if (strcmp(argv[i], "-s")==0){
            printf("%s\n",argv[i+1]);
            strcpy(servername,argv[i+1]);
            printf("Patatudo jijijijijjijiji \n");
        }
        if  (strcmp(argv[i], "-m")==0){

        }
        if(strcmp(argv[i], "-p")==0){

        }

        if (strcmp(argv[i], "-d")==0){
           
        }
        
    }
}