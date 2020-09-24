#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 20    /* �r��w�İϪ��� */

void main()
{
	SOCKET	serv_sd;        /* socket �y�z�l */
  	int   	cli_len, n,i=1;
  	char  	str[MAXLINE];

  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;
	   	
    WSAStartup(0x101, &wsadata); //�I�s WSAStartup() ���U WinSock DLL ���ϥ�
	
   	serv_sd=socket(AF_INET, SOCK_DGRAM, 0);// �}�� UDP socket
   	
   	// for broadcast
   	//char broadcast = 'a';
	//setsockopt(serv_sd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));

   	    /* Set TTL of multicast packet */
   	int multicastTTL=1;
    if (setsockopt(serv_sd, IPPROTO_IP, IP_MULTICAST_TTL, (char *) &multicastTTL, 
          sizeof(multicastTTL)) == SOCKET_ERROR)
    printf("setsockopt() failed");
   	
   	
   	cli_len = sizeof(cli);
   	
   	
   	printf("server will multicastcast.\n");
   	               
    cli.sin_family      = AF_INET;
   	cli.sin_addr.s_addr = inet_addr("224.1.1.1");
   	cli.sin_port        = htons(5678);
   		
while(1){	
		memset(str, i%10 +'0', sizeof(str));
		n=sendto(serv_sd, str, strlen(str), 0,(LPSOCKADDR)&cli,cli_len);
        printf("server multicast: %d\n",n);		// ��ܰe�hclient ���r��	
        sleep(1);
        i++;
    }
        
	//���� WinSock DLL ���ϥ�
   	closesocket(serv_sd);
   	//closesocket(cli_sd);
   	WSACleanup();
}
