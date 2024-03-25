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

//�̺߳���1
void *pthread_func1(void *arg) { 	
	bool flag=1; 
    while(flag)
	{
 		int pthread_mutex_lock(pthread_mutex_t *mutex0);   
		s=ReadTask(filename,taskrecord);	//��struct task taskrecord[1000]�����κθĶ���ȥ����ԭ�ļ���ÿ��ѭ�������¶�ȡԭ�ļ������� 
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
	
			int pthread_mutex_lock(pthread_mutex_t *mutex0);//���� 
			SortTask(taskrecord,s);//�������������ʱ�������������򣬱Ƚ��Ƿ�����ʱֻҪ�Ƚ�ǰ������������� ʱ���Ƿ񵽴� 
			SaveTask(filename,taskrecord,s);//��struct task taskrecord[1000]�����κθĶ���ȥ����ԭ�ļ���ÿ��ѭ�������¶�ȡԭ�ļ������� 
			int pthread_mutex_unlock(pthread_mutex_t *mutex0);//���� 
	
		}
		else if(strcmp(command,"adjust")==0)
		{
			AdjustTask(taskrecord,s,mutex0);
	
			int pthread_mutex_lock(pthread_mutex_t *mutex0);//���� 
			SortTask(taskrecord,s);
			SaveTask(filename,taskrecord,s);//��struct task taskrecord[1000]�����κθĶ���ȥ����ԭ�ļ���ÿ��ѭ�������¶�ȡԭ�ļ������� 
			int pthread_mutex_unlock(pthread_mutex_t *mutex0);//���� 
	
		}
		else if(strcmp(command,"delete")==0)
		{
			DeleteTask(taskrecord,s,mutex0);
	
			int pthread_mutex_lock(pthread_mutex_t *mutex0);//���� 
			SaveTask(filename,taskrecord,s);
			int pthread_mutex_unlock(pthread_mutex_t *mutex0);//���� 
	
		}
		else if(strcmp(command,"quit")==0)
			exit(0);//�˳����� 
		else
			printf("invalid input!\n");

	}

} 



//�̺߳���2
void *pthread_func2(void *arg){
	bool flag=1; 
    while(flag)
	{
    	int pthread_mutex_lock(pthread_mutex_t *mutex0);//���� 
		Remind(taskrecord,s); 
		int pthread_mutex_unlock(pthread_mutex_t *mutex0);//���� 
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
            	usage(argv[0]);//����Ӳ���-h����ʾ���� 
				exit(0);
		}
	}
	
	if(argc > 2) 
	{
		fprintf(stderr, " invalid input.\n");
		return -1;		
	}//���������������2Ϊ��Ч 
	
	char input1[64];
	char input2[64];
	input1[0]='\0';
	input2[0]='\0';
	
	Part1Account(input1,input2);//���������û���������Ȳ��� 
	
    for(int i=0;i<1000;i++)
    taskrecord[i].reminder=1;//һ��ʼ����������Ҫ���� 
    
    
	strcpy(filename,input1);
	strcat(filename,"record.txt");
	
	pthread_t thread_id1; 
    pthread_t thread_id2;
	
	if(pthread_create(&thread_id1,NULL,pthread_func1,NULL)) 
	{ 
		printf("thread 1 failed!\n"); 
		return -1; 
	} //�ж��߳�1�Ƿ񴴽��ɹ� 

	if(pthread_create(&thread_id2,NULL,pthread_func2,NULL)) 
	{ 
		printf("thread 1 failed!\n"); 
		return -1; 
	}//�ж��߳�2�Ƿ񴴽��ɹ� 

	pthread_join(thread_id1,NULL); 
	pthread_join(thread_id2,NULL); 
	// �ȴ��߳̽���,�ͷ��̵߳���Դ
	return 0;
} 
   
