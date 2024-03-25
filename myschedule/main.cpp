#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "account.h"
#include "tasksave.h"
#include "mainstructure.h"
using namespace std;

char filename[64];
bool WhetherRemind[1000];
struct task taskrecord[1000];	
int s;
 
pthread_mutex_t mutex0 = PTHREAD_MUTEX_INITIALIZER;

//线程函数1
void *pthread_func1(void *arg) { 	
	bool flag=1; 
    while(flag)
	{
 		int pthread_mutex_lock(pthread_mutex_t *mutex0);   
		s=ReadTask(filename,taskrecord);	//对struct task taskrecord[1000]进行任何改动后都去覆盖原文件，每次循环都重新读取原文件的内容 
		int pthread_mutex_unlock(pthread_mutex_t *mutex0);
		
		printf("\n");
		printf("do what\n");
		printf("show:show tasks\n");
		printf("add:add a task\n");
		printf("adjust:adjust a task\n");
		printf("delete:delete a task\n");
		printf("quit:exit\n");
		
		char command[64];
		command[0]='\0';
    	standardize(command,64);
	
	
		if(strcmp(command,"show")==0)
		{
    		ShowTask(taskrecord,s,mutex0);
		}
		else if(strcmp(command,"add")==0)
		{
			AddTask(taskrecord,s,mutex0);
	
			int pthread_mutex_lock(pthread_mutex_t *mutex0);//加锁 
			SortTask(taskrecord,s);//根据任务的提醒时间对任务进行排序，比较是否提醒时只要比较前几个任务的提醒 时间是否到达 
			SaveTask(filename,taskrecord,s);//对struct task taskrecord[1000]进行任何改动后都去覆盖原文件，每次循环都重新读取原文件的内容 
			int pthread_mutex_unlock(pthread_mutex_t *mutex0);//解锁 
	
		}
		else if(strcmp(command,"adjust")==0)
		{
			AdjustTask(taskrecord,s,mutex0);
	
			int pthread_mutex_lock(pthread_mutex_t *mutex0);//加锁 
			SortTask(taskrecord,s);
			SaveTask(filename,taskrecord,s);//对struct task taskrecord[1000]进行任何改动后都去覆盖原文件，每次循环都重新读取原文件的内容 
			int pthread_mutex_unlock(pthread_mutex_t *mutex0);//解锁 
	
		}
		else if(strcmp(command,"delete")==0)
		{
			DeleteTask(taskrecord,s,mutex0);
	
			int pthread_mutex_lock(pthread_mutex_t *mutex0);//加锁 
			SaveTask(filename,taskrecord,s);
			int pthread_mutex_unlock(pthread_mutex_t *mutex0);//解锁 
	
		}
		else if(strcmp(command,"quit")==0)
			exit(0);//退出程序 
		else
			printf("invalid input!\n");

	}

} 



//线程函数2
void *pthread_func2(void *arg){
	bool flag=1; 
    while(flag)
	{
    	int pthread_mutex_lock(pthread_mutex_t *mutex0);//加锁 
		Remind(taskrecord,s); 
		int pthread_mutex_unlock(pthread_mutex_t *mutex0);//解锁 
		sleep(5);
	}		
} 

int main(int argc, char * argv[]){
	int optchar;
   
    while((optchar = getopt(argc, argv, "h")) != -1)
	{
        switch(optchar) 
		{
        	case 'h':
            	usage(argv[0]);//后面加参数-h则显示帮助 
				exit(0);
		}
	}
	
	if(argc > 2) 
	{
		fprintf(stderr, " invalid input.\n");
		return -1;		
	}//后面参数数量大于2为无效 
	
	char input1[64];
	char input2[64];
	input1[0]='\0';
	input2[0]='\0';
	
	Part1Account(input1,input2);//进行输入用户名和密码等操作 
	
    for(int i=0;i<1000;i++)
    taskrecord[i].reminder=1;//一开始所有任务都需要提醒 
    
    
	strcpy(filename,input1);
	strcat(filename,"record.txt");
	
	pthread_t thread_id1; 
    pthread_t thread_id2;
	
	if(pthread_create(&thread_id1,NULL,pthread_func1,NULL)) 
	{ 
		printf("thread 1 failed!\n"); 
		return -1; 
	} //判断线程1是否创建成功 

	if(pthread_create(&thread_id2,NULL,pthread_func2,NULL)) 
	{ 
		printf("thread 1 failed!\n"); 
		return -1; 
	}//判断线程2是否创建成功 

	pthread_join(thread_id1,NULL); 
	pthread_join(thread_id2,NULL); 
	// 等待线程结束,释放线程的资源
	return 0;
} 
   
