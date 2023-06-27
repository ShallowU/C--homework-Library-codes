#include "OperationManagement.h"
#include <stdlib.h>
#include "chrange.h"
#include <fstream>

void OperationManagement::login(User* user,char choice)
{
	ifstream readFile;
	ifstream readFile1;
	if (choice == 'A')
	{
		readFile.open("teacherLogin.txt");//改 
		readFile1.open("teacher.txt");
	}
	else
	{
		readFile1.open("student.txt");
		readFile.open("studentLogin.txt");
	}
	if (!readFile.is_open())
	{
		cout << "登录数据读取错误" << endl;
	}
	if (!readFile1.is_open())
	{
		cout << "用户数据读取错误" << endl;
	}
	cout << "请输入您的账号（学工号）:";
	string account, password;
	cin >> account;
	int flag = 0;
	int temp=0;
	while (!readFile.eof())
	{
		string act;
		readFile >> act;
		if (act == account)//匹配账号 
		{
			flag=1; 
			cout << "请输入密码:";
			cin >> password;
			string pwd;
			readFile >> pwd;
			if (pwd == password)
			{
				cout << "登录成功!";
				flag = 1;
				while (!readFile1.eof())
				{
					
					readFile1 >> user;
					if(user->getId() == act)
					{
						cout<<"并且账号与个人信息验证成功！"<<endl;
						temp=1; 
						break;
					}
				}
				if(!temp)
				{
					cout<<"账户和本人信息验证不成功，请稍后去修改信息！"<<endl;
				}
				break;
			}
			else
			{
				cout << "密码错误，请重新登录" << endl;
				login(user, choice);
			}
		}

	}
	if (!flag)//存在问题 
	{
		cout << "学工号错误，请重输入！！！" << endl;
		login(user, choice);
	}
	readFile.close();
	readFile1.close();
}

void OperationManagement::Register(User* user, char choice)//注册一个账号 
{
	ofstream writeFile;
	ofstream writeFile1;
	if (choice == 'A')
	{
		writeFile1.open("teacher.txt", ios::app);
		writeFile.open("teacherLogin.txt",ios::app);
	}
	else
	{
		writeFile1.open("student.txt", ios::app);
		writeFile.open("studentLogin.txt",ios::app);
	}
	string pwd, act;
	cout << "请输入您的学工号作为注册账号:";
	cin >> act;
	user->setId(act);
	cout << "请输入您的注册密码:";
	cin >> pwd;
	user->setPassword(pwd);
	writeFile << endl << act << " " << pwd;
	cout << "请完善您的相应信息!" << endl;
	string  name, department, gender;
	cout << "您的姓名:";
	cin >> name;
	user->setName(name);
	cout << "您的性别:";
	cin >> gender;
	user->setGender(gender);
	cout << "您所在的院系:";
	cin >> department;
	user->setDepartment(department);
	writeFile1 <<endl<< act << " " << name << " " << gender << " " << department;//这里不能用user,因为在登录时才用，并且并没有初始化
	writeFile.close();
	writeFile1.close();
	
	int point=100;
	ofstream filec("creditpoint.txt",ios::app);
	filec<<endl<<act<<" "<<point;
	filec.close();
	
	cout << "注册成功！赶紧登录进入图书管吧!" << endl;
	login(user, choice);
}

void OperationManagement::userOperation(User* user, ManagementBooks mb)
{
	while (1)
	{
		OperationManagement action;
		cout<<"**************************************************************************************"<<endl;
		cout<<"**********************【读者】请根据提示完成各项操作！*******************************"<<endl;
		cout<<"\n\ta)进行借书" ;
		cout<<"\n\tb)查看本人当前借书情况" ;
		cout<<"\n\tc)进行还书";
		cout<<"\n\td)查询书籍";
		cout<<"\n\te)修改个人信息" ;
		cout<<"\n\tf)本周受欢迎图书榜"; 
		cout<<"\n\tg)查看个人信誉积分";
		cout<<"\n\th)退出程序"<<endl;;
		
		string msg="请输入a~h之间的字母！重新输入：";
		char choice;
		CharRange input('A','H',msg);
		cout<<"请输入你的选择：" ;
		choice=input.getChar();
		switch(choice)
		{
			case 'A':
				cout << "当前图书馆情况如下：" << endl;
				mb.showCurrentAllBook();
				cout << "是否有您想要借阅的图书(y/n)：";
				char s;
				cin >> s;
				if (s == 'y'||s=='Y')
				{
					user->borrowBookFromLibrary(mb);
				}
				break;
			case 'B':
				mb.checkBorrowedBook(user->getId());
				break;
			case 'C':
				user->returnBook(mb);
				break;
			case 'D':
				mb.findBook();
				break;
			case 'E':
				user->modifyinfo();
				break;
			case 'F':
				mb.popularbook();
				break;
			case 'G' :
				user->checkcredit();
				break;
			case 'H':
				cout<<"欢迎下次光临本图书馆！" <<endl;
				exit(0);
		}
	}
}

