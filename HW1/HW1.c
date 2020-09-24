#include <stdio.h>
#include <winsock.h>
#include<string.h>
int main(void){

char domain[100]="";
char domainend[100]="";
char temp[3]="";
printf("請輸入起始IP : \n");
scanf("%s",&domain);
printf("請輸入目的IP : \n");
scanf("%s",&domainend);
printf("\n");

int s=0,dot=0,ts=0,num1=0,num2=0;
int j=0;
for(s;s<strlen(domain);s++)
{
     if(dot==3)
    {
    	ts=s;
        for(ts;ts<strlen(domain);ts++)
        {
        	temp[j]=domain[ts];
        	j++;
        }
        num1=atoi(temp);
		break;
    }
    else if(domain[s]=='.')
         {
             dot++;
         }

}
//printf("%d\n",num1);
s=0;ts=0;dot=0;
for(s;s<strlen(domain);s++)
{
     if(dot==3)
    {
    	ts=s;
        for(ts;ts<strlen(domain);ts++)
        {
        	domain[ts]='\0';
        }
		break;
    }
    else if(domain[s]=='.')
         {
             dot++;
         }

}
s=0;ts=0;dot=0;j=0;
for(s;s<strlen(domainend);s++)
{
     if(dot==3)
    {
    	ts=s;
        for(ts;ts<strlen(domainend);ts++)
        {
        	temp[j]=domainend[ts];
        	j++;
        }
        num2=atoi(temp);
		break;
    }
    else if(domainend[s]=='.')
         {
             dot++;
         }

}
//printf("%d\n",num2);
//printf("%d\n",long1);
//int length=domainf[strlen(domainf)-1]-dom//ain[strlen(domain)-1];
//initial WSAStartup

int A=0;
A=num2-num1;

int i=0;
for( i=0;i<=A;i++)
{
	char temp1[3]="";
    itoa(num1,temp1,10);
    strcat(domain,temp1);

WSADATA 		wsadata;
int nResult=WSAStartup(0x101,(LPWSADATA) &wsadata);
if(nResult!=0)
{
	printf("WSA Initialization failed: %d\n",nResult);
	WSACleanup();
	return 0;
}

LPHOSTENT hp;
struct in_addr sAddr;
sAddr.s_addr=inet_addr(domain);

hp=gethostbyaddr((LPSTR) &sAddr, sizeof(sAddr),AF_INET);

if(hp==NULL)
    printf("none");
else{
	printf("%s's '",inet_ntoa(*(LPIN_ADDR)(hp->h_addr)));
    printf("host name:%s\n",hp->h_name);
    //printf("host nickname:%s\n",hp->h_aliases[0]);

}
 s=0;ts=0;dot=0;
    for(s;s<strlen(domain);s++)
    {
     if(dot==3)
    {
    	ts=s;
        for(ts;ts<strlen(domain);ts++)
        {
        	domain[ts]='\0';
        }
		break;
    }
    else if(domain[s]=='.')
         {
             dot++;
         }

    }
    num1++;
}
}
