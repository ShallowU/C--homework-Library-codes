#include "Student.h"
#include<fstream>
#include <ctime>
using  namespace std;

Student::Student()
{
    m_class="信息安全";
}

void Student::showInfo()
{
    cout << "姓名:" << m_name << " " << "学号:" << m_id << " " << "性别:" << m_gender << " " << "院系:" << m_department << " "<<"班级:"<<m_class<<endl;
}

void Student::borrowBookFromLibrary(ManagementBooks& mb)
{
    int all = mb.checkBorrowedBook(m_id);
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
    if (all < 6&&point[flag]>=75)
    {
        string name;
        cout << "请输入您要借的书名:" ;
        cin >> name;
        if (mb.borrow(name))
        {
        	time_t timenow;
        	time(&timenow);
        	tm *p=localtime(&timenow);
        	borrowTime=*p;
        	returnTime=*p;
        	returnTime.tm_mon++;
        	if(returnTime.tm_mon==12)
        	{
        		returnTime.tm_mon=0;
        		returnTime.tm_year++;
			}
			cout<<"您的借书时间为：" <<get_borrowTime();//此处可能有问题
			cout<<"您的还书时间为：" << get_returnTime();
			char buffer[20];
 			strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S",&returnTime ); 
 			
			ofstream file("borrowedtimeStu.txt", ios::app);
            ofstream writeFile("borrowedBook.txt", ios::app);//用追加方式  
            
            ifstream filepopular("popularbook.txt");
            string popularbook[50];
            int a[50];
            int i=0,flag=0;
            while(!filepopular.eof())
            {
            	filepopular>>popularbook[i]>>a[i];
            	i++;
			}
			for(int j=0;j<i;j++)
			{
				if(name==popularbook[j])
				{
					a[j]++;
					flag=1;
					break;
				}
			}
			filepopular.close();
			ofstream filepopular1;
			if(flag)
			{
				filepopular1.open("popularbook.txt",ios::out);
				for(int k=0;k<i;k++)
				{
					filepopular1<<endl<<popularbook[k]<<" "<<a[k];
				}
			}
			else
			{
				filepopular1.open("popularbook.txt",ios::app);
				popularbook[i]=name;
				a[i]=1;
				
				filepopular1<<endl<<popularbook[i]<<" "<<a[i];
			}
			filepopular1.close();
            mb.setMapValue(m_id, name);//将借书人和书籍名联系一起 
            writeFile << endl << m_id << " " << name;//新借的相关信息写进 borrowedBook.txt
            file<<endl<<m_id<<" "<<buffer;
            file.close();
            writeFile.close();
        }
    }
    else
    {
        cout << "您目前不能借书，可能是已经超过了最大可借阅数或者信誉分低于75！" << endl;
    }
    
}

void Student::setClass(string Class)
{
    m_class = Class;
}

string Student::getClass()
{
    return m_class;
}


