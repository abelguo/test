/*************************************************************************
    > File Name: readfile.h
    > Author: guoyong
    > Mail: abelguoyong@qq.com 
    > Created Time: Sat 21 Jun 2014 20:00:59 CST
 ************************************************************************/
#ifndef READFILE_H
#define READFILE_H
int Get_Str(char *str,long len,char *main ,char *name,char *file);
int Get_Int(char *main,char *name,char *file);  //mian de 格式是【main】
void *My_Map(char *File_Path);
void my_umap(char *addr);
#endif
