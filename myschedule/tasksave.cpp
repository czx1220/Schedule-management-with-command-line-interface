#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include "tasksave.h"
#include "mainstructure.h"
using namespace std;


void add0(int a){
	if(a<10)
		printf("0%d",a);
	else
		printf("%d",a);
}//��ʾʱ��ʱ��0���� 

void display(task exa){
	printf("id:%lld  ",exa.id);
	printf("name:%s  ",exa.name);
	printf("classification:%s  ",exa.classification);
	printf("level:");
	switch (exa.level)
	{
		case 1:
			printf("high level  ");
			break;
		case 2:
			printf("medium level  ");
			break;
		case 3:
			printf("low level  ");
			break;
	}
	printf("time:%d %d %d ",exa.detail.tm_year,exa.detail.tm_mon,exa.detail.tm_mday);
	add0(exa.detail.tm_hour);
	printf(":");
	add0(exa.detail.tm_min);
	printf("  ");
	printf("reminding time:%d %d %d ",exa.remind.tm_year,exa.remind.tm_mon,exa.remind.tm_mday);
	add0(exa.remind.tm_hour);
	printf(":");
	add0(exa.remind.tm_min);
	printf("\n");
}//չʾ���������Ϣ 

bool TestDate(char* input1,char* input2,char* input3){
	int year=intonum(input1);
	int month=intonum(input2);
	int day=intonum(input3);
	if(year>=0&&month>0&&day>0)
	{
 		if (month >= 1 && month <= 12) 
		{
   			if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month ==12)&& day <= 31) 
     				return 1;
				
			else if ((month == 4 || month == 6 || month == 9 || month == 11) && day <= 30) 
      				return 1; 
				
	  		else if (month == 2 && day <= 29)
			    {
      				if ((year % 100 != 0 && year % 4 == 0) || year % 400 == 0) 
						return 1;
      				
					else if (day <= 28)
						return 1;
      				
					else 
						return 0;
      				
  				} 
   			else 
				return 0;
   			
 		} 
 		else 
	   		return 0;
 	
	}
	else if(month>0&&day>0)
	{	
	 	if (month >= 1 && month <= 12) 
		{
   			if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month ==12)&& day <= 31) 
		    	 return 1;
  			
			else if ((month == 4 || month == 6 || month == 9 || month == 11) && day <= 30) 
				return 1; 

	  		else if (month == 2 && day <= 29)
				return 1;
	  	else
	  		return 0;
   		} 
   		else 
			return 0;
	}
	else 
		return 1;
}//��������Ƿ������ʵ������������������һ���жϣ�ֻ������������ݴ��ж��Ƿ���� 

long long int Transform(tm exa){
	long long int x;
	x=(exa.tm_mon)*1000000+exa.tm_mday*10000+exa.tm_hour*100+exa.tm_min;
	x+=static_cast<long long int>(exa.tm_year)*100000000;
	return x;
}
//��һ��ʱ��ṹ���������ʱ����ת��Ϊlong long int����
long long int Transform2(tm* exa){
	long long int x;
	x=(exa->tm_mon+1)*1000000+exa->tm_mday*10000+exa->tm_hour*100+exa->tm_min;
	x+=static_cast<long long int>(exa->tm_year+1900)*100000000;
	return x;
}
//����һ������������ͬ����������ָ�� 
long long int PresentTime(){
	struct tm *t;
	time_t tt;
	time(&tt);
	t=localtime(&tt);//��ȡ����ʱ�� 
	long long int temp;
	temp=Transform2(t);//ת��Ϊlong long int 
	return temp;
}
//��ȡ����ʱ���long long int 
long long int PresentTimeSecond(){
	struct tm *t;
	time_t tt;
	time(&tt);
	t=localtime(&tt);//��ȡ����ʱ�� 
	long long int temp;
	temp=Transform2(t);
	temp=100*temp+t->tm_sec;
	return temp;
}
//��ȡ����ʱ���long long int��������Ҳ���ϣ��������о��Ե�Ψһ�� 
bool ReceiveTime2(char* year,char* month,char* day,char* hour,char* minute){	
	bool test=1;		
	while(test)
	{
		
		bool flag1=1;
		while(flag1)
		{
			printf("year:");
			standardize(year,32);
			if(strcmp(year,"")==0||intonum(year)>=0)
			{
				flag1=0;
			}
			else
			{
				printf("invalid input\n");
			}
	  	}
	    
	    bool flag2=1;
	    while(flag2)
		{
			printf("month:");
			standardize(month,32);
			if(strcmp(month,"")==0||(intonum(month)>0&&intonum(month)<13))
			{
				flag2=0;
			}
			else
			{
				printf("invalid input\n");
			}	
	    }
	    
	    bool flag3=1;
	     while(flag3)
		 {
		 	printf("day:");
			standardize(day,32);
			if(strcmp(day,"")==0||(intonum(day)>0&&intonum(day)<32))
			{
				flag3=0;
			}
			else
			{
			printf("invalid input\n");
			}
	    }
	    
	    if(TestDate(year,month,day))//�������������Ƿ������ʵ���� 
	    	test=0;
	    else
	   		printf("wrong date.please input again\n");

	}
	
	bool flag4=1;
	 while(flag4)
	 {
	 	printf("hour:");
		standardize(hour,32);
		if(strcmp(hour,"")==0||(intonum(hour)>=0&&intonum(hour)<24))
		{
			flag4=0;
		}
		else
		{
			printf("invalid input\n");
		}
	}
	    
	bool flag5=1;
	while(flag5)
	{
		printf("minute:");
		standardize(minute,32);
		if(strcmp(minute,"")==0||(intonum(minute)>=0&&intonum(minute)<60))
		{
			flag5=0;
		}
		else
		{
			printf("invalid input\n");
		}
	} 
	    return 1;
}
//��ȡʱ��������������� 

