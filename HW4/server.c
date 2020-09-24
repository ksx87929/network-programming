#include <stdio.h>
#include <string.h>
#include <winsock.h>
#include <time.h>
#define MAXLINE 1024    /* 字串緩衝區長度 */

void main()
{
	printf("---------------------------接收---------------------------\n"); 
	SOCKET	serv_sd, cli_sd;        /* socket 描述子 */
  	int   	cli_len, n,total=0;
  	char  	str[1024],str_r[1024];

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
   	clock_t c1,c2;
   	
   	//while(1)
   	//{
		cli_len = sizeof(cli); 		
		cli_sd=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);		
		c1=clock();
		int time=0;	
		while(1)
		{
			n=recv(cli_sd, str_r, MAXLINE, 0); //由server接收 
			total = total + n;
			//printf("server recv: %d bytes, total:%d \n",n,total); 
			if(total%104857600==0)
		   	{
		   		c2=clock();
		   		time=c2-c1;
		   		c1=c2;
		   		printf("每接收100M bytes 資料耗時 %d sec \n",time);
		   	}
		   	//printf("每接收100M bytes 資料耗時 %d sec \n",total);
			if( total == 1073741824)	
				break;		
		}
		closesocket(cli_sd);
		/*if( n == 0)	
			break;*/	    
	//}
	
	
	printf("---------------------------傳送---------------------------\n");
	cli_len = sizeof(cli); 		
	cli_sd=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);
	int i=1;
	memset(str,"1",MAXLINE);
	for (i=1;i<1048577;i++)
   {
	   send(cli_sd, str, strlen(str)+1, 0); //傳送
	   //total = total + n;
	   //printf( "client send:%d bytes, total:%d\n",n,total); 
	   if(i%102400==0)
	   {
	   		c2=clock();
	   		time=c2-c1;
	   		c1=c2;
	   		printf("每傳送100M bytes 資料耗時 %d msec \n",time);
	   }
   }
	
    //printf("每單位資料量 %d bytes/sec \n",ans);
	//結束 WinSock DLL 的使用
   	closesocket(serv_sd);

   	WSACleanup();
   	system("pause");
}

