#include <stdio.h>
#include <string.h>
#include <winsock.h>
#include <time.h>
#define MAXLINE 1024

int main(int argc, char** argv) {

   SOCKET        	sd;
   struct sockaddr_in serv;
   char  		str[1024]="abc";
   char  		str_r[1024];
   WSADATA 		wsadata;
   int n;
   double ans;
	clock_t t1,t2;
   WSAStartup(0x101,(LPWSADATA) &wsadata); // �I�s WSAStartup() ���U WinSock DLL ���ϥ�

   sd=socket(AF_INET, SOCK_STREAM, 0); //�}�Ҥ@�� TCP socket.
   //���s�u�@�ǳơA�]�t��g sockaddr_in ���c (serv) �C
   //���e���Gserver �� IP ��}�Aport number �����C
    serv.sin_family       = AF_INET;
   	serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
	serv.sin_port         = htons(9);
	connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // �s���� echo server
   int i=0;
   t1=clock();
   for(i=0;i<1000000;i++)
   {
	send(sd, str, strlen(str)+1, 0); //�ǰehow are you��echo server
	}
	t2=clock();
	ans=1000000/(t2-t1);
	ans*=3;
	printf("upload : %f bytes \n",ans);
   	closesocket(sd); //����TCP socket


   ans=0;
   t1=0;
   t2=0;
   int j=0;
   sd=socket(AF_INET, SOCK_STREAM, 0); //�}�Ҥ@�� TCP socket.
   //���s�u�@�ǳơA�]�t��g sockaddr_in ���c (serv) �C
   //���e���Gserver �� IP ��}�Aport number �����C
   	serv.sin_family       = AF_INET;
   	serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
	serv.sin_port         = htons(19);
	connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // �s���� echo server
    t1=clock();
	for(j=0;j<100000;j++)
	{
		n=recv(sd, str_r,MAXLINE, 0); //��echo server����
	}
	t2=clock();
	ans=100000/(t2-t1);
	ans*=1024;
	printf("download : %f bytes \n",ans);
   	closesocket(sd); //����TCP socket
   	WSACleanup();  // ���� WinSock DLL ���ϥ�



   return 0;
}
