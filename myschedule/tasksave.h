#ifndef TASK_H
#define TASK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include "mainstructure.h"
using namespace std;


struct task{
	long long int id;
	int level;//���ȼ���1Ϊ�ߣ�2Ϊ�У�3Ϊ�ͣ�
	char classification[114];//����
	char name[114];//���� 
	bool reminder;//��ʾ�Ƿ��Ѿ����ѹ����Ƿ���Ҫ������ �������ѹ����ֵΪ0��������޸Ĺ��������reminderΪ1 
    tm detail;  //����ʱ�� ��tmΪtime.h�Դ��Ľṹ�� 
    tm remind;//����ʱ�� 
};

void add0(int a);

void display(task exa);

bool TestDate(char* input1,char* input2,char* input3);

long long int Transform(tm exa);

long long int Transform2(tm* exa);

long long int PresentTime();

long long int PresentTimeSecond();

bool ReceiveTime2(char* year,char* month,char* day,char* hour,char* minute);

void ReceiveTime(tm *exa,pthread_mutex_t mutex0);

bool Compare(const int a,const int b);

void ToString(long long int num,char* str);

int SearchTask(task* record,int s,pthread_mutex_t mutex0);

void ShowTask(task* record,int s,pthread_mutex_t mutex0);

void AddTask(task* record,int &s,pthread_mutex_t mutex0);

void AdjustTask(task* record,int s,pthread_mutex_t mutex0);

void DeleteTask(task* record,int& s,pthread_mutex_t mutex0 );

void SortTask(task* record,int s);

void SaveTask(char* x,task* record,int s);

int Readint(char* str);

int ReadTask(const char*x,task* record);

void Remind(task* record,int s);



#endif
