#include<stdio.h>
#include<winsock.h>
#define MAXRECV 1024
#define MAXCLI 5
int main(int argc , char *argv[])
{
	WSADATA wsadata;
	SOCKET serv_sd , new_socket,cli_sd[MAXCLI];
	struct sockaddr_in serv, cli;

	int activity, cli_len, i, n, client_num=0;
	fd_set readfds;  //set of socket descriptors
	char str[MAXRECV];

	for(i=0;i<MAXCLI;i++)
		cli_sd[i]=0;

	WSAStartup(0x101, &wsadata); //�I�s WSAStartup() ���U WinSock DLL ���ϥ�

	serv_sd=socket(AF_INET, SOCK_STREAM, 0);// �}�� TCP socket

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = INADDR_ANY;
	serv.sin_port = htons( 5678 );

	bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));

	listen(serv_sd , 3);


	while(TRUE)
	{

	//	printf("[1]clear the socket fd set. \n");
		FD_ZERO(&readfds);

	//	printf("[2]add serv_sd  to fd set \n");
		FD_SET(serv_sd, &readfds);

	//	printf("[2]add cli_sd[]  to fd set \n");
		for(i=0;i<MAXCLI;i++)
			if(cli_sd[i]>0)
				FD_SET(cli_sd[i], &readfds);

		//wait for an activity on any of the sockets, timeout is NULL , so wait indefinitely
	//	printf("[3]call select() and waiting \n");
		activity = select( 0 , &readfds , NULL , NULL , NULL);
	//	printf("[4]wake up from select()\n");

		if ( activity == SOCKET_ERROR )
		{
			printf("select call failed with error code : %d" , WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		//check serv_sd -> accept(),add new client into cli_sd[]
		if (FD_ISSET(serv_sd , &readfds))
		{
			cli_len = sizeof(cli);
			new_socket = accept(serv_sd , (struct sockaddr *)&cli, (int *)&cli_len);
			if(client_num >= 5)
			{
				strcpy(str,"�t�Τw�� �u��");
				send( new_socket , str , strlen(str)+1 , 0 );
				client_num--;
			}
			for(i=0;i<MAXCLI;i++)
			{
				if(cli_sd[i]==0)
				{
					printf("New connection: socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(cli.sin_addr) , ntohs(cli.sin_port));
					int j;
					strcpy(str,"���s�����[�J");
						for(j=0;j<MAXCLI;j++)
					send( cli_sd[j] , str , strlen(str)+1 , 0 );
					cli_sd[i]=new_socket;
					client_num ++;
					printf("The %d client socket is in cli_sd[%d]\n",client_num,i);
					break;
				}
			}
		}


		//check each cli_sd client 1 presend in read sockets
		for(i=0;i<MAXCLI;i++)
		{
			if(FD_ISSET( cli_sd[i] , &readfds) )
			{
				n = recv( cli_sd[i] , str, MAXRECV, 0);
				if( n == SOCKET_ERROR)
				{
					int error_code = WSAGetLastError();
					if(error_code == WSAECONNRESET)
					{
					//Somebody disconnected , get his details and print
						printf("Host disconnected unexpectedly\n");
						closesocket( cli_sd[i] );
						cli_sd[i] = 0;
						client_num --;
					}
					else
						printf("recv failed with error code : %d" , error_code);
				}
				if ( n == 0)
				{
					//Somebody disconnected , get his details and print
					printf("Host disconnected. \n" );
						closesocket( cli_sd[i] );
						cli_sd[i] = 0;
						client_num --;
				}
				if (n > 0)
				{
					int j=0;
					printf("cli[%d] say : %s \n" ,i, str);
					for(j=0;j<MAXCLI;j++)
						send( cli_sd[j] , str , strlen(str)+1 , 0 );
				}//if
			}
		}//for
	}// while

	closesocket(serv_sd);

	WSACleanup();
	system("pause");

	return 0;
}
