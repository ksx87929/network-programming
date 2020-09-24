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

   WSAStartup(0x101,(LPWSADATA) &wsadata); // �I�s WSAStartup() ���U WinSock DLL ���ϥ�

   sd=socket(AF_INET, SOCK_STREAM, 0); //�}�Ҥ@�� TCP socket.

   serv.sin_family       = AF_INET;
   serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   serv.sin_port         = htons(5678);

   connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // �s���� echo server

   printf("�п�JIP��} : \n");
   gets(str);
   send(sd, str, strlen(str)+1, 0); //�ǰe
   //printf( "send: %s (%d bytes)\n" ,str,strlen(str)+1);
   n=recv(sd, str_r, MAXLINE, 0); //����
   printf("��IP��}����W�٬� : \n%s \n",str_r);


   printf("�п�J���} : \n");
   gets(str);
   send(sd, str, strlen(str)+1, 0); //�ǰe
   n=recv(sd, str_r, MAXLINE, 0); //����
   printf("�ӥD���W�٬� : \n%s \n",str_r);


   printf("�п�JSERVICE : \n");
   gets(str);
   send(sd, str, strlen(str)+1, 0); //�ǰe
   n=recv(sd, str_r, MAXLINE, 0); //����
   printf("��SERVICE PORT�� : \n%s \n",str_r);

   printf("�п�JPORT : \n");
   gets(str);
   send(sd, str, strlen(str)+1, 0); //�ǰe
   n=recv(sd, str_r, MAXLINE, 0); //����
   printf("��PORT SERVICE�� : \n%s \n",str_r);

   char proto[1024]="";
   printf("�п�JPROTOCOL : \n");
   gets(str);
   send(sd, str, strlen(str)+1, 0); //�ǰe
   n=recv(sd, proto, MAXLINE, 0); //����
   printf("��PROTOCOL �s���� : \n%s \n",proto);

   printf("�п�JPROTOCOL NUMBER : \n");
   gets(str);
   send(sd, str, strlen(str)+1, 0); //�ǰe
   n=recv(sd, str_r, MAXLINE, 0); //����
   printf("��PROTOCOL �� : \n%s \n",str_r);



   closesocket(sd); //����TCP socket

   WSACleanup();  // ���� WinSock DLL ���ϥ�


   return 0;
}
