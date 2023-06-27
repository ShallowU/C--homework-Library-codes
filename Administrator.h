#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
#include<iostream>
#include<string>
#include "ManagementBooks.h"
#include"Book.h"
using namespace std;
class Administrator
{
private:
	string m_id;
	string m_name;
	string m_gender;
	string m_department;
public:
	void addBook(ManagementBooks& mb);
	void deleteBook(ManagementBooks& mb);
	void modifyBook(ManagementBooks& mb);
	void setId(string id);
	void setName(string name);
	void setGender(string Gender);
	void setDepartment(string department);
	string getId();
	string getName();
	string getGender();
	string getDepartment();
	void showInfo();
	void checkblacklist();
	friend std::istream& operator >> (std::istream& is, Administrator& admin);
};
#endif
