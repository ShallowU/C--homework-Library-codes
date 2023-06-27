#include<iostream>
#include"Book.h"
#include"Student.h"
#include"ManagementBooks.h"
#include"Teacher.h"
#include<fstream>
#include"Administrator.h"
#include"OperationManagement.h"
#include "chrange.h"
using namespace std;
int main()
{
	ManagementBooks manageb;
	User* user = nullptr;
	OperationManagement operation;
	operation.init(manageb);
	
	cout<<"***********************************************************************************"<<endl;
	cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 欢迎来到图书馆 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" <<endl;
	cout<<"***********************************************************************************"<<endl;
	cout << "注意事项如下:" << endl;
	cout<<"1.学生最多共可借六本书,老师最多共可借八本书"<<endl;
	cout<<"2.借书后一定要及时还书 3次不按时还书会列入图书馆黑名单！" <<endl;
	cout<<"3.每人注册账号后初始信誉分为100"<<endl; 
	cout<<"4.按时还书信誉分+2，逾期还书信誉分-10！信誉分低于75将会列入图书馆黑名单，不能再借书" <<endl;
	cout<<"************************************************************************************"<<endl;
	
	cout << "现在请选择您的登录方式:"<<endl;
	cout<<"a)老师"<<endl;
	cout<<"b)学生"<<endl;
	cout<<"c)管理员" <<endl;
	cout<<"您的选择：";
	string msg="请输入a~c之间的字母！重新输入：";
	char choice;
	CharRange input('A','C',msg);
	choice=input.getChar();
	switch(choice)
	{
		case 'A':
			user = new Teacher;
			break;
		case 'B':
			user = new Student;
			break;
		case 'C':
			Administrator admin;
			operation.adminLogin(admin);
			admin.showInfo();
			operation.adminOperation(admin, manageb);
			return 0;		
	}

	cout<<"您是否已经注册过账号？(y/n):" ;
	char ch;
	cin>>ch;
	if (ch =='Y'||ch=='y')
	{
		operation.login(user,choice);
		user->showInfo();
	}
	else
	{
		cout << "现在可以根据提示,用你的学工号注册一个账号!" << endl;
		operation.Register(user,choice);
	}
	operation.userOperation(user, manageb);
	delete user;
	return 0;
}
