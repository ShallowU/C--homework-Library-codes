#include "ManagementBooks.h"
#include <string>
using namespace std;

void ManagementBooks::showCurrentAllBook()	//查看书籍和剩余数 
{
	for (int i = 0; i < m_allBookNum; i++)
	{
		cout << "书名:" << m_books[i].getName() <<" " << "剩余数量" << m_books[i].getNum() << endl;
	}
}

ManagementBooks::ManagementBooks()
{
	m_allBookNum = 0;	//初始为0 
}

void ManagementBooks::addBook(Book book)
{
	int flag = 0;//用于标记图书库是否有此书 
	for (int i = 0; i < m_allBookNum; i++)
	{
		if (m_books[i].getName() == book.getName())//为旧书 
		{
			flag = 1;
			m_books[i].setNum(m_books[i].getNum() + book.getNum());
			ofstream writeFile("library.txt", ios::out);//打开文件重修修改书库 
			for (int i = 0; i < m_allBookNum; i++)
			{
				writeFile << m_books[i];//已经重载了<< 
			}
			writeFile.close();
			break;
		}
	}
	if (!flag)//为新书 
	{
		ofstream writeFile("library.txt", ios::app);
		m_books.push_back(book);//书籍用push_back新加一本 
		m_allBookNum++;
		writeFile << book;//已经重载<< 
		writeFile.close();
	}
}
bool ManagementBooks::modifyBook(Book book,string oldname)
{
	int flag=0;
	for (int i = 0; i < m_allBookNum; i++)
	{
		if (m_books[i].getName() == oldname)//为旧书 
		{
			m_books[i]=book;
			flag=1;
			break;
		}
	}
	ofstream writeFile("library.txt", ios::out);//打开文件重修修改书库 
	for (int i = 0; i < m_allBookNum; i++)
	{
		writeFile << m_books[i];//已经重载了<< 
	}
	writeFile.close();
	if(flag)
		return true;
	else 
		return false;
}
bool ManagementBooks::deleteBook(string bookname)
{
	int temp=0;
	int flag=0;
	for (int i = 0; i < m_allBookNum; i++)
	{
		if (m_books[i].getName() == bookname)//为旧书 
		{
			temp=i;
			flag=1;
			break;
		}
	}
	ofstream writeFile("library.txt");//打开文件重修修改书库
	for (int i = 0; i < m_allBookNum; i++)
	{
		if(i==temp)
			continue;
		writeFile << m_books[i];//已经重载了<<
	}
	writeFile.close();
	if(flag)
		return true;
	else
		return false;
}
void ManagementBooks::findBook()
{
	string bookname;
	int flag=0;
	cout<<"您所求的书籍名：";
	cin>>bookname; 
	for (int i = 0; i < m_allBookNum; i++)
	{
		if (m_books[i].getName() == bookname)
		{
			cout<<"此书已经查询到，下面为相关信息："<<endl; 
			m_books[i].showInfo();
			flag=1;
			break;
		}	
	}
	if(!flag)
	{
		cout<<"抱歉 图书馆没有此书相关信息！"<<endl;
	}	
}

int ManagementBooks::getAllBookNum()
{
	return m_allBookNum;
}

void ManagementBooks::showAllBooksInfo()
{
	for (int i = 0; i < m_allBookNum; i++)
	{
		m_books[i].showInfo();//展示书籍所有信息 
	}
}

bool ManagementBooks::borrow(string name)
{

	for (int i =0; i <m_allBookNum; i++)
	{
		if (m_books[i].getName() == name)
		{
			if (m_books[i].getNum() >= 1)
			{
				m_books[i].setNum(m_books[i].getNum() - 1);
				cout << "      借书成功呀！" << endl;
				ofstream writeFile("library.txt");//重新修改图书库 
				for (int i = 0; i < m_allBookNum; i++)
				{
					writeFile << m_books[i];
				}
				writeFile.close();
				return true;//借书成功 
			}
			else
			{
				cout << "此书数量不足" << endl;
				return false;
			}
		}

	}
	cout << "很抱歉，暂无此书" << endl;
	return false;
}

void ManagementBooks::Return(string id,string bookName)
{
	Book book;
	book.setName(bookName);
	addBook(book);
	ofstream writeFile("borrowedBook.txt",ios::out);
	for (auto iter =m_outBookMap.begin(); iter != m_outBookMap.end(); ++iter)//运用auto迭代容器遍历循秩 m_outBookMap
	{
		if (iter->first == id && iter->second == bookName)//信息比对均符合 
		{
			m_outBookMap.erase(iter);
			break;
		}
	}
	for (auto map : m_outBookMap)//直接遍历重新修改借书人信息的文件 
	{
		writeFile << endl << map.first << " " << map.second;
	}
	writeFile.close();
}

