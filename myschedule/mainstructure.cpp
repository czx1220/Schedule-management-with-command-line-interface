#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mainstructure.h"
using namespace std;
void usage(const char * cmd){
	printf("�ճ̹������\n");
	printf("��������л��Զ�ȥ��ǰ�������Ŀո�\n") ;
	printf("��������idΪ��ǰʱ�䣬��ȷ����\n");
	printf("�����������������ơ����ԡ����ȼ�����ȱʡֵ��ʱ�䲻����ȱʡֵ\n");
	printf("��������ȱʡֵΪid������ȱʡֵΪdefault�����ȼ�Ϊ�м�\n");
	printf("չʾ���������ʱ������ȱʡֵ���������ʾ�������������\n");
	return;
}//��ӡ���� 


void standardize(char *put,int n){
	fgets(put,n,stdin);//����ȡn���ַ� ������'\n'�ᱻ���� 
	setbuf(stdin , NULL);// �������������fflush(stdin)��������Windows����linux�в������ã��ʲ��� setbuf( stdin , NULL)
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
}//��ȡ���벢ȥ��������ַ���ǰ�������Ŀո񣬵��м�Ŀո���Ա������� 

int length(char* str){
	int i=0;
	while(str[i]!='\0')++i;
	return i+1;
}
//��ȡ������ַ�������λ��ĩβ'\0'���ܳ���
int intonum(char *put){
	if(strcmp(put,"")==0)
	return -1;
	for(int j=0;j<length(put)-1;j++){
		if(put[j]>'9'||put[j]<'0')
		return -1;
	}
	return atoi(put);
}

