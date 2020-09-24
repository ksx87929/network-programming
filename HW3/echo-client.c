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
   

   WSAStartup(0x101,(LPWSADATA) &wsadata); // �I�s WSAStartup() ���U WinSock DLL ���ϥ�
  
   sd=socket(AF_INET, SOCK_STREAM, 0); //�}�Ҥ@�� TCP socket.
   
   serv.sin_family       = AF_INET; 
   serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   serv.sin_port         = htons(5678);

   	connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // �s���� echo server
   
   int x,guess,c=0;
   x=rand();
   x%=100;
   if(x==0)
	   		x=100;
   while(1)
   {
   		c++;

   	   char  str[1024]="";
	   printf( "�^�X%d : �п�J�q���Ʀr ",c );
	   gets(str);
	   send(sd, str, strlen(str)+1, 0); //�ǰe
	   n=recv(sd, str_r, MAXLINE, 0); //���� 
	   printf("server��%s�C",str_r,n);
	   if(strcmp(str_r,"�A�q��F")==0)
	   	{
		  printf("\n");  
		  break;
		}
	   
	   
	   
	   n=recv(sd, str_r, MAXLINE, 0); //���� 
	   printf("server�q%s�C",str_r,n);
	   guess=atoi(str_r);
	   if(guess==x)
	   {
	   	char STR[1024]="�A�q��F";
	   	send(sd, STR, strlen(STR)+1, 0); //�ǰe
	   	break;
	   }
	   if(guess>x)
	   {
	   	char STR[1024]="Too large";
	   	send(sd, STR, strlen(STR)+1, 0); //�ǰe
	   	printf("�Ц^�� : too large\n");
	   }
	   if(guess<x)
	   {
	   	char STR[1024]="Too small";
	   	send(sd, STR, strlen(STR)+1, 0); //�ǰe
	   	printf("�Ц^�� : too small\n");
	   }
	   
	   
	   
   }
   closesocket(sd); //����TCP socket
    
   WSACleanup();  // ���� WinSock DLL ���ϥ�
   system("pause");
   
   return 0;
}