void ReceiveTime(tm *exa,pthread_mutex_t mutex0){	
    char year[32];
	char month[32];
	char day[32];
	char hour[32];
	char minute[32];
		
	year[0]='\0';
	month[0]='\0';
	day[0]='\0';
	hour[0]='\0';
	minute[0]='\0';
	 	
	bool test=1;
		
	while(test)
	{	
		bool flag1=1;
		while(flag1)
		{
			printf("year:");
			standardize(year,32);
			if(strcmp(year,"")!=0&&intonum(year)>=0)
			{
				int pthread_mutex_lock(pthread_mutex_t *mutex0);
				exa->tm_year=intonum(year);
				int pthread_mutex_unlock(pthread_mutex_t *mutex0);
				flag1=0;
			}
			else
			{
				printf("invalid input\n");
			}
	    }
	    
	    bool flag2=1;
	    while(flag2)
		{
			printf("month:");
			standardize(month,32);
			if(intonum(month)>0&&intonum(month)<13)
			{
				int pthread_mutex_lock(pthread_mutex_t *mutex0);
				exa->tm_mon=intonum(month);
				int pthread_mutex_unlock(pthread_mutex_t *mutex0);
				flag2=0;
			}
			else
			{
				printf("invalid input\n");
			}
	    }
	    
	    bool flag3=1;
	     while(flag3)
		 {
	    	printf("day:");
			standardize(day,32);
			if(intonum(day)>0&&intonum(day)<32)
			{
				int pthread_mutex_lock(pthread_mutex_t *mutex0);
				exa->tm_mday=intonum(day);
				int pthread_mutex_unlock(pthread_mutex_t *mutex0);
				flag3=0;
			}
			else
			{
				printf("invalid input\n");
			}
	    }
	    if(TestDate(year,month,day))//�������������Ƿ������ʵ���� 
	    	test=0;
	    else
	   		printf("wrong date.please input again\n");

	}
		
	bool flag4=1;
	while(flag4)
	{
		printf("hour:");
		standardize(hour,32);
		if(strcmp(hour,"")!=0&&intonum(hour)>=0&&intonum(hour)<24)
		{
			int pthread_mutex_lock(pthread_mutex_t *mutex0);
			exa->tm_hour=intonum(hour);
			int pthread_mutex_unlock(pthread_mutex_t *mutex0);
			flag4=0;
		}
		else
		{
			printf("invalid input\n");
		}
	}
	    
	bool flag5=1;
	while(flag5)
	{
		printf("minute:");
		standardize(minute,32);
		if(strcmp(minute,"")!=0&&intonum(minute)>=0&&intonum(minute)<60)
		{
			int pthread_mutex_lock(pthread_mutex_t *mutex0);
			exa->tm_min=intonum(minute);
			int pthread_mutex_unlock(pthread_mutex_t *mutex0);
			flag5=0;
		}
		else
		{
			printf("invalid input\n");
		}
	} 	    
}
//��ȡʱ�䵫���������� 

