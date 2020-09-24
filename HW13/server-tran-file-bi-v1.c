//server��(����)
//client -> server �G�줸��

#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024    /* �r��w�İϪ��� */

int main()
{
	SOCKET	serv_sd, cli_sd,cli_sd2;        /* socket �y�z�l */
  	int   	cli_len, n=1;
  	char  	str[MAXLINE];


  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;
  	FILE *fptr1;

   fptr1=fopen("77777.txt","w");
   if( fptr1!=NULL)
   {

	    WSAStartup(0x101, &wsadata); //�I�s WSAStartup() ���U WinSock DLL ���ϥ�
	
	  	serv_sd=socket(AF_INET, SOCK_STREAM, 0);// �}�� TCP socket
	
	   	//���w socket �� IP ��}�M port number
	   	serv.sin_family      = AF_INET;
	   	serv.sin_addr.s_addr = 0;
	   	serv.sin_port        = htons(5678);	// ���w IPPORT_ECHO �� echo port
	
	    //bind(serv_sd, &serv, sizeof(serv)) ;
	    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));
	
	   	listen(serv_sd, 5) ; //�I�s listen() �� socket �i�J�u��ť�v���A
	
	   	cli_len = sizeof(cli);
	
	   	while (1) 
		{
			printf("Waiting For Client 1\n");
	   		
			cli_sd2=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);
			
	   		printf("Wwaiting For Client 2\n");
	
	   		cli_sd=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);
	   		
	   		
	
	    	while(1)
			{
	            n=recv(cli_sd, str, MAXLINE, 0);
	            if (strcmp(str,"end of file") == 0 )
				{
					send(cli_sd2,str,MAXLINE,0);
					break;
				}
				else
				{
					//printf("server: waiting for client1 : %s",str);
	            	send(cli_sd2,str,n+1,0);
	            }
	        }
	
		    printf("Received EOF:%s\n" ,str);
		    fclose(fptr1);
		    printf("Received Complete!! \n");
		
		    closesocket(cli_sd);
	    }
	//���� WinSock DLL ���ϥ�
   	closesocket(serv_sd);

   	WSACleanup();
   	}//end if
   	return 0;
}
