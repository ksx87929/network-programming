#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 20    /* 字串緩衝區長度 */


void main()
{
	SOCKET	serv_sd,serv_sd2;        /* socket 描述子 */
  	int   	cli_len, cli2_len,n,i=1;
  	char  	str[MAXLINE];
  	struct 	sockaddr_in   	serv, cli,cli2;
  	WSADATA wsadata;
	int port1=7777,port2=7778,port3=7779,port=7780;
   	char ip1[10]="224.1.1.1",ip2[10]="224.1.1.2",ip3[10]="224.1.1.3";          
   	char ch1[1024]="224.1.1.1 port : 7777 channel1 : 11111111",ch2[1024]="224.1.1.2 port : 7778 channel2 : aaaaaaaa",ch3[1024]="224.1.1.3 port : 7779 channel3 : AAAAAAAA";
   	
    WSAStartup(0x101, &wsadata); //呼叫 WSAStartup() 註冊 WinSock DLL 的使用
	
   	serv_sd=socket(AF_INET, SOCK_DGRAM, 0);// 開啟 UDP socket
   	serv_sd2=socket(AF_INET, SOCK_DGRAM, 0);// 開啟 UDP socket
   	
   	// for broadcast
   	//char broadcast = 'a';
	//setsockopt(serv_sd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));

   	    /* Set TTL of multicast packet */
   	int multicastTTL=1;
   	char broadcast = 'a';
	setsockopt(serv_sd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));   	
   	cli_len = sizeof(cli);
   	               
    cli.sin_family      = AF_INET;
   	cli.sin_addr.s_addr = inet_addr("255.255.255.255");
   	cli.sin_port        = htons(port);
   	
   	int state=1,state2=2;
   	cli_len = sizeof(cli);
   	cli2_len = sizeof(cli2);
   	
   	printf("server will multicastcast.\n");
   	
   	
while(1)
	{	
			sendto(serv_sd, ch1, strlen(ch1), 0,(LPSOCKADDR)&cli,cli_len);        
	       	printf("server broadcast: %s\n",ch1);
	       	sendto(serv_sd, ch2, strlen(ch2), 0,(LPSOCKADDR)&cli,cli_len);        
	       	printf("server broadcast: %s\n",ch2);
	       	sendto(serv_sd, ch3, strlen(ch3), 0,(LPSOCKADDR)&cli,cli_len);        
	       	printf("server broadcast: %s\n",ch3);
	       	sleep(1);
	
	
			if (setsockopt(serv_sd2, IPPROTO_IP, IP_MULTICAST_TTL, (char *) &multicastTTL, sizeof(multicastTTL)) == SOCKET_ERROR)
    			printf("setsockopt() failed");	

			cli2.sin_family      = AF_INET;
		   	cli2.sin_addr.s_addr = inet_addr(ip1);
		   	cli2.sin_port        = htons(7777);
			sendto(serv_sd2, "11111111" , 8, 0,(LPSOCKADDR)&cli2,cli2_len);
			printf("server multicast: %s\n",ip1);		// 顯示送去client 的字串	
	       
	        
	        cli2.sin_family      = AF_INET;
		   	cli2.sin_addr.s_addr = inet_addr(ip2);
		   	cli2.sin_port        = htons(7778);
			sendto(serv_sd2, "aaaaaaaa", 8, 0,(LPSOCKADDR)&cli2,cli2_len);
			printf("server multicast: %s\n",ip2);		// 顯示送去client 的字串	
	        
	        
	        cli2.sin_family      = AF_INET;
		   	cli2.sin_addr.s_addr = inet_addr(ip3);
		   	cli2.sin_port        = htons(7779);
			sendto(serv_sd2,"AAAAAAAA", 8, 0,(LPSOCKADDR)&cli2,cli2_len);
			printf("server multicast: %s\n",ip3);		// 顯示送去client 的字串
				
	        sleep(1);
	        
	}
        
	//結束 WinSock DLL 的使用
   	closesocket(serv_sd);
   	//closesocket(cli_sd);
   	WSACleanup();
}
