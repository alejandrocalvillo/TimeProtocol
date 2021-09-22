#include "utils.h"


char *servername;
int mode=0;
int port=0;
static void signintHandler(int sig){
    printf("SIGINT received, closing program\n");
}
void timerProtocol (){
    int sockfd;
    int errorCheck;
    struct sockaddr_in my_addr;
    struct sockaddr_in dest_addr;
    struct hostent *dest_server;
    if(mode==0){//UDP CLIENT
        u_int32_t datagram; //VOID DATAGRAM 32 bits
        if (port==0){
            port=37;
        }
        sockfd=socket(PF_INET, SOCK_DGRAM,0);//Creo que con getprotocolbyname podemos cambiarlo por el 0
        if (sockfd==-1){
            perror("Error al crear el SOCKET");
            exit(0);
        }
        if((dest_server=gethostbyname(servername))==NULL){//Resolvemos el host
            perror("NOT A VALID HOST");
            exit(1);
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
    if(mode==1){//TCP Client
        u_int32_t datagram; //VOID DATAGRAM 32 bits
        sockfd=socket(PF_INET, SOCK_STREAM,0);
        dest_addr.sin_family=AF_INET;
        dest_addr.sin_port=htonl(port);
        if((dest_server=gethostbyname(servername))==NULL){//Resolvemos el host
            perror("NOT A VALID HOST");
            exit(1);
        }
        memcpy(&dest_addr.sin_addr,dest_server->h_addr_list[0], dest_server->h_length);
        errorCheck=connect(sockfd,(struct sockaddr *)&dest_addr,(socklen_t)sizeof(dest_addr));
        if(errorCheck==-1){
            perror("Server seems unreacheble\n");
            exit(1);
        }
        for(int i=0; i<4;i+=errorCheck){//Pochisimo esto yo creo
            errorCheck=recv(sockfd, &datagram, (size_t)4,0);
            if(errorCheck==-1){
                printf("Error at input");
            }
        }
        datagram=ntohl(datagram);
        from_secs_to_cest(&datagram);

        while(signal(SIGINT, signintHandler)!=SIG_ERR){
            for(int i=0; i<4;i+=errorCheck){//Pochisimo esto yo creo
            errorCheck=recv(sockfd, &datagram, (size_t)4,0);
            if(errorCheck==-1){
                printf("Error in packet");
                }
            }
        }
        if (signal(SIGINT, signintHandler)==SIG_ERR){
            close(sockfd);
            exit(1);
        }
    }
    if(mode==2){//TCP Server
        sockfd=socket(PF_INET, SOCK_STREAM,0);
        my_addr.sin_family = AF_INET;
        my_addr.sin_port=htons(port);
        my_addr.sin_addr.s_addr=htonl(INADDR_ANY);
        memset(&(my_addr.sin_zero), '\0', 8);
        errorCheck=bind(sockfd,(struct sockaddr *)&my_addr, sizeof(struct sockaddr));
        if(errorCheck==-1){
            printf("CANNOT CREATE SOURCE SERVER\n");
            exit(0);
        }
        listen(sockfd, 10);
        while(1){
            int sin_size = sizeof(struct sockaddr_in);
            int new_fd = accept(sockfd, (struct sockaddr *)&dest_addr, &sin_size);
        }     
    }
    close(sockfd);
}

int main(int argc, char *argv[]){
    servername=(char*)malloc(100);
    if (argc==2){ 
         
        if (strcmp(argv[1], "man")==0){
        
        printMan();
        mode=3;

            }
        }
    if (argc>2){
            startingArg(argc, argv);
        }  
    timerProtocol();
}