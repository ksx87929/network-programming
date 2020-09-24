#include <stdio.h>
#include <string.h>
#include <winsock.h>
#include <time.h>
#define MAXLINE 1024    /* �r��w�İϪ��� */

void main()
{
	printf("---------------------------����---------------------------\n"); 
	SOCKET	serv_sd, cli_sd;        /* socket �y�z�l */
  	int   	cli_len, n,total=0;
  	char  	str[1024],str_r[1024];

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
   	clock_t c1,c2;
   	
   	//while(1)
   	//{
		cli_len = sizeof(cli); 		
		cli_sd=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);		
		c1=clock();
		int time=0;	
		while(1)
		{
			n=recv(cli_sd, str_r, MAXLINE, 0); //��server���� 
			total = total + n;
			//printf("server recv: %d bytes, total:%d \n",n,total); 
			if(total%104857600==0)
		   	{
		   		c2=clock();
		   		time=c2-c1;
		   		c1=c2;
		   		printf("�C����100M bytes ��ƯӮ� %d sec \n",time);
		   	}
		   	//printf("�C����100M bytes ��ƯӮ� %d sec \n",total);
			if( total == 1073741824)	
				break;		
		}
		closesocket(cli_sd);
		/*if( n == 0)	
			break;*/	    
	//}
	
	
	printf("---------------------------�ǰe---------------------------\n");
	cli_len = sizeof(cli); 		
	cli_sd=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);
	int i=1;
	memset(str,"1",MAXLINE);
	for (i=1;i<1048577;i++)
   {
	   send(cli_sd, str, strlen(str)+1, 0); //�ǰe
	   //total = total + n;
	   //printf( "client send:%d bytes, total:%d\n",n,total); 
	   if(i%102400==0)
	   {
	   		c2=clock();
	   		time=c2-c1;
	   		c1=c2;
	   		printf("�C�ǰe100M bytes ��ƯӮ� %d msec \n",time);
	   }
   }
	
    //printf("�C����ƶq %d bytes/sec \n",ans);
	//���� WinSock DLL ���ϥ�
   	closesocket(serv_sd);

   	WSACleanup();
   	system("pause");
}

