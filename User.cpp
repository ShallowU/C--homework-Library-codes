#include "User.h"
#include "Student.h"
#include "Teacher.h"
#include<iostream>
#include<fstream>
#include"ManagementBooks.h"
using namespace std;

User::User()
{
	
}

void User::setId(string id)
{
    m_id = id;
}

void User::setName(string name)
{
    m_name = name;
}

void User::setGender(string gender)
{
    m_gender = gender;
}

void User::setDepartment(string department)
{
    m_department = department;
}

void User::setPassword(string pas)
{
	password=pas;
}

User::~User()
{
}

void User::returnBook(ManagementBooks& mb)
{
    int all = mb.checkBorrowedBook(m_id);
    if (all == 0)
    {
        cout << "您暂未借书,无需归还" << endl;
    }
    else
    {
        cout << "请输入您要归还的书名:" ;
        string bookName;
        cin >> bookName;
        if (mb.checkTrueBorrow(m_id, bookName))//检查是否借了这本书 
        {
        	if(isdue())
        	{
	            mb.Return(m_id, bookName);
	            cout << "在规定期限还书成功呀!信誉分+2！" << endl;
	            ifstream file("creditpoint.txt");
	            string account[60];
	            int point[60];
	            int i=0,j=0;
	            while(!file.eof())
	            {
	            	file>>account[i]>>point[i];
	            	i++;
				}
				file.close();
				for(j=0;j<i;j++)
				{
					if(account[j]==m_id)
					{
						point[j]=point[j]+2;
						break;
					}
				}
				ofstream file1("creditpoint.txt");
				for(j=0;j<i;j++)
				{
					file1<<endl<<account[j]<<" "<<point[j];
				}
				file1.close();
        	}
        	else
        	{
        		cout<<"还书迟到！未再期限前完成还书,信誉分-10！！！"<<endl;
        		mb.Return(m_id, bookName);
        		cout << "本次还书成功，下次请在规定时间还书！" << endl;
        		ifstream file("creditpoint.txt");
	            string account[60];
	            int point[60];
	            int i=0,j=0;
	            while(!file.eof())
	            {
	            	file>>account[i]>>point[i];
	            	i++;
				}
				file.close();
				for(j=0;j<i;j++)
				{
					if(account[j]==m_id)
					{
						point[j]=point[j]-10;
						break;
					}
				}
				ofstream file1("creditpoint.txt");
				for(j=0;j<i;j++)
				{
					file1<<endl<<account[j]<<" "<<point[j];
				}
				file1.close();
			}
        }
        else
        {
            cout << "您并未借阅此书" << endl;
        }
    }
}
bool User::isdue()
{
	
	ifstream readFile("borrowedtimeStu.txt");
	ifstream readFile1("borrowedtimeTea.txt");
	string name;
	string strtimeToReturn;
	char ch;
	cout<<"请再次确认你是老师（t)还是学生（s）t/s:";
	cin>>ch;
	if(ch=='S'||ch=='s')
	{
		while(!readFile.eof())
		{
			readFile>>name;
			if(name==m_id)
			{
				readFile>>strtimeToReturn;
				break;
			}
		}
	}
	else
	{
		while(!readFile1.eof())
		{
			readFile1>>name;
			if(name==m_id)
			{
				readFile1>>strtimeToReturn;
				break;
			}
		}
	}
	time_t now = time(NULL);
	tm *local_time = localtime(&now);
	char buffer[20];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local_time);
	readFile.close();
	readFile1.close();
	return buffer<strtimeToReturn;
}
void User::modifyinfo()
{
	ifstream file;
	ofstream filew;
	string oldid;
	string space;
	User *p[50];
	int i=0;
	int flag=0;
	char ch;
	cout<<"请问你是老师还是学生（t/s）：";
	cin>>ch;
	cout<<"请输入你目前的学工号：" ;
	cin>>oldid;
	if(ch=='S'||ch=='s')
	{
		file.open("student.txt");
		cout<<"打开成功！"<<endl; 
		for(int m=0;m<50;m++)
		{
			p[m]=new Student;
		}
	}
	else
	{
		 file.open("teacher.txt");
		for(int m=0;m<50;m++)
		{
			p[m]=new Teacher;
		}
	}
	if(file.fail())
		cout<<"修改信息时读取数据打开文件失败"<<endl;
	while(!file.eof())
	{
		file>>p[i];
		if(p[i]->getId() == oldid)
			flag=i;
		i++;
	}
	file.close();
	cout<<"下面是你的原本信息："<<endl;
	p[flag]->showInfo();
	string newid,newname,newgender,newdepartment;
	int t=0;
	cout<<"请选择你要修改的信息："<<endl;
	cout<<"1.学工号"<<endl;
	cout<<"2.姓名"<<endl;
	cout<<"3.性别"<<endl;
	cout<<"4.学院" <<endl;
	cout<<"5.密码" <<endl;
	cout<<"您的选择：";
	cin>>t;
	if(t==1)
	{
		cout<<"新的学号为：";
		cin>>newid;
		p[flag]->setId(newid);
	}
	else if(t==2)
	{
		cout<<"新的姓名为：";
		cin>>newname;
		p[flag]->setName(newname);
	}
	else if(t==3)
	{
		cout<<"新的性别：";
		cin>>newgender;
		p[flag]->setGender(newgender);
	}
	else if(t==4)
	{
		cout<<"新的学院（部门）：";
		cin>>newdepartment;
		p[flag]->setDepartment(newdepartment);
	}
	else
	{
		
	}
	file.close();
	if(ch=='S'||ch=='s')
	{
		 filew.open("student.txt");
	}
	else
	{
		 filew.open("teacher.txt");
	}
	if(filew.fail())
		cout<<"修改信息时写数据打开文件失败"<<endl;
	for(int j=0;j<i;j++)
	{
		filew<<p[j];
	}
	filew.close();
	if(t==5)
	{
		ifstream filea;
		ofstream fileb;
		string oldaccount,newkey;
		string account[50];
		string key[50];
		int n=0,k=0;
		char ch1;
		if(ch=='S'||ch=='s')
		{
			filea.open("studentLogin.txt");
		}
		else
		{
			filea.open("teacherLogin.txt");
		}
		cout<<"请输入你的学工号：";
		cin>>oldaccount;
		while(!filea.eof())
		{
			filea>>account[n]>>key[n];
			if(account[n]==oldaccount)
			{
				k=n;
			}
			n++;
		}
		filea.close();
		cout<<"你的原密码为："<<key[k]<<endl;
		cout<<"确认是否修改（y/n）：";
		cin>>ch1;
		if(ch1=='y'||ch1=='Y')
		{
			cout<<"设置新密码为：";
			cin>>newkey;
			key[k]=newkey;
		}
		else
			cout<<"好的我们不修改密码呢！"<<endl;
		if(ch=='S'||ch=='s')
		{
			fileb.open("studentLogin.txt");
		}
		else
		{
			fileb.open("teacherLogin.txt");
		}
		for(int a=0;a<n;a++)
		{
			fileb<<endl<<account[a]<<" "<<key[a];
		}
		fileb.close();
	}
	cout<<"修改信息完毕！"<<endl; 
	
}
void User::checkcredit()
{
    ifstream file("creditpoint.txt");
	string account[60];
    int point[60];
	int i=0,j=0;
	int flag=0;
	while(!file.eof())
	{
	    file>>account[i]>>point[i];
	    i++;
	}
	file.close();
	for(j=0;j<i;j++)
	{
		if(account[j]==m_id)
		{
			flag=j;
			break;
		}
	}
	cout<<"当前你的信誉分为："<<point[flag]<<"分"<<endl;
}

string User::getId()
{
    return m_id;
}

string User::getName()
{
    return m_name;
}

string User::getGender()
{
    return m_gender;
}


string User::getDepartment()
{
    return m_department;
}

string User::getPassword()
{
	return password;
}
string User::get_borrowTime()
{
	string time=asctime(&borrowTime);
	return time;
}

string User::get_returnTime()
{
	string time=asctime(&returnTime);
	return time;
}
tm* User::get_returnTime_tm()
{
	return &returnTime; 
}
std::ostream& operator<<(std::ostream& os, const User* user)//重载<<将用户信息格式化写入文件 
{
    os<< endl << user->m_id << " " << user->m_name << " " << user->m_gender << " " << user->m_department;
    return os;
}

std::istream& operator>>(std::istream& is, User* user)//重载>>将用户信息读出来 
{

   is >> user->m_id >> user->m_name >> user->m_gender >> user->m_department;
   return is;
}


