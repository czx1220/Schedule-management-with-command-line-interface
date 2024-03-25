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
}//显示时间时加0补齐 

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
}//展示任务具体信息 

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
}//检测日期是否符合现实，输入年月日则三者一起判断，只输入了月日则据此判断是否合理 

long long int Transform(tm exa){
	long long int x;
	x=(exa.tm_mon)*1000000+exa.tm_mday*10000+exa.tm_hour*100+exa.tm_min;
	x+=static_cast<long long int>(exa.tm_year)*100000000;
	return x;
}
//将一个时间结构体的年月日时分钟转化为long long int返回
long long int Transform2(tm* exa){
	long long int x;
	x=(exa->tm_mon+1)*1000000+exa->tm_mday*10000+exa->tm_hour*100+exa->tm_min;
	x+=static_cast<long long int>(exa->tm_year+1900)*100000000;
	return x;
}
//与上一个函数功能相同，但参数是指针 
long long int PresentTime(){
	struct tm *t;
	time_t tt;
	time(&tt);
	t=localtime(&tt);//获取现在时间 
	long long int temp;
	temp=Transform2(t);//转化为long long int 
	return temp;
}
//获取现在时间的long long int 
long long int PresentTimeSecond(){
	struct tm *t;
	time_t tt;
	time(&tt);
	t=localtime(&tt);//获取现在时间 
	long long int temp;
	temp=Transform2(t);
	temp=100*temp+t->tm_sec;
	return temp;
}
//获取现在时间的long long int，但把秒也加上，这样具有绝对的唯一性 
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
	    
	    if(TestDate(year,month,day))//检测输入的日期是否符合现实条件 
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
//获取时间且允许不输入参数 

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
	    if(TestDate(year,month,day))//检测输入的日期是否符合现实条件 
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
//获取时间但不允许不输入 

bool Compare(const int a,const int b){
	if(a==-1)
		return 1;
	else
	if(a==b)
		return 1;
	else return 0;	
}
//比较输入和存档的内容，如果输入为空则表示不进行比较，返回1
 
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
//把long long int 转换到字符串形式 并储存 

