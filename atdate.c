#include "utils.h"

int main(int argc, char *argv[]){

    if (argc>1){   

        if (strcmp(argv[1], "man")==0){
        
        printMan();

        }
    }  
    else{
        fromSecstoCEST(200);
        printTime();
        return 0;

    }
}
    