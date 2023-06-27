#include <iostream> //下列为字符有效性检验类的函数定义 
using namespace std;
#include<ctype.h>
#include <string.h>
#include "chrange.h"

CharRange::CharRange(char low,char high, string str)
{
	lower=toupper(low);
	upper=toupper(high);
	errMsg=str;
}
char CharRange::getChar()
{
	cin>>(input);
	//cin.ignore();
	input=toupper(input);
	
	while(input<lower||input>upper)
	{
		cout<<errMsg;
		cin>>(input);
		//cin.ignore();
		input=toupper(input);
	}
	return input;
}