bool Compare(const int a,const int b){
	if(a==-1)
		return 1;
	else
	if(a==b)
		return 1;
	else return 0;	
}
//�Ƚ�����ʹ浵�����ݣ��������Ϊ�����ʾ�����бȽϣ�����1
 
void ToString(long long int num,char* str){
	int i=0,j=0;
	char temp[20];
	while(num)
	{
    	temp[i]=num%10+'0';  
    	i++;
    	num=num/10;    	       
	}
    temp[i]='\0';
    
 	i=i-1;
 	while(i>=0)
    {	
		str[j]=temp[i];  
    	j++;
   	 	i--;
	} 
	str[j]='\0';       
} 
//��long long int ת�����ַ�����ʽ ������ 

int SearchTask(task* record,int s,pthread_mutex_t mutex0){
	
	int i=0;
 	char input[30];
 	char id[30];
    printf("input the id of the task\n");
	standardize(input,30);
	int pthread_mutex_lock(pthread_mutex_t *mutex0);//���� 
	for(i=0;i<s;i++)
	{
		ToString(record[i].id,id);//��idת��Ϊ�ַ��� 
		if(strcmp(input,id)==0)//�Ƚ�id�Ƿ���ͬ 
		return i;
	}
	int pthread_mutex_unlock(pthread_mutex_t *mutex0);//���� 
	return -1;
}

