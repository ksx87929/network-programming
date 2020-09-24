#include <stdio.h>
#include <string.h>
#include <winsock.h>
#include <pthread.h>
#define MAXLINE 1024
SOCKET        	sd;     
struct sockaddr_in serv,cli;

WSADATA 		wsadata;
int n,serv_len,state=1,channel;
char x;
int flag=1,len=sizeof(int),cli_len,port1=7777,port2=7778,port3=7779,port=7780;
char broadcast = 'a',ip1[10]="224.1.1.1",ip2[10]="224.1.1.2",ip3[10]="224.1.1.3";      

void *recvMess(void *argu)
{    // 每隔一秒鐘印出一次 George 的函數

    while (1)
	{       
		char  		str[1024]="";
        cli_len= sizeof(cli);        
		n=recvfrom(sd, str, MAXLINE, 0,(LPSOCKADDR) &cli,&cli_len ); //由echo server接收 
		if (n > 0)
        	printf("client(from:%s):%s,%d\n",inet_ntoa(cli.sin_addr),str,n);
    }
}
int main(int argc, char** argv)
{  
	pthread_t thread1;
   
   
   WSAStartup(0x101,(LPWSADATA) &wsadata); // 呼叫 WSAStartup() 註冊 WinSock DLL 的使用
   sd=socket(AF_INET, SOCK_DGRAM, 0);
   
   struct ip_mreq multicastRequest;
   
   sd=socket(AF_INET, SOCK_DGRAM, 0);
   if(	setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast))<0)
   		printf("setsockopt() broadcast error!\n");
	
    serv.sin_family       = AF_INET;
    serv.sin_addr.s_addr  = 0;   
    serv.sin_port         = htons(port);
    if( bind(sd, (LPSOCKADDR) &serv, sizeof(serv)) <0 )
   		printf("bind error!\n");
   	
   serv_len=sizeof(serv);

   pthread_create(&thread1, NULL, &recvMess, NULL);
   while(1)
	{
		
		scanf("%c",&x);
		if(x=='x'||x=='X')
			x='4';
		channel=x-48;
		switch(channel)
		{
			case 1:
				    closesocket(sd);
			        sd=socket(AF_INET, SOCK_DGRAM, 0);			        
					if ( setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &flag, len) < 0 )
	        			printf("setsockopt() failed");
		   			
		       		cli.sin_family       = AF_INET;
				    cli.sin_addr.s_addr  = 0;
				    cli.sin_port         = htons(port1);
					cli_len= sizeof(cli); 
    				if( bind(sd, (LPSOCKADDR) &cli, sizeof(cli)) <0 )
	   					printf("bind error!\n");  
		   	   		
		   	   			
					    /* Specify the multicast group */
					serv_len=sizeof(serv);
			
					multicastRequest.imr_multiaddr.s_addr = inet_addr(ip1);
				    	/* Accept multicast from any interface */
				    multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY);
				    	/* Join the multicast address */
				
				    if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *) &multicastRequest,sizeof(multicastRequest)) < 0)
				    	printf("setsockopt() failed");
				    break;
			case 2:
					closesocket(sd);
			        sd=socket(AF_INET, SOCK_DGRAM, 0);				
    				if ( setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &flag, len) < 0 )
	        			printf("setsockopt() failed");
		   			
		       		cli.sin_family       = AF_INET;
				    cli.sin_addr.s_addr  = 0;
				    cli.sin_port         = htons(port2);
					cli_len= sizeof(cli); 
    				if( bind(sd, (LPSOCKADDR) &cli, sizeof(cli)) <0 )
	   					printf("bind error!\n");  
		   	   		
		   	   		  /* Multicast address join structure */ 	
					    /* Specify the multicast group */
					serv_len=sizeof(serv);
						
						
					multicastRequest.imr_multiaddr.s_addr = inet_addr(ip2);
				    	/* Accept multicast from any interface */
				    multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY);
				    	/* Join the multicast address */
				
				    if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *) &multicastRequest,sizeof(multicastRequest)) < 0)
				    	printf("setsockopt() failed");
				    break;
			case 3:
					closesocket(sd);
			        sd=socket(AF_INET, SOCK_DGRAM, 0);	
    				if ( setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &flag, len) < 0 )
	        			printf("setsockopt() failed");
		   			
		       		cli.sin_family       = AF_INET;
				    cli.sin_addr.s_addr  = 0;
				    cli.sin_port         = htons(port3);
					cli_len= sizeof(cli); 
    				if( bind(sd, (LPSOCKADDR) &cli, sizeof(cli)) <0 )
	   					printf("bind error!\n");  
		   	   		
		   	   		  /* Multicast address join structure */ 	
					    /* Specify the multicast group */
					serv_len=sizeof(serv);
						
					multicastRequest.imr_multiaddr.s_addr = inet_addr(ip3);
				    	/* Accept multicast from any interface */
				    multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY);
				    	/* Join the multicast address */
				
				    if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *) &multicastRequest,sizeof(multicastRequest)) < 0)
				    	printf("setsockopt() failed");
				    break;
			case 4:
					closesocket(sd);
			        sd=socket(AF_INET, SOCK_DGRAM, 0);
			    	
					broadcast = 'a';
					if(	setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast))<0)
						printf("setsockopt() broadcast error!\n");
						
				    serv.sin_family       = AF_INET;
				    serv.sin_addr.s_addr  = 0;   
				    serv.sin_port         = htons(port);
				    if( bind(sd, (LPSOCKADDR) &serv, sizeof(serv)) <0 )
				   		printf("bind error!\n");
				    break;
				
		}
		
	}
	
  	closesocket(sd); //關閉 socket
    WSACleanup();  // 結束 WinSock DLL 的使用
   
   	return 0;
}


