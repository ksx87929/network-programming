#include <stdio.h>
#include <string.h>
#include <winsock.h>
#define MAXLINE 1024

int main(int argc, char** argv) {

   SOCKET        	sd;
   struct sockaddr_in serv;
   char  		str[1024];
   char c;
   WSADATA 		wsadata;
   int counter=1;
   FILE *fptr1;
   char ch,name[1024]="";

   while(1)
   {

   printf("請輸入要讀取的檔名\n");
   gets(name);
   fptr1=fopen(name,"r");
   if( fptr1!=NULL)
   {
   WSAStartup(0x101,(LPWSADATA) &wsadata); // 呼叫 WSAStartup() 註冊 WinSock DLL 的使用

   sd=socket(AF_INET, SOCK_STREAM, 0); //開啟一個 TCP socket.

   //為連線作準備，包含填寫 sockaddr_in 結構 (serv) 。
   //內容有：server 的 IP 位址，port number 等等。
   serv.sin_family       = AF_INET;
   serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   serv.sin_port         = htons(5678);

   connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // 連接至 echo server

   while( (ch=getc(fptr1))!=EOF)
   {

   str[0]=ch;
   str[1]='\0';
   send(sd, str, 1, 0);
   printf("[%d] send: %c \n" ,counter,str[0]);
   counter++;
    }//end while

   printf("sent complete and close!!\n");

   closesocket(sd); //關閉TCP socket

   WSACleanup();  // 結束 WinSock DLL 的使用

   fclose(fptr1);
   }//end if
}
   system("pause");

   return 0;
}
