#include "utils.h"


char *servername;
int mode;
int port;

void timerProtocol (){
    int sockfd;
    int errorCheck;
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
        if((dest_server=gethostbyname(servername))==NULL){//Resolvemos el host
            perror("NOT A VALID HOST");
            exit(0);
        }
        memcpy(&dest_addr.sin_addr,dest_server->h_addr_list[0], dest_server->h_length);
        dest_addr.sin_family=AF_INET;
        dest_addr.sin_port=htons(port);
        errorCheck=sendto(sockfd, &datagram,(u_int32_t)4,0,(struct sockaddr *)&dest_addr,(socklen_t)sizeof(dest_addr));//Lo de los octetos me lia
        if(errorCheck==-1){
            perror("Ha ocurrido un error ");
            exit(0);
        }
        socklen_t recvsize=(socklen_t)sizeof(dest_addr);
        for(int i=0; i<4;i+=errorCheck){//Este for es porque envia en octetos, por eso necesito hacerlo 4 veces
            errorCheck=recvfrom(sockfd, &datagram, (size_t)4,0,(struct sockaddr *)&dest_addr,&recvsize);
            if(errorCheck==-1){
                printf("Error at input");
            }
        }
        datagram=ntohl(datagram);
        from_secs_to_cest(&datagram);
    }
    close(sockfd);
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
        }  
    timerProtocol();
}


    