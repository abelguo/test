/*************************************************************************
  > File Name: sampletelnet.c
  > Author: guoyong
  > Mail: abelguoyong@qq.com 
  > Created Time: Thu 03 Jul 2014 22:56:50 CST
 ************************************************************************/
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<errno.h>
#include<setjmp.h>
#include<signal.h>
static  jmp_buf jmpbuf;
void mysignal(int SIG)
{
	if(SIG==SIGALRM)
		longjmp(jmpbuf,1);
}
int opentelnet(char *addr,short port,char *usrname,char *pwd)
{
	int clientsocket;
	struct sockaddr_in server;
	char a[100];
	if(-1==(clientsocket=socket(AF_INET,SOCK_STREAM,0)))
	{
		perror("socket");
		return -1;
	}
	memset(&server,0,sizeof(struct sockaddr_in));
	server.sin_family=AF_INET;
	server.sin_port=htons(port);
	server.sin_addr.s_addr=inet_addr(addr);
	if(-1==(connect(clientsocket,(struct sockaddr *)&server,sizeof(server))))
	{
		perror("connect");
		close(clientsocket);
		return -1;
	}
	signal(SIGALRM,mysignal);
	if(setjmp(jmpbuf)!=0)
	{
		close(clientsocket);
		return -2;
	}
	alarm(1);
	if(strcmp(usrname,"NA")==0)
	{
		alarm(0);
		return clientsocket;
	}
	memset(a,0,100);
	recv(clientsocket,a,sizeof(a),0);
if(strstr(a,"ogin:")!=NULL||strstr(a,"name:")!=NULL)
	{
		memset(a,0,100);
		sprintf(a,"%s\n",usrname);
		send(clientsocket,a,strlen(a),0);
	}
	else
	{
		printf("ogin failed %s\n",a);
		alarm(0);
		return -1;

	}
	if(strcmp(pwd,"NA")!=0)
	{
		memset(a,0,100);
		recv(clientsocket,a,sizeof(a),0);
		if(strstr(a,":")!=NULL)
		{
			memset(a,0,100);
			sprintf(a,"%s\n",pwd);
			send(clientsocket,a,strlen(a),0);
		}
		else
		{
			printf("passwd failed \n");
			alarm(0);
			return -1;

		}
	}
	alarm(0);
	return clientsocket;
}
int cmd(int sock,char *cmd,char *waitfor)
{
	int num;
	char wait[50];
	memset(wait,0,50);
	if(send(sock,cmd,strlen(cmd),0)<0)
	{
		perror("send");
		return -1;
	}
	signal(SIGALRM,mysignal);
	if(setjmp(jmpbuf)!=0)
	{
		return -2;
	}
	alarm(10);
	if(waitfor==NULL)
	{
		return 0;
	}
	while(1)
	{
		if(recv(sock,wait,sizeof(wait)-1,0)<0)
		{
			perror("send");
			return -1;
		}
		else
		{
			if(strstr(wait,waitfor)!=NULL)
				return 0;
			else
			{
				printf("%s",wait);
				memset(wait,0,50);
			}
		}
	}
}
int main(int argc,char *argv[])
{
	int fd;
	int errn;
	short port;
	if(argc<5)
	{
		printf("you must input four paramer\n");
		return -1;
	}
	port=(short)atoi(argv[2]);
	printf("%s   %s\n",argv[0],argv[1]);
	fd=opentelnet(argv[1],port,argv[3],argv[4]);
	if(fd<0)
	{
		printf("opentelnet is failed \n");
		return -1;
	}
	else
		if((errn=cmd(fd,"ls\n\t","~$"))<0)
		{
			switch(errn)
			{
				case -2:
					printf("timeout \n");
					break;
				default:
					break;
			}
		}
		else 
		{
			cmd(fd,"exit\n",NULL);
			close(fd);
		}
}
