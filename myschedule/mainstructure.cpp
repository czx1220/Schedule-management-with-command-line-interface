#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mainstructure.h"
using namespace std;
void usage(const char * cmd){
	printf("日程管理软件\n");
	printf("输入过程中会自动去掉前面与后面的空格\n") ;
	printf("创建过程id为当前时间，精确到秒\n");
	printf("创建过程中任务名称、属性、优先级允许缺省值，时间不允许缺省值\n");
	printf("任务名称缺省值为id，属性缺省值为default，优先级为中级\n");
	printf("展示任务过程中时间允许缺省值，不输入表示不对其进行搜索\n");
	return;
}//打印帮助 


void standardize(char *put,int n){
	fgets(put,n,stdin);//最多读取n个字符 ，最后的'\n'会被保留 
	setbuf(stdin , NULL);// 清除缓冲区，但fflush(stdin)仅适用于Windows，在linux中不起作用，故采用 setbuf( stdin , NULL)
	int i=0,t=0;
	while(put[t]!='\n'&&t<n)
		++t;
	--t;
	while(put[t]==' ')
		--t;
	put[t+1]='\0';
	while(put[i]==' ')
		++i;
	for(int j=i;j<=t+1;j++)
	{
		put[j-i]=put[j];
	}	
}//读取输入并去除输入的字符串前面与后面的空格，但中间的空格可以保留下来 

int length(char* str){
	int i=0;
	while(str[i]!='\0')++i;
	return i+1;
}
//读取输入的字符串从首位到末尾'\0'的总长度
int intonum(char *put){
	if(strcmp(put,"")==0)
	return -1;
	for(int j=0;j<length(put)-1;j++){
		if(put[j]>'9'||put[j]<'0')
		return -1;
	}
	return atoi(put);
}

