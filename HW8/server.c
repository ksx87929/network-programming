#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024    /* �r��w�İϪ��� */

void main()
{
	SOCKET	serv_sd, cli_sd[10],new_sd;        /* socket �y�z�l */
  	int   	cli_len, n=0,i,num_client=0;
  	char  	str[MAXLINE];

  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;

    WSAStartup(0x101, &wsadata); //�I�s WSAStartup() ���U WinSock DLL ���ϥ�

  	serv_sd=socket(AF_INET, SOCK_STREAM, 0);// �}�� TCP socket

   	//���w socket �� IP ��}�M port number
   	serv.sin_family      = AF_INET;
   	serv.sin_addr.s_addr = 0;
   	serv.sin_port        = htons(5678);	// ���w IPPORT_ECHO �� echo port

    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));

   	listen(serv_sd, 5) ; //�I�s listen() �� socket �i�J�u��ť�v���A
   	cli_len = sizeof(cli);
   	printf("waiting for server\n");
   	u_long iMode=1;
   	ioctlsocket(serv_sd,FIONBIO,&iMode);

   	while (1)
	{
       	//enable non-blocking mode when iMode=1

		if( (new_sd=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len)) != -1 )
		{
			printf("server get a new client %d\n",num_client+1);
			cli_sd[num_client]=new_sd;
			ioctlsocket(cli_sd[num_client],FIONBIO,&iMode);
			num_client++;
		}
		/*if (iMode ==0)
			printf("This is blocking mode.\n");
		else
       		printf("This is non-blocking mode.\n");*/

	    for(i=0;i<num_client;i++)
		{

			n=recv(cli_sd[i], str, MAXLINE, 0);
			if (n > 0 )
	    		printf("Recv from client %d : %s\n",num_client,str);

		   	// ��ܱq client �ǨӪ��r��
			int nError=WSAGetLastError();
			if(nError!=WSAEWOULDBLOCK && nError!=0)
			{
				int k=0;
				for(k=i;k<num_client-1;k++)
					cli_sd[k]=cli_sd[k+1];
				printf("Disconnected! error code:%d\n",nError);
				num_client--;
				break;
			}
		}

    }
	//���� WinSock DLL ���ϥ�
   	closesocket(serv_sd);

   	WSACleanup();
}
