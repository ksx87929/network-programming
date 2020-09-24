#include <stdio.h>
#include <string.h>
#include <winsock.h>
#define MAXLINE 1024    /* 字串緩衝區長度 */

void main()
{
	SOCKET	serv_sd, cli_sd;        /* socket 描述子 */
  	int   	cli_len, n;
  	char  	str_r[MAXLINE];

  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;

    WSAStartup(0x101, &wsadata); //呼叫 WSAStartup() 註冊 WinSock DLL 的使用

  	serv_sd=socket(AF_INET, SOCK_STREAM, 0);// 開啟 TCP socket

   	//指定 socket 的 IP 位址和 port number
   	serv.sin_family      = AF_INET;
   	serv.sin_addr.s_addr = 0;
   	serv.sin_port        = htons(5678);	// 指定port

    //bind(serv_sd, &serv, sizeof(serv)) ;
    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));

   	listen(serv_sd, 5) ; //呼叫 listen() 使 socket 進入「監聽」狀態

	cli_len = sizeof(cli);
	cli_sd=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);

	int x,y=50,c=0;
	char guess[1024]="";
    x=rand();
    x%=100;
   	if(x==0)
   		x=100;
   	int up=100,down=1,k;
    k=(up+down)/2;
   	while(1)
   	{
   		c++;
		int number;

	   	n=recv(cli_sd, str_r, MAXLINE, 0); //由server接收

	    number=atoi(str_r);
		if(number>x)
		{
			printf( "回合%d : client猜%d ，too large。\n",c,number );

			char str[5]="太大";
			send(cli_sd, str, strlen(str)+1, 0); //傳送至echo server
		}
		else if(number==x)
		{
			printf( "回合%d : client猜%d ，get answer。\n",c,number );
			char str[9]="你猜對了";
			send(cli_sd, str, strlen(str)+1, 0); //傳送至echo server 
			break;
		}
		else if(number<x)
		{
			printf( "回合%d : client猜%d ，too small。\n",c,number );
			char str[5]="太小";
			send(cli_sd, str, strlen(str)+1, 0); //傳送至echo server

		}


		

			printf( "server猜%d。\n",k );
			sprintf(guess,"%d",k);
			send(cli_sd, guess, strlen(guess)+1, 0); //傳送至echo server
			n=recv(cli_sd, str_r, MAXLINE, 0); //由server接收

			if(strcmp(str_r,"你猜對了")==0)
				break;
			else if(strcmp(str_r,"Too large")==0)
			{
				up=k;
				k=(k+down)/2;
			}
			else if(strcmp(str_r,"Too small")==0)
			{
				down=k;
				k=(k+up)/2;
			}
		/*n=recv(cli_sd, str_r, MAXLINE, 0); //由server接收 */
	/*char STR[MAXLINE]="";
	gets(STR);
    send(cli_sd, STR, strlen(STR)+1, 0);//傳送至echo server
    /*printf("server reply: %d (%d bytes)\n" ,number,strlen(str)+1); */
	}
	//結束 WinSock DLL 的使用
   	closesocket(serv_sd);
   	closesocket(cli_sd);
   	WSACleanup();
   	system("pause");
}