void ShowTask(task* record,int s,pthread_mutex_t mutex0){

	bool flag0=1;
	while(flag0)
	{
		printf("according to what to show\n");
		printf("no input:show all\n");
		printf("1:id\n");
		printf("2:name\n");
		printf("3:level\n");
		printf("4:classification\n");
		printf("5:time\n");
		printf("6:reminding time\n");
	
		char call[64];
		call[0]='\0';
		standardize(call,64);
	
		if(strcmp(call,"")==0)
		{
			if(s!=0)
			{
				int pthread_mutex_lock(pthread_mutex_t *mutex0);//���� 
				for(int i=0;i<s;i++)
					display(record[i]);
				int pthread_mutex_unlock(pthread_mutex_t *mutex0);//���� 
			}
			else
				printf("no tasks!\n");
			
			flag0=0;
		}//���������ʾ���� 
	
		else if(intonum(call)==1)
		{
			int pthread_mutex_lock(pthread_mutex_t *mutex0);
        	if(int t=SearchTask(record,s,mutex0 )>=0)//����idȥ�� 
        		display(record[t-1]);
        	
        	else
        		printf("no task meet the requirement\n");
        	int pthread_mutex_unlock(pthread_mutex_t *mutex0);	
			flag0=0;		
		}
		
	   else if(intonum(call)==2)
	   {
	
			printf("enter the name of the task\n");
			char taskname[64];
	 		taskname[0]='\0';
	 		standardize(taskname,64);// ȥ����������ǰ��Ŀո�
			int flag=0;
			
			int pthread_mutex_lock(pthread_mutex_t *mutex0);
		
			for(int i=0;i<s;i++)
			{
				if(strcmp(taskname,record[i].name)==0)
				{
					display(record[i]);
				flag++;
	    		}
	    	}
	    	
	    	if(flag==0)
	    		printf("no task meet the requirement\n");
	    
			int pthread_mutex_unlock(pthread_mutex_t *mutex0);
		
			flag0=0;
		}
		else if(intonum(call)==3)
		{
			printf("enter the level of the task\n");
			char level[64];
			level[0]='\0';
			standardize(level,64);
			
			if(intonum(level)!=1&&intonum(level)!=2&&intonum(level)!=3)//����levelȥ�� 
				printf("invalid input\n");
		
			else
			{
				int flag=0;
				int pthread_mutex_lock(pthread_mutex_t *mutex0);
				for(int i=0;i<s;i++)
				{
				if(record[i].level==intonum(level))
					{
						display(record[i]);
						flag++;
	    			}
	   		}
	    		if(flag==0)
	    			printf("no task meet the requirement\n");
	    			
				int pthread_mutex_unlock(pthread_mutex_t *mutex0);

			}
	
			flag0=0;
		}
		else if(intonum(call)==4)
		{
			printf("enter the classification of the task\n");
			char taskclass[64];
	 		taskclass[0]='\0';
	 		standardize(taskclass,64);
			int flag=0;
			
			int pthread_mutex_lock(pthread_mutex_t *mutex0);
			for(int i=0;i<s;i++)
			{
				if(strcmp(taskclass,record[i].classification)==0)
				{
					display(record[i]);
					flag++;
	    		}
	    	}
	    	if(flag==0)
	    		printf("no task meet the requirement\n");
	    
			int pthread_mutex_unlock(pthread_mutex_t *mutex0);
		
		flag0=0;
		}
		else if(intonum(call)==5)
		{
			printf("enter the time of the task\n");
			char year[10];
			char month[5];
			char day[5];
			char hour[5];
			char minute[5];
		
	 		year[0]='\0';
	 		month[0]='\0';
	 		day[0]='\0';
	 		hour[0]='\0';
	 		minute[0]='\0';
		
       		if(ReceiveTime2(year,month,day,hour,minute))
       		{ 
				int flag=0;
       			int pthread_mutex_lock(pthread_mutex_t *mutex0);
	   			for(int i=0;i<s;i++)
      			{	
				  	if(Compare(intonum(year),(record[i].detail.tm_year))&&
	   				Compare(intonum(month),(record[i].detail.tm_mon))&&
	   				Compare(intonum(day),record[i].detail.tm_mday)&&
	   				Compare(intonum(hour),record[i].detail.tm_hour)&&
	   				Compare(intonum(minute),record[i].detail.tm_min))//����ʱ��ȥ�� 
       				{
					   	display(record[i]);
       					flag++;
		   			}
       	
	  			}
	   			if(flag==0)
	    			printf("no task meet the requirement\n");
	    		int pthread_mutex_unlock(pthread_mutex_t *mutex0);
	   		}
	   		flag0=0;
		}
		else if(intonum(call)==6)
		{
			printf("enter the reminding time of the task\n");
			char year[10];
			char month[5];
			char day[5];
			char hour[5];
			char minute[5];
		
	 		year[0]='\0';
	 		month[0]='\0';
	 		day[0]='\0';
	 		hour[0]='\0';
	 		minute[0]='\0';
		
       		if(ReceiveTime2(year,month,day,hour,minute))//��������ʱ�䣬�����Բ������ʱ�䲻���бȶ� 
       		{ 
			   int flag=0;
       
       			int pthread_mutex_lock(pthread_mutex_t *mutex0);
       
	   			for(int i=0;i<s;i++)
       			{if(Compare(intonum(year),(record[i].remind.tm_year))&&
	   			Compare(intonum(month),(record[i].remind.tm_mon))&&
	   			Compare(intonum(day),record[i].remind.tm_mday)&&
	   			Compare(intonum(hour),record[i].remind.tm_hour)&&
	   			Compare(intonum(minute),record[i].remind.tm_min))//����ʱ��ȥ�� ��δ����ĳ��ʱ�䣨�ꡢ�¡��յȣ������������Ӧ��ʱ��ȽϽ����Ϊ�� 
       			{
				   	display(record[i]);
       				flag++;
       			}
	   			}
	   			if(flag==0)
	    			printf("no task meet the requirement\n");
	    
	    		int pthread_mutex_unlock(pthread_mutex_t *mutex0);
	  		}
	   		flag0=0;
		}
		else 
		{
			printf("invalid input\n");
		}
	}
}


