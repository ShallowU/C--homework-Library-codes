#ifndef USER_H
#define USER_H
#include<iostream>
#include"ManagementBooks.h"
#include <ctime>
using namespace std;
class User
{
protected:
	string m_id;
	string m_name;
	string m_gender;
	string m_department;
	string password;
	tm borrowTime;
	tm returnTime;
public:
	User();
    virtual	void borrowBookFromLibrary(ManagementBooks& mb)= 0;//纯虚函数用于继承的子类 
	void setId(string id);
	void setName(string name);
	void setGender(string Gender);
	void setDepartment(string department);
	void setPassword(string pas);
    virtual void showInfo()=0;//纯虚函数用于继承的子类 
	virtual ~User();//纯虚函数用于继承的子类 
	void returnBook(ManagementBooks& mb);
	string getId();
	string getName();
	string getGender();
	string getDepartment();
	string getPassword();
	string get_borrowTime();
	string get_returnTime();
	tm* get_returnTime_tm();
	bool isdue();
	void modifyinfo();
	void checkcredit();
	friend std::ostream& operator << (std::ostream& os, const User* user);
	friend std::istream& operator >> (std::istream& is,  User* user);
};
#endif
