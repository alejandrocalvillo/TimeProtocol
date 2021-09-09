#include "utils.h"


char *servername;
char *mode;
int port;

int main(int argc, char *argv[]){

    if (argc==2){   

        if (strcmp(argv[1], "man")==0){
        
        printMan();

            }
        }
    if (argc>2){
            printf("toy aqui\n");
            startingArg(argc, argv, servername, mode, port);

        }  
    else{
        fromSecstoCEST(200);
        printTime();
        return 0;

    }
}
    