#include <stdio.h>
#include <string.h>
#include <winsock.h>
#include <time.h>
#define MAXLINE 1024

int main(int argc, char** argv) {  
	printf("---------------------------傳送---------------------------\n");

   SOCKET        	sd;     
   struct sockaddr_in serv;
   char  		str[1024];
   char  		str_r[1024];
   WSADATA 		wsadata;
   clock_t c1,c2;
   int n,i,j,total=0,time,ans;
   
   memset(str,"1",MAXLINE);
   
   WSAStartup(0x101,(LPWSADATA) &wsadata); // 呼叫 WSAStartup() 註冊 WinSock DLL 的使用
  
 
   sd=socket(AF_INET, SOCK_STREAM, 0); //開啟一個 TCP socket.
   
   serv.sin_family       = AF_INET; 
   serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   serv.sin_port         = htons(5678);

   connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // 連接至 echo server
   c1=clock();
   for (i=1;i<1048577;i++)
   {
	   n = send(sd, str, MAXLINE, 0); //傳送
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
   closesocket(sd); //關閉TCP socket
   printf("---------------------------接收---------------------------\n"); 
   sd=socket(AF_INET, SOCK_STREAM, 0); //開啟一個 TCP socket.
   
   serv.sin_family       = AF_INET; 
   serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   serv.sin_port         = htons(5678);
   total=0;
   n=0;
   connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // 連接至 echo server
   c1=clock();
   while(1)
		{
			n=recv(sd, str_r, MAXLINE, 0); //接收  //由server接收 
			total = total + n;
			//printf("server recv: %d bytes, total:%d \n",n,total); 
			if(total%1048576==0)
		   	{
		   		c2=clock();
		   		time=c2-c1;
		   		c1=c2;
		   		printf("每接收100M bytes 資料耗時 %d sec \n",time);
		   	}
		   	//printf("每接收100M bytes 資料耗時 %d sec \n",total);
			if( total%1073741824==0)	
				break;		
		}
   
   closesocket(sd); //關閉TCP socket
	
    
   WSACleanup();  // 結束 WinSock DLL 的使用
   system("pause");
   
   return 0;
}

