#include "utils.h"

int main(int argc, char *argv[]){

    if (argc==2){   

        if (strcmp(argv[1], "man")==0){
        
        printMan();

            }
        }
    if (argc>2){
            printf("toy aqui\n");
            startingArg(argc, argv);

        }  
    else{
        fromSecstoCEST(200);
        printTime();
        return 0;

    }
}
    