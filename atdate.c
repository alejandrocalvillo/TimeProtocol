#include "utils.h"
#include <sys/socket.h>

char *servername;
int mode=0;
int port=0;
int debugger=0;
void signintHandler( int sig){
    printf("SIGINT received, closing program\n");
    exit(0);
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

        if (debugger==1){
            printf("Abriendo un socket modo UDP\n");
        }

        sockfd=socket(PF_INET, SOCK_DGRAM,0);//Creo que con getprotocolbyname podemos cambiarlo por el 0
        if (sockfd==-1){
            perror("Error al crear el SOCKET");
            exit(0);
        }

        if((dest_server=gethostbyname(servername))==NULL){//Resolvemos el host
            perror("NOT A VALID HOST");
            exit(0);
        }

        memcpy(&dest_addr.sin_addr,dest_server->h_addr_list[0], dest_server->h_length);
        dest_addr.sin_family=AF_INET;
        dest_addr.sin_port=htons(port);

        if (debugger==1){
            printf("Enviando un paquete vacio a %s al puerto: %d \n",servername, port);
        }

        errorCheck=sendto(sockfd, &datagram,(u_int32_t)0,0,(struct sockaddr *)&dest_addr,(socklen_t)sizeof(dest_addr));//Lo de los octetos me lia
        if(errorCheck==-1){
            perror("Ha ocurrido un error ");
            exit(0);
        }
        socklen_t recvsize=(socklen_t)sizeof(dest_addr);
        for(int i=0; i<4;i+=errorCheck){//Este for es porque envia en octetos, por eso necesito hacerlo 4 veces
            if (debugger==1){
            printf("Recibiendo el octeto Nº %d\n", i+1);
            }
            errorCheck=recvfrom(sockfd, &datagram, (size_t)4,0,(struct sockaddr *)&dest_addr,&recvsize);
            
            if(errorCheck==-1){
                printf("Error at input");
            }
        }

        close(sockfd);
        datagram=ntohl(datagram);

        if (debugger==1){
            printf("Procesando los datos...\n");
        }

        from_secs_to_cest(&datagram);
    }
    if(mode==1){//TCP Client
        u_int32_t datagram; //VOID DATAGRAM 32 bits
        signal(SIGINT, signintHandler);
        sockfd=socket(PF_INET, SOCK_STREAM,0);
        bzero((char *)&dest_addr, sizeof(dest_addr));
        dest_addr.sin_family=AF_INET;

        if (debugger==1){
            printf("Resolvemos el Host %s al puerto %d\n", servername,port);
        }

        if((dest_server=gethostbyname(servername))==NULL){//Resolvemos el host
            perror("NOT A VALID HOST");
            exit(0);
        }
        dest_addr.sin_port=htons(port);
        bcopy((char *)dest_server->h_addr, (char *)&dest_addr.sin_addr.s_addr, dest_server->h_length);

        if (debugger==1){
            printf("Conectando con el servidor...\n");
        }

        errorCheck=connect(sockfd,(struct sockaddr *)&dest_addr,(socklen_t)sizeof(dest_addr));

        if(errorCheck==-1){
            perror("Server seems unreacheble\n");
            exit(0);
        }

        if (debugger==1){
            printf("Conectado\n");
        }

        while(1){

            if (debugger==1){
            printf("Recibiendo los datos\n");
            }

            errorCheck=recv(sockfd, &datagram, (size_t)4,0);
            datagram=ntohl(datagram);

            if (debugger==1){
            printf("Procesando los datos\n");
            }

            from_secs_to_cest(&datagram);
            if (signal(SIGINT, signintHandler)==SIG_ERR){
                close(sockfd);
                exit(0);
            }
        }  
        
        

    }
    if(mode==2){//TCP Server
        u_int32_t datagram;
        int sender;
        struct hostent *hostp;
        int hostaddrp;
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

        if (debugger==1){
            printf("Creando el servidor y poniendolo en modo escucha\n");
        }

        listen(sockfd, 1);
        while(1){
            int sin_size = sizeof(struct sockaddr_in);
            int new_fd = accept(sockfd, (struct sockaddr *)&dest_addr, &sin_size);
            //hostp = gethostbyaddr((const char *)&dest_addr.sin_addr.s_addr, sizeof(dest_addr.sin_addr.s_addr), AF_INET);
           // hostaddrp = inet_ntoa(dest_addr.sin_addr); //No se yo cuanto de bien está esto
           if(!fork()){
           close(sockfd);
            if (new_fd==-1){
                perror("Error acepting Connection\n");
                exit(0);
            }
            if (debugger==1){
                printf("Nueva conexión\n");
            }
            while(new_fd!=-1){
                if (debugger==1){
                    printf("Enviando los datos de hora\n");
                }
                datagram=htonl((u_int32_t)time(NULL)+2208988800);
                sender = send(new_fd,&datagram,sizeof(datagram),0);
                if (sender<=0){
                    close(new_fd);
                }
                retardo(1000);
            }
            close(new_fd);
            exit(1);
            }
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