void AddTask(task* record,int &s,pthread_mutex_t mutex0){
	

	printf("input the name of the task\n");
	char taskname[64];
	taskname[0]='\0';
	standardize(taskname,64);
	int pthread_mutex_lock(pthread_mutex_t *mutex0);
	record[s].id=PresentTimeSecond();//idΪ��ǰʱ�䣬��ȷ���� 
	record[s].reminder=1;
	if(strcmp(taskname,"")!=0)
	{
		strcpy(record[s].name,taskname);
	}
	else
	{
		ToString(record[s].id,record[s].name);
		printf("use default name\n");//δ������ʹ��Ĭ�����ƣ���id 
	} 
	int pthread_mutex_unlock(pthread_mutex_t *mutex0);

    printf("input the classification of the task\n");
	char taskclass[64];
	taskclass[0]='\0';
	standardize(taskclass,64);
	
	int pthread_mutex_lock(pthread_mutex_t *mutex0);
	if(strcmp(taskclass,"")!=0)
	{
		strcpy(record[s].classification,taskclass);//δ������ʹ��Ĭ������
	}
	else
	{
		strcpy(record[s].classification,"default");
		printf("use default classification\n");
	} 
	int pthread_mutex_unlock(pthread_mutex_t *mutex0);
	
	bool flag1=1;
	while(flag1)
	{
		printf("input the level of the task\n");
		char level[32];
		level[0]='\0';
		standardize(level,32);
		int pthread_mutex_lock(pthread_mutex_t *mutex0);
		if(strcmp(level,"")==0)
		{
			record[s].level=2;
			printf("use default level\n");//δ������ʹ��Ĭ�����ȼ�
			flag1=0;
		}
		else if(intonum(level)==1||intonum(level)==2||intonum(level)==3)
		{
			record[s].level=intonum(level);
			flag1=0;
		} 
		else
		{
			printf("invalid input\n");
		}
		int pthread_mutex_unlock(pthread_mutex_t *mutex0);
    }
    
    long long int presenttime=PresentTime();
    
    printf("input the time\n");
  
    ReceiveTime(&(record[s].detail),mutex0 );//��ȡ����ʱ�� 
   long long int num1= Transform(record[s].detail);
   
    if(num1<=presenttime)
   		printf("warning!the time of the task is earlier than the present time.you can adjust it later.\n");
   		
    printf("input the reminding time\n");//����ʱ�����������򾯸�
  
    
    ReceiveTime(&(record[s].remind),mutex0);//��ȡ����ʱ�� 
    long long int num2= Transform(record[s].remind);

    if(num2<=presenttime)
    	printf("warning!the reminding time of the task is earlier than the present time.you can adjust it later.\n");//����ʱ�����������򾯸�
    if(num2>=num1)
    	printf("warning!the time of the task is earlier than the reminding time of the task.you can adjust it later.\n");//����ʱ����������ʱ���򾯸�
    s++;//����������1 
}

