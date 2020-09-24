#include <stdio.h>
#include <string.h>
#include <winsock.h>
#define MAXLINE 1024    /* 字串緩衝區長度 */

void main()
{
	SOCKET	serv_sd, cli_sd;        /* socket 描述子 */
  	int   	cli_len, n;
  	char  	str[MAXLINE],str_r[MAXLINE];

  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;

    WSAStartup(0x101, &wsadata); //呼叫 WSAStartup() 註冊 WinSock DLL 的使用

  	serv_sd=socket(AF_INET, SOCK_STREAM, 0);// 開啟 TCP socket

   	//指定 socket 的 IP 位址和 port number
   	serv.sin_family      = AF_INET;
   	serv.sin_addr.s_addr = 0;
   	serv.sin_port        = htons(5678);	// 指定port

    //bind(serv_sd, &serv, sizeof(serv)) ;
    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));

   	listen(serv_sd, 5) ; //呼叫 listen() 使 socket 進入「監聽」狀態

   	cli_len = sizeof(cli);
	printf("server waits for client\n");
	cli_sd=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);


   	n=recv(cli_sd, str_r, MAXLINE, 0); //由server接收

    LPHOSTENT hp,hn,nproto;
    LPSERVENT sp,pservice;
    LPPROTOENT pp,nump;
	struct in_addr sAddr;
    sAddr.s_addr=inet_addr(str_r);


    hp=gethostbyaddr((LPSTR) &sAddr, sizeof(sAddr),AF_INET);
	if(hp==NULL)
	    strcpy(str,"get hp error");
	else
		strcpy(str,hp->h_name);
    send(cli_sd, str, strlen(str)+1, 0); //傳送至echo server
    printf("server reply: %s (%d bytes)\n" ,str,strlen(str)+1);


    char str_rhn[1024]="";
    n=recv(cli_sd, str_rhn, MAXLINE, 0); //由server接收
    hn=gethostbyname(str_rhn);
    if(hn==NULL)
	    strcpy(str,"get hn error");
	else
		strcpy(str,hn->h_name);
	send(cli_sd, str, strlen(str)+1, 0); //傳送至echo server
    printf("server reply: %s (%d bytes)\n" ,str,strlen(str)+1);

    char str_rsp[1024]="";
    n=recv(cli_sd, str_rsp, MAXLINE, 0); //由server接收
    sp=getservbyname(str_rsp,"tcp");
    if(sp==NULL)
	    strcpy(str,"get sp error");
	else
		sprintf(str,"%d",ntohs(sp->s_port));
	send(cli_sd, str, strlen(str)+1, 0); //傳送至echo server
    printf("server reply: %s (%d bytes)\n" ,str,strlen(str)+1);

    char str_rpservice[1024]="";
    int port=0;
    n=recv(cli_sd, str_rpservice, MAXLINE, 0); //由server接收
    port=atoi(str_rpservice);
    pservice=getservbyport(htons((unsigned short)port),"tcp");
    if(pservice==NULL)
	    strcpy(str,"get pservice error");
	else
		strcpy(str,pservice->s_name);
    send(cli_sd, str, strlen(str)+1, 0); //傳送至echo server
    printf("server reply: %s (%d bytes)\n" ,str,strlen(str)+1);

    char str_rpp[1024]="";
    n=recv(cli_sd, str_rpp, MAXLINE, 0); //由server接收
    pp=getprotobyname(str_rpp);
    if(pp==NULL)
	    strcpy(str,"get pp error");
	else
		sprintf(str,"%d",pp->p_proto);
    send(cli_sd, str, strlen(str)+1, 0); //傳送至echo server
    printf("server reply: %s (%d bytes)\n" ,str,strlen(str)+1);

    char str_rnump[1024]="";
    int number=0;
    n=recv(cli_sd, str_rnump, MAXLINE, 0); //由server接收
    number=atoi(str_rnump);
    nump=getprotobynumber(number);
    if(nump==NULL)
    	strcpy(str,"get nump error");
    else
    	strcpy(str,nump->p_name);
    send(cli_sd, str, strlen(str)+1, 0); //傳送至echo server
    printf("server reply: %s (%d bytes)\n" ,str,strlen(str)+1);

    system("pause");

   	closesocket(serv_sd);
   	closesocket(cli_sd);
   	WSACleanup();
}
