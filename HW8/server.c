#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024    /* 字串緩衝區長度 */

void main()
{
	SOCKET	serv_sd, cli_sd[10],new_sd;        /* socket 描述子 */
  	int   	cli_len, n=0,i,num_client=0;
  	char  	str[MAXLINE];

  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;

    WSAStartup(0x101, &wsadata); //呼叫 WSAStartup() 註冊 WinSock DLL 的使用

  	serv_sd=socket(AF_INET, SOCK_STREAM, 0);// 開啟 TCP socket

   	//指定 socket 的 IP 位址和 port number
   	serv.sin_family      = AF_INET;
   	serv.sin_addr.s_addr = 0;
   	serv.sin_port        = htons(5678);	// 指定 IPPORT_ECHO 為 echo port

    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));

   	listen(serv_sd, 5) ; //呼叫 listen() 使 socket 進入「監聽」狀態
   	cli_len = sizeof(cli);
   	printf("waiting for server\n");
   	u_long iMode=1;
   	ioctlsocket(serv_sd,FIONBIO,&iMode);

   	while (1)
	{
       	//enable non-blocking mode when iMode=1

		if( (new_sd=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len)) != -1 )
		{
			printf("server get a new client %d\n",num_client+1);
			cli_sd[num_client]=new_sd;
			ioctlsocket(cli_sd[num_client],FIONBIO,&iMode);
			num_client++;
		}
		/*if (iMode ==0)
			printf("This is blocking mode.\n");
		else
       		printf("This is non-blocking mode.\n");*/

	    for(i=0;i<num_client;i++)
		{

			n=recv(cli_sd[i], str, MAXLINE, 0);
			if (n > 0 )
	    		printf("Recv from client %d : %s\n",num_client,str);

		   	// 顯示從 client 傳來的字串
			int nError=WSAGetLastError();
			if(nError!=WSAEWOULDBLOCK && nError!=0)
			{
				int k=0;
				for(k=i;k<num_client-1;k++)
					cli_sd[k]=cli_sd[k+1];
				printf("Disconnected! error code:%d\n",nError);
				num_client--;
				break;
			}
		}

    }
	//結束 WinSock DLL 的使用
   	closesocket(serv_sd);

   	WSACleanup();
}
