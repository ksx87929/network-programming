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

   printf("�п�J�nŪ�����ɦW\n");
   gets(name);
   fptr1=fopen(name,"r");
   if( fptr1!=NULL)
   {
   WSAStartup(0x101,(LPWSADATA) &wsadata); // �I�s WSAStartup() ���U WinSock DLL ���ϥ�

   sd=socket(AF_INET, SOCK_STREAM, 0); //�}�Ҥ@�� TCP socket.

   //���s�u�@�ǳơA�]�t��g sockaddr_in ���c (serv) �C
   //���e���Gserver �� IP ��}�Aport number �����C
   serv.sin_family       = AF_INET;
   serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   serv.sin_port         = htons(5678);

   connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // �s���� echo server

   while( (ch=getc(fptr1))!=EOF)
   {

   str[0]=ch;
   str[1]='\0';
   send(sd, str, 1, 0);
   printf("[%d] send: %c \n" ,counter,str[0]);
   counter++;
    }//end while

   printf("sent complete and close!!\n");

   closesocket(sd); //����TCP socket

   WSACleanup();  // ���� WinSock DLL ���ϥ�

   fclose(fptr1);
   }//end if
}
   system("pause");

   return 0;
}
