#include "utils.h"


char *servername;
int mode;
int port;

void timerProtocol (){
    int sockfd;
    struct sockaddr_in my_addr;
    struct sockaddr_in dest_addr;
    struct hostent *dest_server;
    if(mode==0){//UDP MODE
        u_int32_t datagram; //VOID DATAGRAM 32 bits
        sockfd=socket(PF_INET, SOCK_DGRAM,0);
        if (sockfd==-1){
            perror("Error al crear el SOCKT");
            exit(0);
        }
        if((dest_server=gethostbyname(servername))==NULL){
            perror("NOT A VALID HOST");
            exit(1);
        }
        memcpy(&dest_addr.sin_addr,dest_server->h_addr_list[0], dest_server->h_length);
        dest_addr.sin_family=AF_INET;
        dest_addr.sin_port=htons(port);

        
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


    