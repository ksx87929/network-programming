#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024

int main(int argc, char** argv) {

   SOCKET        	sd;
   struct sockaddr_in serv;
   char  		str[1024],str1[1024];
   WSADATA 		wsadata;
   int n,i;

   WSAStartup(0x101,(LPWSADATA) &wsadata); // 呼叫 WSAStartup() 註冊 WinSock DLL 的使用

   sd=socket(AF_INET, SOCK_STREAM, 0); //開啟一個 TCP socket.

   serv.sin_family       = AF_INET;
   serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   serv.sin_port         = htons(5678);

   connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // 連接至 echo server
   printf("Client2 has connectted to Server.\n");



	for (;;){

		gets(str);
	   	send(sd, str, strlen(str)+1, 0);

		int nError=WSAGetLastError();
		if(nError!=WSAEWOULDBLOCK && nError!=0)
		{
			printf("Winsock error code:%d\n",nError);
			printf("Disconnected!");
			// Close our socket entirely
			closesocket(sd);
			break;
		}
	   printf("Send : %s\n" ,str);


}

   closesocket(sd); //關閉TCP socket

   WSACleanup();  // 結束 WinSock DLL 的使用

   return 0;
}
