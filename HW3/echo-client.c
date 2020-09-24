#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024

int main(int argc, char** argv) {  

   SOCKET        	sd;     
   struct sockaddr_in serv;
  
   char  		str_r[1024];
   WSADATA 		wsadata;
   int n;
   

   WSAStartup(0x101,(LPWSADATA) &wsadata); // 呼叫 WSAStartup() 註冊 WinSock DLL 的使用
  
   sd=socket(AF_INET, SOCK_STREAM, 0); //開啟一個 TCP socket.
   
   serv.sin_family       = AF_INET; 
   serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   serv.sin_port         = htons(5678);

   	connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // 連接至 echo server
   
   int x,guess,c=0;
   x=rand();
   x%=100;
   if(x==0)
	   		x=100;
   while(1)
   {
   		c++;

   	   char  str[1024]="";
	   printf( "回合%d : 請輸入猜的數字 ",c );
	   gets(str);
	   send(sd, str, strlen(str)+1, 0); //傳送
	   n=recv(sd, str_r, MAXLINE, 0); //接收 
	   printf("server說%s。",str_r,n);
	   if(strcmp(str_r,"你猜對了")==0)
	   	{
		  printf("\n");  
		  break;
		}
	   
	   
	   
	   n=recv(sd, str_r, MAXLINE, 0); //接收 
	   printf("server猜%s。",str_r,n);
	   guess=atoi(str_r);
	   if(guess==x)
	   {
	   	char STR[1024]="你猜對了";
	   	send(sd, STR, strlen(STR)+1, 0); //傳送
	   	break;
	   }
	   if(guess>x)
	   {
	   	char STR[1024]="Too large";
	   	send(sd, STR, strlen(STR)+1, 0); //傳送
	   	printf("請回覆 : too large\n");
	   }
	   if(guess<x)
	   {
	   	char STR[1024]="Too small";
	   	send(sd, STR, strlen(STR)+1, 0); //傳送
	   	printf("請回覆 : too small\n");
	   }
	   
	   
	   
   }
   closesocket(sd); //關閉TCP socket
    
   WSACleanup();  // 結束 WinSock DLL 的使用
   system("pause");
   
   return 0;
}


