//client��(�ǰe)
//client -> server �G�줸��
#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024

#define MAX 50

int main(int argc, char** argv)
{

   SOCKET        	sd;
   struct sockaddr_in serv;
   char  		str[1024];
   WSADATA 		wsadata;
   int n=0,bytes;
   FILE *fptr1;
   char ch;

   fptr1=fopen("send.txt","r");
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
	
		while (!feof(fptr1))
		{
		    bytes=fread(str,sizeof(char),MAX,fptr1);
		    send(sd, str, bytes, 0);
		}
	
	
	   strcpy(str,"end of file"); //��ch=EOF��
	   send(sd, str, strlen(str)+1, 0); //�ǰeEOF��server
	   printf("send :%s\n",str);
	
	
	   closesocket(sd); //����TCP socket
	
	   WSACleanup();  // ���� WinSock DLL ���ϥ�
	
	   fclose(fptr1);
	   printf("sent complete!!\n");
	}//end if
	system("pause");
	return 0;
}


