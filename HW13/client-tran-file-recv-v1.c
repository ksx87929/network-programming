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

   fptr1=fopen("recv.txt","w");
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
	
		while(1)
		{
	        n=recv(sd, str, MAXLINE, 0);
	        if (strcmp(str,"end of file") == 0 )
				break; 
	        fwrite(str,sizeof(char),n,fptr1);
	    }

		printf("received EOF:%s\n" ,str);
		fclose(fptr1);
		printf("received complete!! \n");
		closesocket(sd); //����TCP socket
	  
	}//end if
	
	WSACleanup();  // ���� WinSock DLL ���ϥ�
	system("pause");
	return 0;
}


