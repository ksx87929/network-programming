#include <stdio.h>
#include <string.h>
#include <winsock.h>
#include <time.h> 
#define MAXLINE 1024    /* �r��w�İϪ��� */

void main()
{
	printf("---------------------------server recive---------------------------\n");
	SOCKET	serv_sd;        /* socket �y�z�l */
  	int   	cli_len, n;
  	char  	str[MAXLINE],str_r[MAXLINE];
  	
  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;
    WSAStartup(0x101, &wsadata); //�I�s WSAStartup() ���U WinSock DLL ���ϥ�
  	serv_sd=socket(AF_INET, SOCK_DGRAM, 0);// �}�� UDP socket
   	//���w socket �� IP ��}�M port number
   	serv.sin_family      = AF_INET;
   	serv.sin_addr.s_addr = 0;
   	serv.sin_port        = htons(5678);	// ���wport
    //bind(serv_sd, &serv, sizeof(serv)) ;
    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));
   	//listen(serv_sd, 5) ; //�I�s listen() �� socket �i�J�u��ť�v���A
   	cli_len = sizeof(cli);  		
	//cli_sd=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);
   	int total;
   	clock_t c1,c2;
   	c1=clock();
   	while(1)
   	{
	   	//printf("server waits for client\n");
	   	//n=recv(cli_sd, str_r, MAXLINE, 0); //��server���� 
	   	n=recvfrom(serv_sd, str_r, MAXLINE, 0,(LPSOCKADDR) &cli, &cli_len); //��server���� 
		total+=n;
		if(total%104857600==0)
		{	 
	  		int temp;
	   		c2=clock();
  	   		temp=c2-c1;
			c1=c2;
		   	printf("server recv: %d bytes , cost %d msec\n",total,temp);
		}
	    if(total==1073741824)
	    	break;
	}

    printf("---------------------------server send---------------------------\n");
	memset(str,'1',1023);
	int i=0;
	total=0;
	c1=clock();
	for(i=1;i<1048577;i++)
    {
		sendto(serv_sd, str, strlen(str)+1, 0,(LPSOCKADDR) &cli, cli_len); //�ǰe��echo server 
		total+=n;
		if(i%102400==0) 
		{
			int temp;
			c2=clock();
			temp=c2-c1;
	   		c1=c2;
			printf( "send : %d bytes , cost %d msec\n" ,total,temp);
		}
	}
    //printf("server reply: %s (%d bytes)\n" ,str,strlen(str)+1); 
    
	//���� WinSock DLL ���ϥ�
   	//closesocket(serv_sd);
   	//closesocket(cli_sd);
   	WSACleanup();
   	system("pause");
}
