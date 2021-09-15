#include "utils.h"


char *servername;
int mode;
int port;

int main(int argc, char *argv[]){
    servername=(char*)malloc(100);
    if (argc==2){ 
         
        if (strcmp(argv[1], "man")==0){
        
        printMan();

            }
        }
    if (argc>2){
            startingArg(argc, argv);
            printf("%d\n", port);
            printf("%d\n", mode);
            printf("%s\n",servername);
        }  
    else{
        fromSecstoCEST(200);
        printTime();
        return 0;

    }
}
    