//adjust��show��add������ 
void AdjustTask(task* record,int s,pthread_mutex_t mutex0){
	
	
	int t=SearchTask(record,s,mutex0);
    if(t>=0)
	{
    	bool flag=1;
    
    	while(flag)
		{
    		printf("\n");
    		printf("adjust what\n");
			printf("1:name\n");
			printf("2:level\n");
			printf("3:classification\n");
			printf("4:time\n");
			printf("5:reminding time\n");
			printf("0:quit\n");
			char call[64];
			call[0]='\0';
			standardize(call,64);

    		if(intonum(call)==1)
			{
				printf("enter the name of the task\n");
				char taskname[64];
	  		  	taskname[0]='\0';
	  		  	standardize(taskname,64);
				int pthread_mutex_lock(pthread_mutex_t *mutex0);
		
				if(strcmp(taskname,"")!=0)
					strcpy(record[t].name,taskname);
				else
					printf("you input nothing"); 
				int pthread_mutex_unlock(pthread_mutex_t *mutex0);
			}
			else if(intonum(call)==2)
			{
				bool flag1=1;
				while(flag1)
				{
					printf("enter the level of the task\n");
					char level[64];
					level[0]='\0';
					standardize(level,64);
					if(intonum(level)!=1&&intonum(level)!=2&&intonum(level)!=3)
					printf("invalid input");
					else
					{	
						int pthread_mutex_lock(pthread_mutex_t *mutex0);
						record[t].level=intonum(level);
						int pthread_mutex_unlock(pthread_mutex_t *mutex0);
						flag1=0;
					}
				}
	
			}
	
			else if(intonum(call)==3)
			{
				printf("enter the classification of the task\n");
				char taskclass[64];
	 			taskclass[0]='\0';
	 			standardize(taskclass,64);
				int pthread_mutex_lock(pthread_mutex_t *mutex0);
				if(strcmp(taskclass,"")!=0)
					strcpy(record[t].classification,taskclass);
				else
					printf("you input nothing"); 
				int pthread_mutex_unlock(pthread_mutex_t *mutex0);
			}
			else if(intonum(call)==4)
			{
				printf("enter the time of the task\n");
				char year[10];
				char month[5];
				char day[5];
				char hour[5];
				char minute[5];
		
	 			year[0]='\0';
	 			month[0]='\0';
	 			day[0]='\0';
	 			hour[0]='\0';
	 			minute[0]='\0';
		
      			if(ReceiveTime2(year,month,day,hour,minute))
      			{
	    			int pthread_mutex_lock(pthread_mutex_t *mutex0);
	    			if(strcmp(year,"")!=0)
        				record[t].detail.tm_year=intonum(year);//�ַ���Ϊ������Ҫ���и���
        			if(strcmp(month,"")!=0)
       	 				record[t].detail.tm_mon=intonum(month);
       				if(strcmp(day,"")!=0)
        				record[t].detail.tm_mday=intonum(day);
        			if(strcmp(hour,"")!=0)
        				record[t].detail.tm_hour=intonum(hour);
        			if(strcmp(minute,"")!=0)
        				record[t].detail.tm_min=intonum(minute);
        			int pthread_mutex_unlock(pthread_mutex_t *mutex0);
	   			}//ʱ�����δ��������Ҫ���и��� 
	   
	    		long long int presenttime=PresentTime();
	    	
	    		int pthread_mutex_lock(pthread_mutex_t *mutex0);
				if(Transform(record[t].detail)<=presenttime)
   				printf("warning!the time of the task is earlier than the present time.you can adjust it later.\n"); //����ʱ�����������򾯸�
   				int pthread_mutex_unlock(pthread_mutex_t *mutex0);
			}
			else if(intonum(call)==5)
			{
				printf("enter the reminding time of the task\n");
				char year[10];
				char month[5];
				char day[5];
				char hour[5];
				char minute[5];
		
	 			year[0]='\0';
	 			month[0]='\0';
	 			day[0]='\0';
	 			hour[0]='\0';
	 			minute[0]='\0';
		
      			if(ReceiveTime2(year,month,day,hour,minute))
       			{
       				int pthread_mutex_lock(pthread_mutex_t *mutex0);
	   				if(strcmp(year,"")!=0)//�ַ���Ϊ������Ҫ���и���
        				record[t].remind.tm_year=intonum(year);
        			if(strcmp(month,"")!=0)
        				record[t].remind.tm_mon=intonum(month);
        			if(strcmp(day,"")!=0)
        				record[t].remind.tm_mday=intonum(day);
        			if(strcmp(hour,"")!=0)
        				record[t].remind.tm_hour=intonum(hour);
        			if(strcmp(minute,"")!=0)
        				record[t].remind.tm_min=intonum(minute);
        
        			int pthread_mutex_unlock(pthread_mutex_t *mutex0);
	   			}//ʱ�����δ��������Ҫ���и��� 

	    		long long int presenttime=PresentTime();
	    		int pthread_mutex_lock(pthread_mutex_t *mutex0);
				if(Transform(record[t].remind)<=presenttime)
  	    		printf("warning!the reminding time of the task is earlier than the present time.you can adjust it later.\n");//����ʱ�����������򾯸�
   				if(Transform(record[t].detail)<=Transform(record[s].remind))
   				printf("warning!the time of the task is earlier than the reminding time of the task.you can adjust it later.\n");//����ʱ����������ʱ���򾯸�
   				int pthread_mutex_unlock(pthread_mutex_t *mutex0);
			}
			else if(intonum(call)==0&&strcmp(call,"")!=0)
			{
				flag=0;
			}
			else
				printf("invalid input\n");
		}
		record[t].reminder=1;
	}
   else 
   {
   		printf("no such a task\n");
   }
}

void DeleteTask(task* record,int& s,pthread_mutex_t mutex0 ){
	
	
	int t=SearchTask(record,s,mutex0);
	if(t>=0)
	{
		int pthread_mutex_lock(pthread_mutex_t *mutex0);
		if(t<=s-2)//����������һ��������ֱ���ú��������ȥ���ǣ�����������һ�����񣬾�ֱ��������һ�����ý����������� 
		{
			for(int i=t;i<s-1;i++)	
			record[i]=record[i+1];
		}
		s--;
		printf("delete successfully\n");
		int pthread_mutex_unlock(pthread_mutex_t *mutex0);
	}
   else 
   {
   		printf("no such a task\n");
   }	
}
//ɾ������ 

void SortTask(task* record,int s ){
	

	
	for (int i=1 ; i<s; i++) 
	{
        for (int j=0;j<s-i;j++) 
		{
            if(Transform(record[j].remind)>Transform(record[j+1].remind))
			{
            	task temp;
            	temp=record[j];
                record[j]=record[j+1];
                record[j+1]=temp;
            }
        }
    }
}
//�������������ʱ�������������ʱ���������ǰ�� 

