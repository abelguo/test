/*************************************************************************
  > File Name: main.c
  > Author: guoyong
  > Mail: abelguoyong@qq.com 
  > Created Time: Sat 21 Jun 2014 23:17:26 CST
 ************************************************************************/
#include"readfile.h"
#include<stdio.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
	int a;
	char *file;
	if(argc<2)
	{
		printf("you must input file name\n");
		return -1;

	}
	file=(char *)My_Map(argv[1]);
	printf("the number is %s\n",file);
	if((a=Get_Int(argv[2],argv[3],file))==-1)
	{
		printf("have error\n");
		return -1;
	}
	printf("the number is %d\n",a);
	printf("the number is %d\n",a);
	printf("the number is %d\n",a);
	printf("the number is %d\n",a);
	printf("the number is %d\n",a);
	printf("the number is %d\n",a);
	printf("the number is %d\n",a);
	printf("the number is %d\n",a);
	printf("the number is %d\n",a);
	printf("the number is %d\n",a);
	printf("the number is %d\n",a);
	my_umap(file);
	return (EXIT_SUCCESS);
}
