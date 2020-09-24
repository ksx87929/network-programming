#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <winsock.h>

#define MAXLINE 1024

SOCKET        	sd;
struct sockaddr_in serv;
char  		str[1024];
char  		str_r[1024];
WSADATA 		wsadata;
int timeout = 50,n;

void *recvMess(void *argu) {    // �C�j�@�����L�X�@�� George �����
    while (1) {
        setsockopt(sd,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout));
		n=recv(sd, str_r, MAXLINE, 0); //�����Ӧۨ�Lclient���T��
		if(n>1)
            printf("recv: %s (%d bytes)\n",str_r,strlen(str_r)+1);
    }
}

int main(int argc, char** argv) {
   int n,i,j,total=0;
	pthread_t thread1;

   WSAStartup(0x101,(LPWSADATA) &wsadata); // �I�s WSAStartup() ���U WinSock DLL ���ϥ�


   sd=socket(AF_INET, SOCK_STREAM, 0); //�}�Ҥ@�� TCP socket.

   serv.sin_family       = AF_INET;
   serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   serv.sin_port         = htons(5678);

   connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // �s���� echo server


    pthread_create(&thread1, NULL, &recvMess, NULL);

	while(1){
		printf(">>");
		gets(str);
		send(sd, str, strlen(str)+1, 0); //�ǰe�T��
	}

   closesocket(sd); //����TCP socket

   WSACleanup();  // ���� WinSock DLL ���ϥ�
   system("pause");

   return 0;
}
