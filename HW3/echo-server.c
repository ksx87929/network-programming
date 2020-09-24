#include <stdio.h>
#include <string.h>
#include <winsock.h>
#define MAXLINE 1024    /* �r��w�İϪ��� */

void main()
{
	SOCKET	serv_sd, cli_sd;        /* socket �y�z�l */
  	int   	cli_len, n;
  	char  	str_r[MAXLINE];

  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;

    WSAStartup(0x101, &wsadata); //�I�s WSAStartup() ���U WinSock DLL ���ϥ�

  	serv_sd=socket(AF_INET, SOCK_STREAM, 0);// �}�� TCP socket

   	//���w socket �� IP ��}�M port number
   	serv.sin_family      = AF_INET;
   	serv.sin_addr.s_addr = 0;
   	serv.sin_port        = htons(5678);	// ���wport

    //bind(serv_sd, &serv, sizeof(serv)) ;
    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));

   	listen(serv_sd, 5) ; //�I�s listen() �� socket �i�J�u��ť�v���A

	cli_len = sizeof(cli);
	cli_sd=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);

	int x,y=50,c=0;
	char guess[1024]="";
    x=rand();
    x%=100;
   	if(x==0)
   		x=100;
   	int up=100,down=1,k;
    k=(up+down)/2;
   	while(1)
   	{
   		c++;
		int number;

	   	n=recv(cli_sd, str_r, MAXLINE, 0); //��server����

	    number=atoi(str_r);
		if(number>x)
		{
			printf( "�^�X%d : client�q%d �Atoo large�C\n",c,number );

			char str[5]="�Ӥj";
			send(cli_sd, str, strlen(str)+1, 0); //�ǰe��echo server
		}
		else if(number==x)
		{
			printf( "�^�X%d : client�q%d �Aget answer�C\n",c,number );
			char str[9]="�A�q��F";
			send(cli_sd, str, strlen(str)+1, 0); //�ǰe��echo server 
			break;
		}
		else if(number<x)
		{
			printf( "�^�X%d : client�q%d �Atoo small�C\n",c,number );
			char str[5]="�Ӥp";
			send(cli_sd, str, strlen(str)+1, 0); //�ǰe��echo server

		}


		

			printf( "server�q%d�C\n",k );
			sprintf(guess,"%d",k);
			send(cli_sd, guess, strlen(guess)+1, 0); //�ǰe��echo server
			n=recv(cli_sd, str_r, MAXLINE, 0); //��server����

			if(strcmp(str_r,"�A�q��F")==0)
				break;
			else if(strcmp(str_r,"Too large")==0)
			{
				up=k;
				k=(k+down)/2;
			}
			else if(strcmp(str_r,"Too small")==0)
			{
				down=k;
				k=(k+up)/2;
			}
		/*n=recv(cli_sd, str_r, MAXLINE, 0); //��server���� */
	/*char STR[MAXLINE]="";
	gets(STR);
    send(cli_sd, STR, strlen(STR)+1, 0);//�ǰe��echo server
    /*printf("server reply: %d (%d bytes)\n" ,number,strlen(str)+1); */
	}
	//���� WinSock DLL ���ϥ�
   	closesocket(serv_sd);
   	closesocket(cli_sd);
   	WSACleanup();
   	system("pause");
}
