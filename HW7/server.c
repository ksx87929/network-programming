#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024    /* �r��w�İϪ��� */

int main()
{
	SOCKET	serv_sd, cli_sd;        /* socket �y�z�l */
  	int   	cli_len, n,counter=1;
  	char  	str[MAXLINE];

  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;
  	FILE *fptr1;
	char name[1024]="";

while(1)
 {

   printf("�п�J�n�g�J���ɦW\n");
   gets(name);
   fptr1=fopen(name,"w");
   if( fptr1!=NULL)
   {

    WSAStartup(0x101, &wsadata); //�I�s WSAStartup() ���U WinSock DLL ���ϥ�

  	serv_sd=socket(AF_INET, SOCK_STREAM, 0);// �}�� TCP socket

   	//���w socket �� IP ��}�M port number
   	serv.sin_family      = AF_INET;
   	serv.sin_addr.s_addr = 0;
   	serv.sin_port        = htons(5678);	// ���w IPPORT_ECHO �� echo port


    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));

   	listen(serv_sd, 5) ; //�I�s listen() �� socket �i�J�u��ť�v���A

   	cli_len = sizeof(cli);


	printf("server: waiting for client\n");

	cli_sd=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);
	char str1[1024]="";
	while( 1 )
	{
	    n=recv(cli_sd, str, MAXLINE, 0);
	    str[n]='\0';
	    strcat(str1,str);
	  	fputs(str,fptr1);

	    if (n == 0)
		{
	    	printf("[%d] recv:%s  (size:%d) \n",counter,str1,n);
			puts("close connection");
	    	break;
		}

	    counter++;
	}


	fclose(fptr1);

    closesocket(cli_sd);
   	closesocket(serv_sd);

   	WSACleanup();
   	}//end if
   }
   	system("pause");
   	return 0;
}
