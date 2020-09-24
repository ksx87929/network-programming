//server端(接收)
//client -> server 二位元檔

#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024    /* 字串緩衝區長度 */

int main()
{
	SOCKET	serv_sd, cli_sd,cli_sd2;        /* socket 描述子 */
  	int   	cli_len, n=1;
  	char  	str[MAXLINE];


  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;
  	FILE *fptr1;

   fptr1=fopen("77777.txt","w");
   if( fptr1!=NULL)
   {

	    WSAStartup(0x101, &wsadata); //呼叫 WSAStartup() 註冊 WinSock DLL 的使用
	
	  	serv_sd=socket(AF_INET, SOCK_STREAM, 0);// 開啟 TCP socket
	
	   	//指定 socket 的 IP 位址和 port number
	   	serv.sin_family      = AF_INET;
	   	serv.sin_addr.s_addr = 0;
	   	serv.sin_port        = htons(5678);	// 指定 IPPORT_ECHO 為 echo port
	
	    //bind(serv_sd, &serv, sizeof(serv)) ;
	    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));
	
	   	listen(serv_sd, 5) ; //呼叫 listen() 使 socket 進入「監聽」狀態
	
	   	cli_len = sizeof(cli);
	
	   	while (1) 
		{
			printf("Waiting For Client 1\n");
	   		
			cli_sd2=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);
			
	   		printf("Wwaiting For Client 2\n");
	
	   		cli_sd=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);
	   		
	   		
	
	    	while(1)
			{
	            n=recv(cli_sd, str, MAXLINE, 0);
	            if (strcmp(str,"end of file") == 0 )
				{
					send(cli_sd2,str,MAXLINE,0);
					break;
				}
				else
				{
					//printf("server: waiting for client1 : %s",str);
	            	send(cli_sd2,str,n+1,0);
	            }
	        }
	
		    printf("Received EOF:%s\n" ,str);
		    fclose(fptr1);
		    printf("Received Complete!! \n");
		
		    closesocket(cli_sd);
	    }
	//結束 WinSock DLL 的使用
   	closesocket(serv_sd);

   	WSACleanup();
   	}//end if
   	return 0;
}
