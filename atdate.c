#include "utils.h"


char *servername;
int mode;
int port;

void timerProtocol (){
    int sockfd;
    if(mode==0){//UDP MODE
        sockfd=socket(PF_INET, SOCK_DGRAM,0);
    }
}

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
    timerProtocol();
}


    