/*************************************************************************
  > File Name: readfile.c
  > Author: guoyong
  > Mail: abelguoyong@qq.com 
  > Created Time: Sat 21 Jun 2014 18:23:27 CST
 ************************************************************************/
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/fcntl.h>
#include<sys/unistd.h>
#include<sys/mman.h>
void *My_Map(char *File_Path)
{
	int fd;
	void *addr;
	off_t len;
	struct stat stat_buf;
	if((fd=open(File_Path,O_RDONLY))==-1)
	{
		perror("open");
		return (void*)-1;
	}
	fstat(fd,&stat_buf);
	len=stat_buf.st_size;
	if((addr=mmap(NULL,len,PROT_READ,MAP_SHARED,fd,0))==(void *)-1)
	{
		perror("mmap");
		return (void*)-1;
	}
	return addr;
}
int Get_Int(char *main,char *name,char *file)  //mian de 格式是【main】
{
	char My_main[100];
	char *mstart,*mend;
	char  *start;
	char  *my_int;
	if(strcmp(main,"NULL"))
	{
		sprintf(My_main,"[%s]",main);
		if((mstart=strstr(file,My_main))==NULL)
		{
#ifdef DEBUG
			printf("have no %s\n",main);
#endif
			return -1;
		}
	}
	else
	{
		mstart=file;
	}
	if((mend=strstr(mstart+strlen(My_main),"["))==NULL)
	{
		mend=file+strlen(file);
	}
	if((start=strstr(mstart,name))==NULL)
	{
		printf("have no %s\n",name);
		return -1;
	}
	if(isalpha(*(start+strlen(name)))||isalpha(*(start-1)))
	{
#ifdef DEBUG
		printf("have no %s\n",name);
#endif
		return -1;
	}
	if((long)start>(long)mend)
	{
#ifdef DEBUG
		printf("have no %s in %s\n",name,main);
#endif
		return -1;
	}
	my_int=strstr(start,"=");
	return atoi(my_int+1);
}
int Get_Str(char *str,long len,char *main ,char *name,char *file)
{
	return 0;
}
void my_umap(char *addr)
{
	munmap(addr,strlen(addr));
}

