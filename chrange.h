#ifndef CHARRANGE_H
#define CHARRANGE_H
#include <string>
class CharRange //�����ַ���Ч�Լ������ 
{
	private:
		string errMsg;
		char input;
		char lower;
		char upper;
	public:
		CharRange(char,char,string);
		char getChar();
};
#endif 