void SaveTask(char* x,task* record,int s){
	
	
	FILE * pFile = fopen (x, "w");
	for(int i=0;i<s;i++)
	{
		fprintf(pFile,"%s\n",record[i].name);
    	fprintf(pFile,"%s\n",record[i].classification);	
    	char str[20];
    	ToString(record[i].id,str);
    	fprintf(pFile,"%s\n",str);	
    	fprintf(pFile,"%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n",record[i].level,
		record[i].detail.tm_year,record[i].detail.tm_mon,record[i].detail.tm_mday,record[i].detail.tm_hour,record[i].detail.tm_min,
		record[i].remind.tm_year,record[i].remind.tm_mon,record[i].remind.tm_mday,record[i].remind.tm_hour,record[i].remind.tm_min);	
	}
	fclose (pFile);
}
//������д���ļ��� ��һ������ֳ�4��ȥ���� 
//ǰ������Ϊ���ַ��������ܺ��� �������ݣ��ʷֿ����� 
//���һ���ã������ݷֿ� 

int Readint(char* str){
	int n=0;
	for(int i=0;str[i]!=';'&&str[i]!='\0';i++)
	n=10*n+(str[i]-'0');
	return n;
}
//���������ַ����ĳ�int 
int ReadTask(const char*x,task* record){
	int i=0;
	FILE * pFile = fopen (x, "r");//��ֻ����ʽ�� ��������д�� 
	char buff[64];
	if(pFile==NULL) 
	{
		printf("cannot find %s\n",x);
		exit(0);//�ļ��򲻿����߲����ھ��˳� 
	}
	while (fgets(buff,64,pFile)&&strcmp(buff,"\n")!=0)
	{
		buff[length(buff)-2]='\0';
		i++;
		if(i%4==1)
			strcpy(record[(i-1)/4].name,buff);
		if(i%4==2)
			strcpy(record[(i-2)/4].classification,buff);
		if(i%4==3)
		{
    		long long int num=0;
    		for(int j=0;buff[j]!='\0';j++)
    		num=10*num+static_cast<long long int>(buff[j]-'0');
    		record[(i-3)/4].id=num;
		}
		if(i%4==0)
		{
			int a[10];
			int m=0;
			for(int j=0;j<64&&m<10;j++)
			{ 	
				if(buff[j]==';')
	  			{
	  				a[m]=j;
	  				m++;
	  			}
			}
			record[(i-4)/4].level=Readint(buff);
			record[(i-4)/4].detail.tm_year=Readint(buff+a[0]+1);
			record[(i-4)/4].detail.tm_mon=Readint(buff+a[1]+1);
			record[(i-4)/4].detail.tm_mday=Readint(buff+a[2]+1);
			record[(i-4)/4].detail.tm_hour=Readint(buff+a[3]+1);
			record[(i-4)/4].detail.tm_min=Readint(buff+a[4]+1);
			record[(i-4)/4].remind.tm_year=Readint(buff+a[5]+1);
			record[(i-4)/4].remind.tm_mon=Readint(buff+a[6]+1);
			record[(i-4)/4].remind.tm_mday=Readint(buff+a[7]+1);
			record[(i-4)/4].remind.tm_hour=Readint(buff+a[8]+1);
			record[(i-4)/4].remind.tm_min=Readint(buff+a[9]+1);//����ȡ�����ַ����ĳ�int 
		}
	}
	fclose (pFile);
	return i/4;
}
//��ȡ���� 
void Remind(task* record,int s){
	long long int temp=PresentTime();
	bool flag=1;
	for(int i=0;i<s&&flag==1;i++)
	{
		if(Transform(record[i].remind)<=temp&& (Transform(record[i].detail)>=temp-10000||Transform(record[i].remind)>=temp-10000)&&record[i].reminder==1)// �ﵽ����ʱ�䣬δ��������ʱ�������ʱ��һ����δ���ѹ���ȥ���� 
		{	printf("\n");
			printf("remind:");
			display(record[i]);
			record[i].reminder=0;//reminder��ʾ�Ƿ���Ҫ�����ѣ��Ѿ����ѹ��Ͳ���Ҫ�ٽ������ѣ����� ���������͸Ķ��˵�����reminder��Ϊ1 
		}
		else
			flag=0;
	}
}//�ȶ�ʱ�䲢���� 
