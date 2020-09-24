// broadcast multi-thread server
// each channel has its port number

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <winsock.h>

#define MAXLINE 20    /* 字串緩衝區長度 */
int BROADCAST=54678;
char B[6]="54678";

SOCKET	serv_sd;        /* socket 描述子 */
int   	cli_len, n,i=1,c=0;
char  	str[MAXLINE];
struct 	sockaddr_in   	serv, cli;
WSADATA wsadata;

void *change(void *argu)
{
	int temp=0;
	while(1)
	{
		gets(B);
		c=1;
	}
	
}
void main()
{
	   	
    WSAStartup(0x101, &wsadata); //呼叫 WSAStartup() 註冊 WinSock DLL 的使用
	pthread_t thread1;
   	serv_sd=socket(AF_INET, SOCK_DGRAM, 0);// 開啟 UDP socket
   	char broadcast = 'a';
	setsockopt(serv_sd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));   	
   	cli_len = sizeof(cli);
   	printf("server will broadcast.\n");
   	               
    cli.sin_family      = AF_INET;
   	cli.sin_addr.s_addr = inet_addr("255.255.255.255");
   	cli.sin_port        = htons(52678);
   	pthread_create(&thread1, NULL, &change, NULL);
   	
while(1){
		
		if(c!=0)
		{
			cli.sin_port        =  htons(BROADCAST );	
			sendto(serv_sd, "K", 2 , 0,(LPSOCKADDR)&cli,cli_len);
			sendto(serv_sd, B, strlen(B), 0,(LPSOCKADDR)&cli,cli_len);
			c=0;
			sleep(3);
			BROADCAST=atoi(B);
		}
		
		cli.sin_port        =  htons(BROADCAST );	
		memset(str, i%10 +'0', sizeof(str));
		sendto(serv_sd, str, strlen(str), 0,(LPSOCKADDR)&cli,cli_len);        
        printf("server broadcast: %s\n",str);		// 顯示送去client 的字串	
        
        cli.sin_port        = htons(BROADCAST+1);
		memset(str, (i-1)%26 +'a', sizeof(str));
		sendto(serv_sd, str, strlen(str), 0,(LPSOCKADDR)&cli,cli_len);        
        printf("server broadcast: %s\n",str);		// 顯示送去client 的字串        
        
        cli.sin_port        = htons(BROADCAST+2);
		memset(str, (i-1)%26 +'A', sizeof(str));
		sendto(serv_sd, str, strlen(str), 0,(LPSOCKADDR)&cli,cli_len);        
        printf("server broadcast: %s\n",str);		// 顯示送去client 的字串 
		
		sleep(2);
        
        
        i++;
    }
        
	//結束 WinSock DLL 的使用
   	closesocket(serv_sd);
   	//closesocket(cli_sd);
   	WSACleanup();
}
