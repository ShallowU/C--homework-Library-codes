#ifndef STUDENT_H
#define STUDENT_H
#include<string.h>
#include<iostream>
#include"User.h"
#include"ManagementBooks.h"
using namespace std;
class Student :  public User//¹«ÓÐ¼Ì³Ð 
{
private:
	string m_class;
public:
	Student();
	void showInfo();
	void borrowBookFromLibrary(ManagementBooks& mb);
	void setClass(string Class);
	string getClass();
};
#endif
