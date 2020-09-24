#include <stdio.h>      /* for printf(), fprintf() */
#include <winsock.h>    /* for socket(),... */
#include <stdlib.h>     /* for exit() */

void *ThreadMain(void *arg);             /* Main program of a thread */

struct ThreadArgs /* Structure of arguments to pass to client thread */
{
    int clntSock;                      /* Socket descriptor for client */
    int num;
};

int cli[10]={0},cnum=0;

int main(int argc, char *argv[])

{
	struct ThreadArgs *threadArgs;   /* Pointer to argument structure for thread */
    DWORD  threadID;                 /* Thread ID from CreateThread() */
	char str[1024];
	int servSock;                    /* Socket descriptor for server */
    int clntSock,j=0,i,new;                    /* Socket descriptor for client */
    WSADATA wsaData;                 /* Structure for WinSock setup communication */
	struct sockaddr_in echoServAddr; /* Local address */
    struct sockaddr_in echoClntAddr; /* Client address */
 	unsigned int clntLen;            /* Length of client address data structure */

	if (WSAStartup(0x101, &wsaData) != 0) /* Load Winsock 2.0 DLL */
    {
        printf("WSAStartup() failed");
        exit(1);
    }

	/* Create socket for incoming connections */
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        printf("socket() failed");

    /* Construct local address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));   /* Zero out structure */
    echoServAddr.sin_family = AF_INET;                /* Internet address family */
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    echoServAddr.sin_port = htons(5678);              /* Local port */

    /* Bind to the local address */
    if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        printf("bind() failed");

    /* Mark the socket so it will listen for incoming connections */
    if (listen(servSock, 3) < 0)
        printf("listen() failed");

    printf("Server is waiting for clients.\n");
    for (;;) /* Run forever */
    {
	    clntLen = sizeof(echoClntAddr);

	    /* Wait for a client to connect */
	    /*if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0)
	        printf("accept() failed");*/

		clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen);
		if(cnum>=5)
		{
			strcpy(str,"人數已滿");
			send(clntSock,str,strlen(str)+1,0);
			closesocket(clntSock);
		}
		else
		{
			for(i=0;i<5;i++)
			{
				if(cli[i]==0)
				{
					cli[i]=clntSock;
					new=i;
					cnum++;
					printf("The %d client socket is in cli_sd[%d]\n",cnum,i);
					threadArgs = (struct ThreadArgs *) malloc(sizeof(struct ThreadArgs));
			        threadArgs -> clntSock = clntSock;
			        threadArgs -> num = new+1;

			        if (CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) ThreadMain, threadArgs, 0, (LPDWORD) &threadID) == NULL)
			            printf("thread_create() failed");

			        printf("New client with thread ID: %ld and socket:%d\n", threadID,clntSock);
			        printf("New client cnum:%d and cli_sd:%d\n", cnum,cli[cnum-1]);
					break;
				}
			}
			strcpy(str,"有新成員加入聊天室!!!");
			for(j=0;j<10;j++)
			{
				if(cli[j]>0)
				{
					if(j!=new)
					{
						send(cli[j],str,strlen(str)+1,0);
					}
				}
			}
		}

		/* Create separate memory for client argument */

    }
}// end main



void *ThreadMain(void *threadArgs)
{
    int clntSock,j,i,num;                   /* Socket descriptor for client connection */
    /* Extract socket file descriptor from argument */
    clntSock = ((struct ThreadArgs *) threadArgs) -> clntSock;
	num = ((struct ThreadArgs *) threadArgs) -> num;

	char echoBuffer[1000];        /* Buffer for echo string */
    int recvMsgSize;                    /* Size of received message */
	char who[10];
    /* Send received string and receive again until end of transmission */
    while (1)      /* zero indicates end of transmission */
    {
        /* Receive message from client */
        if ((recvMsgSize = recv(clntSock, echoBuffer, 1000, 0)) < 0)
        {
			int error_code=WSAGetLastError();
			if(error_code==WSAECONNRESET)
			{
				printf("Host disconnected unexpectedly\n");
				closesocket(clntSock);    /* Close client socket */
				cli[num-1]=0;
				cnum--;
				break;
			}
			else
				printf("recv failed with erroe code : %d\n",error_code);
		}
    		//printf("recv() failed");
        /* Echo message back to client */
        for(j = 0 ; j < 10 ; j++)
        {
        	if(cli[j]!=clntSock)
        	{
				sprintf(who, "%d", num);
   				//printf("str = %s\n", str);
   				strcat(who," : ");
   				strcat(who,echoBuffer);
	        	send(cli[j], who, strlen(who)+1, 0);
			}
		}
    }
    free(threadArgs);
    return (NULL);
}
