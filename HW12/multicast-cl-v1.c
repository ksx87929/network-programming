#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024

int main(int argc, char** argv) {  

   SOCKET        	sd;     
   struct sockaddr_in serv,cli;
   char  		str[1024];
   WSADATA 		wsadata;
   int n,serv_len;
   int flag=1,len=sizeof(int); 
   
   WSAStartup(0x101,(LPWSADATA) &wsadata); // 呼叫 WSAStartup() 註冊 WinSock DLL 的使用
  
   sd=socket(AF_INET, SOCK_DGRAM, 0);
   
    if ( setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &flag, len) < 0 )
        printf("setsockopt() failed");
   
   cli.sin_family       = AF_INET;
   cli.sin_addr.s_addr  = 0;
   cli.sin_port         = htons(7778);
   
  	if( bind(sd, (LPSOCKADDR) &cli, sizeof(cli)) <0 )
   		printf("bind error!\n");
   	
	struct ip_mreq multicastRequest;  /* Multicast address join structure */ 	
    /* Specify the multicast group */
    multicastRequest.imr_multiaddr.s_addr = inet_addr("224.1.1.2");
    /* Accept multicast from any interface */
    multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY);
    /* Join the multicast address */

    if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *) &multicastRequest,sizeof(multicastRequest)) < 0)
    	printf("setsockopt() failed");

 	serv_len=sizeof(serv);
	while(1){
	
		n=recvfrom(sd, str, MAXLINE, 0,(LPSOCKADDR) &serv,&serv_len ); //由echo server接收 
   		str[n]='\0';
		printf("client(from:%s):%s\n",inet_ntoa(serv.sin_addr),str);    
	}
	
  	closesocket(sd); //關閉 socket
    WSACleanup();  // 結束 WinSock DLL 的使用
   
   	return 0;
}


