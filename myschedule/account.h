#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mainstructure.h"
using namespace std;

struct namepwd{
	char name[60];//ÕË»§Ãû³Æ 
	int hash;//¹þÏ£Öµ 
};

unsigned int SDBMHash(char *str);

bool Testfile();

int length(char* str);

void ReadInput1(char *name);

void ReadInput2(char *password);

void CreateAccount(char *name,char *password);

int ReadAccount(namepwd * record);

bool AvoidRepitition(char* name,namepwd * record,int t);

int TestAccount1(char* name,namepwd * record,int t);

bool TestAccount2(char* name,char* password,namepwd * record,int i);

void Part1Account(char *input1,char *input2);
#endif
