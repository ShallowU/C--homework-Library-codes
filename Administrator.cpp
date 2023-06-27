#include "Administrator.h"
void Administrator::addBook(ManagementBooks& mb)
{
	Book book;
	cout << "当前图书馆情况如下:" << endl;
	mb.showAllBooksInfo();
	cout << "请输入您要增加的图书信息!" << endl;
	string name, author;
	string press;
	int pages;
	double price;
	int num;
	cout << "请输入增加的图书书名：" ;
	cin >> name;
	cout << "请输入增加的图书的作者：";
	cin >> author;
	cout << "请输入增加的图书价格：" ;
	cin >> price;
	cout << "请输入增加的图书的出版社：";
	cin >> press;
	cout << "请输入增加图书的总页数：";
	cin >> pages;
	cout << "请输入增加的图书的本数：" ;
	cin >> num;
	book.setName(name);
	book.setAuthor(author);
	book.setPressInfo(press);
	book.setPage(pages);
	book.setNum(num);
	book.setPrice(price);
	mb.addBook(book);
	cout << "新增图书成功!" << endl;
}
void Administrator::modifyBook(ManagementBooks& mb)
{
	Book book;
	mb.findBook();
	cout<<"下面请输入新的图书信息："<<endl;
	string name, author;
	string press;
	int pages;
	double price;
	int num;
	cout << "请输入新的的图书书名：" ;
	cin >> name;
	cout << "请输入新的的图书的作者：";
	cin >> author;
	cout << "请输入新的的图书价格：" ;
	cin >> price;
	cout << "请输入新的的图书的出版社：";
	cin >> press;
	cout << "请输入新的图书的总页数：";
	cin >> pages;
	cout << "请输入新的的图书的本数：" ;
	cin >> num;
	book.setName(name);
	book.setAuthor(author);
	book.setPressInfo(press);
	book.setPage(pages);
	book.setNum(num);
	book.setPrice(price);
	string oldname;
	cout<<"请再次输入原图书名来确定：";
	cin>>oldname;
	if(mb.modifyBook(book,oldname))
		cout<<"修改图书信息成功！"<<endl;
	else
		cout<<"修改图书信息失败！"<<endl;
}
void Administrator::deleteBook(ManagementBooks& mb)
{
	string bookname;
	mb.findBook();
	char ch;
	cout<<"是否确认删除该书？（y/n):";
	cin>>ch;
	if(ch=='y'||ch=='Y') 
	{
		cout<<"请再次输入你要删除的书名：";
		cin>>bookname;
		if(mb.deleteBook(bookname))
			cout<<"删除书籍："<<bookname<<"成功！"<<endl;
		else
			cout<<"删除失败，未找到该书！"<<endl;
	}
	else
		cout<<"好的，删除取消"<<endl;
}
void Administrator::checkblacklist()
{
	ifstream file("creditpoint.txt");
	string account[60];
    int point[60];
	int i=0,j=0,k=0;
	string badaccount[30];
	int badpoint[30];
	while(!file.eof())
	{
	    file>>account[i]>>point[i];
	    i++;
	}
	file.close();
	for(j=0;j<i;j++)
	{
		if(point[j]<75)
		{
			badaccount[k]=account[j];
			badpoint[k]=point[j];
			k++;
		}
	}
	cout<<"图书馆黑名单如下："<<endl;
	for(j=0;j<k;j++)
	{
		cout<<"学工号："<<badaccount[j]<<"  "<<"信誉分："<<badpoint[j]<<endl;
	} 
}
void  Administrator::setId(string id)
{
	m_id = id;
}

void Administrator::setName(string name)
{
	m_name = name;
}

void Administrator::setGender(string gender)
{
	m_gender = gender;
}
void Administrator::setDepartment(string department)
{
	m_department = department;
}
void Administrator::showInfo()
{
	cout << "姓名:" << m_name << " " << "工号:" << m_id << " " << "性别:" << m_gender << " " << "部门:" << m_department <<endl;
}

std::istream& operator>>(std::istream& is, Administrator& admin)//重载>>用于读文件 
{
	is >> admin.m_id >> admin.m_name >> admin.m_gender >> admin.m_department;
	return is;
}
string Administrator::getId()
{
	return m_id;
}

string Administrator::getName()
{
	return m_name;
}

string Administrator::getGender()
{
	return m_gender;
}

string Administrator::getDepartment()
{
	return m_department;
}