int SearchTask(task* record,int s,pthread_mutex_t mutex0){
	
	int i=0;
 	char input[30];
 	char id[30];
    printf("input the id of the task\n");
	standardize(input,30);
	int pthread_mutex_lock(pthread_mutex_t *mutex0);//加锁 
	for(i=0;i<s;i++)
	{
		ToString(record[i].id,id);//把id转化为字符串 
		if(strcmp(input,id)==0)//比较id是否相同 
		return i;
	}
	int pthread_mutex_unlock(pthread_mutex_t *mutex0);//解锁 
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
				int pthread_mutex_lock(pthread_mutex_t *mutex0);//加锁 
				for(int i=0;i<s;i++)
					display(record[i]);
				int pthread_mutex_unlock(pthread_mutex_t *mutex0);//解锁 
			}
			else
				printf("no tasks!\n");
			
			flag0=0;
		}//不输入就显示所有 
	
		else if(intonum(call)==1)
		{
			int pthread_mutex_lock(pthread_mutex_t *mutex0);
        	if(int t=SearchTask(record,s,mutex0 )>=0)//根据id去找 
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
	 		standardize(taskname,64);// 去除输入内容前后的空格
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
			
			if(intonum(level)!=1&&intonum(level)!=2&&intonum(level)!=3)//根据level去找 
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
	   				Compare(intonum(minute),record[i].detail.tm_min))//根据时间去找 
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
		
       		if(ReceiveTime2(year,month,day,hour,minute))//允许不输入时间，这样对不输入的时间不进行比对 
       		{ 
			   int flag=0;
       
       			int pthread_mutex_lock(pthread_mutex_t *mutex0);
       
	   			for(int i=0;i<s;i++)
       			{if(Compare(intonum(year),(record[i].remind.tm_year))&&
	   			Compare(intonum(month),(record[i].remind.tm_mon))&&
	   			Compare(intonum(day),record[i].remind.tm_mday)&&
	   			Compare(intonum(hour),record[i].remind.tm_hour)&&
	   			Compare(intonum(minute),record[i].remind.tm_min))//根据时间去找 ，未输入某个时间（年、月、日等）则与所有相对应的时间比较结果都为真 
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
	record[s].id=PresentTimeSecond();//id为当前时间，精确到秒 
	record[s].reminder=1;
	if(strcmp(taskname,"")!=0)
	{
		strcpy(record[s].name,taskname);
	}
	else
	{
		ToString(record[s].id,record[s].name);
		printf("use default name\n");//未输入则使用默认名称，即id 
	} 
	int pthread_mutex_unlock(pthread_mutex_t *mutex0);

    printf("input the classification of the task\n");
	char taskclass[64];
	taskclass[0]='\0';
	standardize(taskclass,64);
	
	int pthread_mutex_lock(pthread_mutex_t *mutex0);
	if(strcmp(taskclass,"")!=0)
	{
		strcpy(record[s].classification,taskclass);//未输入则使用默认属性
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
			printf("use default level\n");//未输入则使用默认优先级
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
  
    ReceiveTime(&(record[s].detail),mutex0 );//读取任务时间 
   long long int num1= Transform(record[s].detail);
   
    if(num1<=presenttime)
   		printf("warning!the time of the task is earlier than the present time.you can adjust it later.\n");
   		
    printf("input the reminding time\n");//输入时间早于现在则警告
  
    
    ReceiveTime(&(record[s].remind),mutex0);//读取提醒时间 
    long long int num2= Transform(record[s].remind);

    if(num2<=presenttime)
    	printf("warning!the reminding time of the task is earlier than the present time.you can adjust it later.\n");//输入时间早于现在则警告
    if(num2>=num1)
    	printf("warning!the time of the task is earlier than the reminding time of the task.you can adjust it later.\n");//任务时间早于提醒时间则警告
    s++;//任务总数＋1 
}

//adjust与show、add等相似 
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
        				record[t].detail.tm_year=intonum(year);//字符串为空则不需要进行更改
        			if(strcmp(month,"")!=0)
       	 				record[t].detail.tm_mon=intonum(month);
       				if(strcmp(day,"")!=0)
        				record[t].detail.tm_mday=intonum(day);
        			if(strcmp(hour,"")!=0)
        				record[t].detail.tm_hour=intonum(hour);
        			if(strcmp(minute,"")!=0)
        				record[t].detail.tm_min=intonum(minute);
        			int pthread_mutex_unlock(pthread_mutex_t *mutex0);
	   			}//时间如果未输入则不需要进行更改 
	   
	    		long long int presenttime=PresentTime();
	    	
	    		int pthread_mutex_lock(pthread_mutex_t *mutex0);
				if(Transform(record[t].detail)<=presenttime)
   				printf("warning!the time of the task is earlier than the present time.you can adjust it later.\n"); //输入时间早于现在则警告
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
	   				if(strcmp(year,"")!=0)//字符串为空则不需要进行更改
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
	   			}//时间如果未输入则不需要进行更改 

	    		long long int presenttime=PresentTime();
	    		int pthread_mutex_lock(pthread_mutex_t *mutex0);
				if(Transform(record[t].remind)<=presenttime)
  	    		printf("warning!the reminding time of the task is earlier than the present time.you can adjust it later.\n");//输入时间早于现在则警告
   				if(Transform(record[t].detail)<=Transform(record[s].remind))
   				printf("warning!the time of the task is earlier than the reminding time of the task.you can adjust it later.\n");//任务时间早于提醒时间则警告
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
		if(t<=s-2)//如果不是最后一个任务，则直接用后面的任务去覆盖，如果不是最后一个任务，就直接总数减一，不用进行其他操作 
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
//删除任务 

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
//对任务根据提醒时间进行排序，提醒时间早的排在前面 

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
//把任务写进文件中 ，一个任务分成4行去保存 
//前几行因为是字符串，可能含有 各种内容，故分开保存 
//最后一行用；把内容分开 

int Readint(char* str){
	int n=0;
	for(int i=0;str[i]!=';'&&str[i]!='\0';i++)
	n=10*n+(str[i]-'0');
	return n;
}
//将读到的字符串改成int 
int ReadTask(const char*x,task* record){
	int i=0;
	FILE * pFile = fopen (x, "r");//以只读方式打开 ，不允许写入 
	char buff[64];
	if(pFile==NULL) 
	{
		printf("cannot find %s\n",x);
		exit(0);//文件打不开或者不存在就退出 
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
			record[(i-4)/4].remind.tm_min=Readint(buff+a[9]+1);//将读取到的字符串改成int 
		}
	}
	fclose (pFile);
	return i/4;
}
//读取任务 
void Remind(task* record,int s){
	long long int temp=PresentTime();
	bool flag=1;
	for(int i=0;i<s&&flag==1;i++)
	{
		if(Transform(record[i].remind)<=temp&& (Transform(record[i].detail)>=temp-10000||Transform(record[i].remind)>=temp-10000)&&record[i].reminder==1)// 达到提醒时间，未超过任务时间或提醒时间一天且未提醒过则去提醒 
		{	printf("\n");
			printf("remind:");
			display(record[i]);
			record[i].reminder=0;//reminder表示是否还需要在提醒，已经提醒过就不需要再进行提醒，对于 新添的任务和改动了的任务，reminder都为1 
		}
		else
			flag=0;
	}
}//比对时间并提醒 
