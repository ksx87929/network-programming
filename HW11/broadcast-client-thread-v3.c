// broadcast multi-thread client
// each channel has its port number


#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <winsock.h>

#define MAXLINE 20
int BROADCAST=54678;
SOCKET        	sd;
struct sockaddr_in serv,cli;
char  		str[1024];
char  		str_r[1024];
WSADATA 		wsadata;
int timeout = 50,n,serv_len,cli_len,channel=1;



void *recvMess(void *argu) 
{    // �C�j�@�����L�X�@�� George �����
    while (1)
	{
        cli_len= sizeof(cli);        
		n=recvfrom(sd, str, MAXLINE, 0,(LPSOCKADDR) &cli,&cli_len ); //��echo server���� 
		if (n > 6)
        	printf("client(from:%s):%s,%d\n",inet_ntoa(cli.sin_addr),str,n);
        else
        {
			recvfrom(sd, str_r, 6, 0,(LPSOCKADDR) &cli,&cli_len );
        	BROADCAST=atoi(str_r);
        	printf("�w�s�u�� Port %d \n",BROADCAST);
        }
    }
}

int main(void) {
	
    int n,i,j,total=0;
    pthread_t thread1;

    WSAStartup(0x101,(LPWSADATA) &wsadata); // �I�s WSAStartup() ���U WinSock DLL ���ϥ�


    sd=socket(AF_INET, SOCK_DGRAM, 0);
    char broadcast = 'a';
    if(	setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast))<0)
		   printf("setsockopt() broadcast error!\n");
	
    serv.sin_family       = AF_INET;
    serv.sin_addr.s_addr  = 0;   
    serv.sin_port         = htons(BROADCAST);
    if( bind(sd, (LPSOCKADDR) &serv, sizeof(serv)) <0 )
   		printf("bind error!\n");
   	
    	serv_len=sizeof(serv);

    pthread_create(&thread1, NULL, &recvMess, NULL);
    

	while(1)
	{
		scanf("%d",&channel);
		printf("switch to channel %d\n\n",channel);
		switch(channel){
			case 1:
				    closesocket(sd);
			        sd=socket(AF_INET, SOCK_DGRAM, 0);
    				broadcast = 'a';
    				if(	setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast))<0)
		   			printf("setsockopt() broadcast error!\n");
		   			
		       		serv.sin_family       = AF_INET;
    				serv.sin_addr.s_addr  = 0;
					serv.sin_port  = htons(BROADCAST);
					
    				if( bind(sd, (LPSOCKADDR) &serv, sizeof(serv)) <0 )    				
   					printf("bind error!(%d)\n", WSAGetLastError ());      
		   	   		 break;
			case 2:
					closesocket(sd);
			        sd=socket(AF_INET, SOCK_DGRAM, 0);
    				broadcast = 'a';
    				if(	setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast))<0)
		   			printf("setsockopt() broadcast error!\n");
		   			
		       		serv.sin_family       = AF_INET;
    				serv.sin_addr.s_addr  = 0;
					serv.sin_port  = htons(BROADCAST+1);
    				if( bind(sd, (LPSOCKADDR) &serv, sizeof(serv)) <0 )
   					printf("bind error!\n");
  		   	   		 break;
			case 3:
					closesocket(sd);
			        sd=socket(AF_INET, SOCK_DGRAM, 0);
			        
    				broadcast = 'a';
    				if(	setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast))<0)
		   			printf("setsockopt() broadcast error!\n");
		   			
		       		serv.sin_family       = AF_INET;
    				serv.sin_addr.s_addr  = 0;
					serv.sin_port  = htons(BROADCAST+2);
    				if( bind(sd, (LPSOCKADDR) &serv, sizeof(serv)) <0 )
   					printf("bind error!\n");    
		   	   		 break;
		}
	}

   closesocket(sd); //����TCP socket

   WSACleanup();  // ���� WinSock DLL ���ϥ�
   system("pause");

   return 0;
}