void OperationManagement::adminLogin(Administrator& admin)
{
	ifstream readFile("adminLogin.txt");
	ifstream readFile1("admin.txt");
	cout << "请输入您的工号:" ;
	string account, password;
	cin >> account;
	int flag = 0;
	int temp=0;
	while (!readFile.eof())
	{
		string act;
		readFile >> act;
		if (act == account)
		{
			flag=1;
			cout << "请输入密码:";
			cin >> password;
			string pwd;
			readFile >> pwd;
			if (pwd == password)
			{
				cout << "登录成功,欢迎您!" << endl;
				flag = 1;

				while (!readFile1.eof())
				{
					readFile1 >> admin;
					if(admin.getId() == act)
					{
						cout<<"并且账户和本人信息验证成功!"<<endl;
						temp=1;
						break;
					}
				}
				if(!temp)
				{
					cout<<"账户和本人信息验证不成功，请稍后去修改信息！"<<endl;
				}
				break;
			}
			else
			{
				cout << "密码错误，请重新登录" << endl;
				adminLogin(admin);
			}
		}

	}
	if (!flag)//此处存在问题 
	{
		cout << "学工号错误，请重输入" << endl;
		adminLogin(admin);
	}
	readFile.close();
	readFile1.close();

}

void OperationManagement::init(ManagementBooks& mb)
{
	mb.initBooks();//初始化，将书籍信息读入m_books 
	mb.initOutBook();//将信息读入m_outBookMap 
}

void OperationManagement::adminOperation(Administrator admin, ManagementBooks mb)
{
	while (1)
	{
		OperationManagement action;
		cout<<"***************************************************************************************"<<endl;
		cout<<"**********************【管理员】请根据提示完成各项操作！*******************************"<<endl;
		cout<<"\n\ta)添加新书" ;
		cout<<"\n\tb)查看当前借阅情况" ;
		cout<<"\n\tc)查看借阅人详细信息";
		cout<<"\n\td)查看当前所有图书信息情况" ;
		cout<<"\n\te)查找书籍"; 
		cout<<"\n\tf)删除书籍";
		cout<<"\n\tg)修改图书信息";
		cout<<"\n\th)查看本周图书馆受欢迎图书";
		cout<<"\n\ti)查看图书馆借书黑名单";
		cout<<"\n\tj)清空图书馆图书";
		cout<<"\n\tk)退出程序"<<endl;;
		
	    string msg="请输入a~j之间的字母！重新输入：";
		char choice;
		CharRange input('A','K',msg);
		cout<<"您的选择：" ;
		choice=input.getChar();
		string id;
		switch(choice)
		{
			case 'A':
				admin.addBook(mb);
				break;
			case 'B':
				mb.checekOutBook();
				break;
			case 'C':
				cout << "请输入您要查看借阅人的学工号:" ;
				cin >> id;
				mb.viewBorrowerDetails(id);
				break;
			case 'D':
				mb.showAllBooksInfo();
				break;
			case 'E':
				mb.findBook();
				break;
			case 'F':
				admin.deleteBook(mb);
				mb.clearallbook();
				action.init(mb);
				break;
			case 'G':
				admin.modifyBook(mb);
				mb.clearallbook();
				action.init(mb);
				break;
			case 'H':
				mb.popularbook();
				break;
			case 'I' :
				admin.checkblacklist();
				break;
			case 'J':
				mb.clearallbook();
				mb.outclear() ;
				cout<<"图书清空完毕！"<<endl ;
			case 'K':
				cout<<"欢迎管理员下次光临！"<<endl; 
				exit(0);
				break;
			
		}
	}
}