void ManagementBooks::initOutBook()//将借书人的数据与 m_outBookMap联系 
{
	ifstream readFile("borrowedBook.txt");
	if (!readFile.is_open())
	{
		cout << "查看全体借书情况数据读取出错" << endl;
	}
	else
	{
		while (!readFile.eof())
		{
			string studentId, bookName;
			readFile >> studentId >> bookName;
			m_outBookMap.insert(pair<string, string>(studentId, bookName));//将借书人和借书名联系一起便于查找 
		}
	}
	readFile.close();

}

void ManagementBooks::checekOutBook()//查看借书情况（借书人及对应的书籍名） 
{
	for (auto map : m_outBookMap)	//for(auto map: m_outBookMap)
	{
		cout << "借阅人学工号:" << map.first<<" " << "借阅书名:" << map.second << endl;
	}
}

void ManagementBooks::initBooks()
{
	ifstream readFile;
	readFile.open("library.txt");
	if (!readFile.is_open())
	{
		cout << "图书数据读取错误" << endl;
		readFile.close();
		return ;
	}
	m_allBookNum=0;
	while (!readFile.eof())
	{
		
		Book book;
		readFile >> book;//已经重载<< 
		m_allBookNum++;
		m_books.push_back(book);//读入m-books中 
	}
	readFile.close();
}
void ManagementBooks::clearallbook()
{
	m_books.clear();
}
void ManagementBooks::outclear()
{
	ofstream writeFile("library.txt");
	writeFile<<" ";
	writeFile.close();
}
int ManagementBooks::checkBorrowedBook(string userId)//展示个人借的全部书籍 ,需要还的书籍一共多少本 
{
	
	int flag = 0;
	for (auto map : m_outBookMap)
	{
		if (userId == map.first)
		{
			if (!flag)
			{
				cout << "您已经借的全部图书如下：" << endl;
				flag++;
			}
			else
			{
				flag++;
			}
			cout << map.second << " ";
		}
	}
	if (!flag)
	{
		cout << "       【您目前没有借书 】        " << endl;
	}
	cout << "即当前一共借书：" << flag << "   本";
	cout << endl;
	return flag;
}

void ManagementBooks::popularbook()
{
	ifstream filepopular("popularbook.txt");
    string popularbook[50];
    int a[50];
    int i=0,j=0,flag1=0;
    int flag2=0,flag3=0;
    while(!filepopular.eof())
    {
		filepopular>>popularbook[i]>>a[i];
  		i++;
	}
	filepopular.close();
	int maxfirst=a[0];
	int maxsecond=a[0];
	int maxthird=a[0];
	for(j=0;j<i;j++)
	{
		if(a[j]>maxfirst)
		{
			maxfirst=a[j];
			flag1=j;
		}
	}
	for(j=0;j<i;j++)
	{
		if(j==flag1)
			continue;
		if(a[j]>maxsecond)
		{
			maxsecond=a[j];
			flag2=j;
		}
	}
	for(j=0;j<i;j++)
	{
		if(j==flag1||j==flag2)
			continue;
		if(a[j]>maxthird)
		{
			maxthird=a[j];
			flag3=j;
		}
	}
	cout<<"图书前三popular排行榜如下："<<endl;
	cout<<"top1:"<<popularbook[flag1]<<endl;
	cout<<"top2:"<<popularbook[flag2]<<endl;
	cout<<"top3:"<<popularbook[flag3]<<endl;
}

void ManagementBooks::viewBorrowerDetails(string id)//查看借书人具体的信息 
{
	ifstream readFile("teacher.txt");
	ifstream readFile1("student.txt");
	int flag = 0;//用于判断时学生还是老师 
	if (!readFile1.is_open()|| readFile.fail()) 
	{
		cout << "用户数据读取错误" << endl;
	}
	while (!readFile1.eof())
	{
		string act1, name, department, gender;
		readFile1 >> act1 >> name >> gender >> department;
		if (id == act1)
		{
			cout<<"用户类别:"<<"学生"<<" " << "用户姓名:" << name << " " << "用户性别:" << gender << " " << "用户所在部门:" << department << endl;
			flag = 1;
		}
	
	}
	if (!flag)
	{
		while (!readFile.eof())
		{
			string act1, name, department, gender;
			readFile >> act1 >> name >> gender >> department;
			if (id == act1)
			{
				flag = 1;
				cout << "用户类别:"<<"老师"<<" " << "用户姓名:" << name << " " << "用户性别:" << gender << " " << "用户所在部门:" << department << endl;
			}

		}
	}
	if (!flag)
	{
		cout << "无此用户！" << endl;
	}
	readFile.close();
	readFile1.close();
}

bool ManagementBooks::checkTrueBorrow(string id, string bookName)//查看某人是否借了某书 
{
	
	for (auto map : m_outBookMap)//遍历借书人 
	{
		if (map.first == id && map.second == bookName)
		{
			return true;
		}
	}
	return false;
}

void ManagementBooks::setMapValue(string userId,string bookName)//加入新的一个借书人及其借的书籍 
{
	m_outBookMap.insert(pair<string, string>(userId, bookName));
}


