#include <stdio.h>
#include <string.h>
#include <winsock.h>
#include <time.h>
#define MAXLINE 1024

int main(int argc, char** argv) 
{
	printf("---------------------------client sent---------------------------\n");
	SOCKET        	sd;
	struct sockaddr_in serv,cli;
	char  		str[1024];
	char  		str_r[1024];
	WSADATA 		wsadata;
	long long int n,cli_len,total=0;
	clock_t c1,c2;
	WSAStartup(0x101,(LPWSADATA) &wsadata); // 呼叫 WSAStartup() 註冊 WinSock DLL 的使用
	sd=socket(AF_INET, SOCK_DGRAM, 0); //開啟一個 TCP socket.
	serv.sin_family       = AF_INET;
	serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
	serv.sin_port         = htons(5678);
	//connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // 連接至 echo server
	int i;
	memset(str,'1',1023);
	c1=clock();
	for(i=1; i<1048577; i++)
	{
		n=sendto(sd, str, strlen(str)+1, 0, (LPSOCKADDR) &serv, sizeof(serv)); //傳送
		total+=n;
		if(i%102400==0) 
		{
			int temp;
			c2=clock();
			temp=c2-c1;
	   		c1=c2;
			printf( "send : %d bytes , cost %d msec\n" ,total,temp);
		}
	}
	printf("---------------------------client recive---------------------------\n");
	cli_len = sizeof(cli);
	
	total=0;
	c1=clock();
	while(1)
	{
		n=recvfrom(sd, str_r, MAXLINE, 0,(LPSOCKADDR) &cli, &cli_len); //接收
		total+=n;
		if(total%104857600==0)
		{	 
	  		int temp;
	   		c2=clock();
  	   		temp=c2-c1;
			c1=c2;
		   	printf("client recv: %d bytes , cost %d msec\n",total,temp);
		}
	    if(total==1073741824)
	    	break;
	}
	//closesocket(sd); //關閉TCP socket

	WSACleanup();  // 結束 WinSock DLL 的使用
	system("pause");

	return 0;
}


