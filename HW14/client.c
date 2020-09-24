#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024

int main(int argc, char** argv) {

   SOCKET        	sd;
   struct sockaddr_in serv;
   char  		str[1024];
   char  		str_r[1024];
   WSADATA 		wsadata;
   int n;

   WSAStartup(0x101,(LPWSADATA) &wsadata); // 呼叫 WSAStartup() 註冊 WinSock DLL 的使用

   sd=socket(AF_INET, SOCK_STREAM, 0); //開啟一個 TCP socket.

   serv.sin_family       = AF_INET;
   serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   serv.sin_port         = htons(5678);

   connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // 連接至 echo server

   printf("請輸入IP位址 : \n");
   gets(str);
   send(sd, str, strlen(str)+1, 0); //傳送
   //printf( "send: %s (%d bytes)\n" ,str,strlen(str)+1);
   n=recv(sd, str_r, MAXLINE, 0); //接收
   printf("該IP位址網域名稱為 : \n%s \n",str_r);


   printf("請輸入網址 : \n");
   gets(str);
   send(sd, str, strlen(str)+1, 0); //傳送
   n=recv(sd, str_r, MAXLINE, 0); //接收
   printf("該主機名稱為 : \n%s \n",str_r);


   printf("請輸入SERVICE : \n");
   gets(str);
   send(sd, str, strlen(str)+1, 0); //傳送
   n=recv(sd, str_r, MAXLINE, 0); //接收
   printf("該SERVICE PORT為 : \n%s \n",str_r);

   printf("請輸入PORT : \n");
   gets(str);
   send(sd, str, strlen(str)+1, 0); //傳送
   n=recv(sd, str_r, MAXLINE, 0); //接收
   printf("該PORT SERVICE為 : \n%s \n",str_r);

   char proto[1024]="";
   printf("請輸入PROTOCOL : \n");
   gets(str);
   send(sd, str, strlen(str)+1, 0); //傳送
   n=recv(sd, proto, MAXLINE, 0); //接收
   printf("該PROTOCOL 編號為 : \n%s \n",proto);

   printf("請輸入PROTOCOL NUMBER : \n");
   gets(str);
   send(sd, str, strlen(str)+1, 0); //傳送
   n=recv(sd, str_r, MAXLINE, 0); //接收
   printf("該PROTOCOL 為 : \n%s \n",str_r);



   closesocket(sd); //關閉TCP socket

   WSACleanup();  // 結束 WinSock DLL 的使用


   return 0;
}
