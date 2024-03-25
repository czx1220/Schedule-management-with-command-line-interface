#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "mainstructure.h"
using namespace std;


//得到密码的哈希值 
unsigned int SDBMHash(char *str){
    unsigned int hash = 0;
    while (*str)
    {hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }
    return (hash & 0x7FFFFFFF);
}

//读取用户名，太长或太短（即未输入任何字符）均要求重新输入 
void ReadInput1(char *name)
{
	printf("Username:");
	standardize(name,64);//一个输入函数(在structure里定义)，可以输入并且去除前后的空格
	
	//判断名字过短
	while(length(name)<2)
	{
		printf("the username is too short\n");
		printf("please input something\n");
		printf("Username:");
		standardize(name,64);
	}

	//判断名字过长
	while(length(name)>=60)
	{	printf("the username is too long\n");
		printf("Username:");
		standardize(name,64);
	}
}

//读取密码，太长或太短（小于10）均要求重新输入
void ReadInput2(char *password)
{   printf("the length of the password>10\n");
	printf("Password:");
	standardize(password,64);//一个输入函数(在structure里定义)，可以输入并且去除前后的空格
	
	//判断密码过短
	while(length(password)<10)
	{	printf("the password is too short\n");
		printf("the length of the password>10\n");
		printf("Password:");
		standardize(password,64);
	}

	//判断密码过长
	while(length(password)>=60)
	{	printf("the password is too long\n");
		printf("Password:");
		standardize(password,64);
	} 
}

// 将用户名和密码存入记载用户信息的文档，并为该账户创建存储任务的文件 
void CreateAccount(char *name,char *password)
{
	FILE * pFile = fopen ("account.txt", "a");
    fprintf(pFile,"%s\n%d\n",name,SDBMHash(password));//用户名和密码没放在同一行，因为二者之间的分隔不好鉴别，name中可能出现任何字符，分两行存储便于在读取时进行区分二者 
    fclose (pFile);
    char temp[114];
    strcpy(temp,name);
    strcat(temp,"record.txt");//将 record.txt复制到用户名后 
    FILE * qFile = fopen (temp, "w");
    fclose (qFile);
}

//读取所有的账户的信息
int ReadAccount(namepwd * record){
	int i=0;
	FILE * pFile = fopen ("account.txt", "r");//以只读方式打开 ，不允许写入 
		if(pFile==NULL) 
	{
		printf("cannot find account.txt\n");
		exit(0);//文件打不开或者不存在就退出 
	}
	char buff[64];
	while (fgets(buff,64,pFile)&&strcmp(buff,"\n")!=0)
	{	buff[length(buff)-2]='\0';//fgets会将\n与'\0' 分别存储，buff从首位到 末尾 '\0'的总长度为length(buff) ，\n位于buff[length(buff)-2]，将其改为'\0' 
		i++;
		if(i%2==1)
		strcpy(record[(i-1)/2].name,buff);
		else
		record[i/2-1].hash=intonum(buff);
	}
	fclose (pFile);
	return i/2;
}

 //防止创建同名的账户，如果有同名的账户则返回0，没有同名的账户则返回1
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

//检测输入的用户名是否存在 
int TestAccount1(char* name,namepwd * record,int t)
{ 	int i;
    for(i=0;i<=t;i++)
	{
    	if(strcmp(record[i].name,name)==0)
    	return i;//若存在，返回其在record数组中序号
	}
 	printf("no such an account\n");
  	return -1;
}

//检测密码是否正确，通过转化后的哈希值是否相同来检测 
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
	if(fopen ("account.txt", "r")==NULL)//文件不存在时 
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
	 		printf("print 1 to log in.\n");//输入1登录 
	 		printf("print 2 to create an account.\n");//输入2创建账号 
	 		printf("print 0 to exit.\n");//输入0退出 
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
	   			exit(0);//退出程序 
				break;
		}
    	}
   }
}
