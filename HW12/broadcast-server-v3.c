// broadcast multi-thread server
// each channel has its port number

#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 20    /* �r��w�İϪ��� */
#define BROADCAST 54678

void main()
{
	SOCKET	serv_sd;        /* socket �y�z�l */
  	int   	cli_len, n,i=1;
  	char  	str[MAXLINE];

  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;
	   	
    WSAStartup(0x101, &wsadata); //�I�s WSAStartup() ���U WinSock DLL ���ϥ�
	
   	serv_sd=socket(AF_INET, SOCK_DGRAM, 0);// �}�� UDP socket
   	char broadcast = 'a';
	setsockopt(serv_sd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));   	
   	cli_len = sizeof(cli);
   	printf("server will broadcast.\n");
   	               
    cli.sin_family      = AF_INET;
   	cli.sin_addr.s_addr = inet_addr("255.255.255.255");
   	cli.sin_port        = htons(52678);
   		
while(1){

		cli.sin_port        =  htons(BROADCAST );	
		memset(str, i%10 +'0', sizeof(str));
		sendto(serv_sd, str, strlen(str), 0,(LPSOCKADDR)&cli,cli_len);        
        printf("server broadcast: %s\n",str);		// ��ܰe�hclient ���r��	
        
        cli.sin_port        = htons(BROADCAST+1);
		memset(str, (i-1)%26 +'a', sizeof(str));
		sendto(serv_sd, str, strlen(str), 0,(LPSOCKADDR)&cli,cli_len);        
        printf("server broadcast: %s\n",str);		// ��ܰe�hclient ���r��        
        
        cli.sin_port        = htons(BROADCAST+2);
		memset(str, (i-1)%26 +'A', sizeof(str));
		sendto(serv_sd, str, strlen(str), 0,(LPSOCKADDR)&cli,cli_len);        
        printf("server broadcast: %s\n",str);		// ��ܰe�hclient ���r�� 
		
		sleep(1);
        
        
        i++;
    }
        
	//���� WinSock DLL ���ϥ�
   	closesocket(serv_sd);
   	//closesocket(cli_sd);
   	WSACleanup();
}
