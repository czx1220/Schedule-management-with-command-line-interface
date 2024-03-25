#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "mainstructure.h"
using namespace std;


//�õ�����Ĺ�ϣֵ 
unsigned int SDBMHash(char *str){
    unsigned int hash = 0;
    while (*str)
    {hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }
    return (hash & 0x7FFFFFFF);
}

//��ȡ�û�����̫����̫�̣���δ�����κ��ַ�����Ҫ���������� 
void ReadInput1(char *name)
{
	printf("Username:");
	standardize(name,64);//һ�����뺯��(��structure�ﶨ��)���������벢��ȥ��ǰ��Ŀո�
	
	//�ж����ֹ���
	while(length(name)<2)
	{
		printf("the username is too short\n");
		printf("please input something\n");
		printf("Username:");
		standardize(name,64);
	}

	//�ж����ֹ���
	while(length(name)>=60)
	{	printf("the username is too long\n");
		printf("Username:");
		standardize(name,64);
	}
}

//��ȡ���룬̫����̫�̣�С��10����Ҫ����������
void ReadInput2(char *password)
{   printf("the length of the password>10\n");
	printf("Password:");
	standardize(password,64);//һ�����뺯��(��structure�ﶨ��)���������벢��ȥ��ǰ��Ŀո�
	
	//�ж��������
	while(length(password)<10)
	{	printf("the password is too short\n");
		printf("the length of the password>10\n");
		printf("Password:");
		standardize(password,64);
	}

	//�ж��������
	while(length(password)>=60)
	{	printf("the password is too long\n");
		printf("Password:");
		standardize(password,64);
	} 
}

// ���û����������������û���Ϣ���ĵ�����Ϊ���˻������洢������ļ� 
void CreateAccount(char *name,char *password)
{
	FILE * pFile = fopen ("account.txt", "a");
    fprintf(pFile,"%s\n%d\n",name,SDBMHash(password));//�û���������û����ͬһ�У���Ϊ����֮��ķָ����ü���name�п��ܳ����κ��ַ��������д洢�����ڶ�ȡʱ�������ֶ��� 
    fclose (pFile);
    char temp[114];
    strcpy(temp,name);
    strcat(temp,"record.txt");//�� record.txt���Ƶ��û����� 
    FILE * qFile = fopen (temp, "w");
    fclose (qFile);
}

//��ȡ���е��˻�����Ϣ
int ReadAccount(namepwd * record){
	int i=0;
	FILE * pFile = fopen ("account.txt", "r");//��ֻ����ʽ�� ��������д�� 
		if(pFile==NULL) 
	{
		printf("cannot find account.txt\n");
		exit(0);//�ļ��򲻿����߲����ھ��˳� 
	}
	char buff[64];
	while (fgets(buff,64,pFile)&&strcmp(buff,"\n")!=0)
	{	buff[length(buff)-2]='\0';//fgets�Ὣ\n��'\0' �ֱ�洢��buff����λ�� ĩβ '\0'���ܳ���Ϊlength(buff) ��\nλ��buff[length(buff)-2]�������Ϊ'\0' 
		i++;
		if(i%2==1)
		strcpy(record[(i-1)/2].name,buff);
		else
		record[i/2-1].hash=intonum(buff);
	}
	fclose (pFile);
	return i/2;
}

 //��ֹ����ͬ�����˻��������ͬ�����˻��򷵻�0��û��ͬ�����˻��򷵻�1
bool AvoidRepitition(char* name,namepwd * record,int t)
{
	int i;
	for(i=0;i<t;i++)
	{
		if(strcmp(record[i].name,name)==0)
    	return 0;
    }
  return 1;
}

//���������û����Ƿ���� 
int TestAccount1(char* name,namepwd * record,int t)
{ 	int i;
    for(i=0;i<=t;i++)
	{
    	if(strcmp(record[i].name,name)==0)
    	return i;//�����ڣ���������record���������
	}
 	printf("no such an account\n");
  	return -1;
}

//��������Ƿ���ȷ��ͨ��ת����Ĺ�ϣֵ�Ƿ���ͬ����� 
bool TestAccount2(char* name,char* password,namepwd * record,int i)
{ 
    if(SDBMHash(password)==record[i].hash) 
    return 1;
	else
	{ 
		printf("wrong password\n");
    	return 0;
	}
}


void Part1Account(char *input1,char *input2){
	printf("my schedule\n");
	if(fopen ("account.txt", "r")==NULL)//�ļ�������ʱ 
	{	
		printf("please create an account.\n");
		ReadInput1(input1);
		ReadInput2(input2);
		CreateAccount(input1,input2);
		printf("create an account successfully.\n");
		printf("now your account is %s.\n",input1);
    }
	else
	{	int flag=1;
		while(flag)
		{	namepwd record[1000];
		 	int s=ReadAccount(record);
	 		printf("print 1 to log in.\n");//����1��¼ 
	 		printf("print 2 to create an account.\n");//����2�����˺� 
	 		printf("print 0 to exit.\n");//����0�˳� 
	 		char command1[32];
   		 	standardize(command1,32);
			while(intonum(command1)!=1&&intonum(command1)!=2&&intonum(command1)!=0)
			{
				printf("invalid input.\n");
				printf("please input again.\n");
				printf("print 1 to log in.\n");
				printf("print 2 to create an account.\n");
				printf("print 0 to exit.\n");
				standardize(command1,16);
			}
		switch(intonum(command1)){
		
		case 1:
			{
	 			printf("log in.\n");
	  			printf("Username:");
	 			standardize(input1,64);
				if(TestAccount1(input1,record,s)>-1)
				{ printf("Password:");
	    		standardize(input2,64);
	      		 if(TestAccount2(input1,input2,record,TestAccount1(input1,record,s)))
				   {
					printf("log in successfully.\n");
					printf("now your account is %s.\n",input1);
					flag=0;
	  				}
   				}
			}break;
		
		case 2:
			{
	 			printf("create an account.\n");
				ReadInput1(input1);
				if(AvoidRepitition(input1,record,s))
				{	ReadInput2(input2);
					CreateAccount(input1,input2);
					printf("create an account successfully.\n");
					printf("now your account is %s.\n",input1);
					flag=0;
   				}
   				else
					printf("the account has already existed!\n");
			}break;

		case 0:
	   			exit(0);//�˳����� 
				break;
		}
    	}
   }
}
