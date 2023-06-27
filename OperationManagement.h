#ifndef OPERATIONMANAGEMENT_H
#define OPERATIONMANAGEMENT_H
#include<iostream>
#include"Book.h"
#include"Student.h"
#include"ManagementBooks.h"
#include"Teacher.h"
#include<fstream>
#include"Administrator.h"
using namespace std;
class OperationManagement//用于管理员和用户密码登录 
{
public:
	void login(User* user, char choice);
	void Register(User* user, char choice);
	void userOperation(User* user, ManagementBooks mb);
	void adminLogin(Administrator& admin);
	void init(ManagementBooks& mb);
	void adminOperation(Administrator admin, ManagementBooks mb);
};
#endif 
