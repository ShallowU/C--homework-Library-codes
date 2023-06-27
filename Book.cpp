#include "Book.h"
#include <iostream>
#include<fstream>
using namespace std;


Book::Book()
{
	string b = "";
	string randStr = "0123456789X";
	for (int i = 0; i <= 12; i++)	//随机设置ISBN号 
	{
		if (i == 1 || i == 5 || i == 11)
		{
			b += '-';
		}
		else
		{
			if (i == 12)
			{
				b += randStr[rand() % 11];
			}
			else
			{
				b += randStr[rand() % 10];
			}
		}
	}
	m_isbn = b;
}

void Book::setNum(int num)
{
	m_num = num;
}

int Book::getNum()
{
	return m_num;
}

void Book::setName(string name)
{
	m_name = name;
}

string Book::getName()
{
	return m_name;
}

void Book::setIsbn(string isbn)
{
	m_isbn = isbn;
}

string Book::getIsbn()
{
	return m_isbn;
}

void Book::setPressInfo(string perssInfo)
{ 
	m_pressInfo = perssInfo;
}

string Book::getPressInfo()
{
	return m_pressInfo;
}

void Book::setPrice(double price)
{
	m_price = price;
}

double Book::getPrice()
{
	return m_price;
}

void Book::setPage(int page)
{
	m_page = page;

}

int Book::getPage()
{
	return m_page;
}

void Book::setAuthor(string author)
{
	m_author = author;
}

string Book::getAuthor()
{
	return m_author;
}

void Book::checkIsnb()
{
	int sum = 0;
	for (int i = 0, j = 1; i < m_isbn.size(); i++) {
		if (m_isbn[i] != '-' && i != 12) {
			sum += (m_isbn[i] - '0') * j;
			j++;
		}

	}
	sum %= 11;
	char c = 'X';
	if (sum < 10) c = sum + '0';
	if (m_isbn[12] == c) puts("This book isbn are Right!");
	else puts("This book isbn are wrong!");
}

bool Book::isBorrowed()
{
	if (m_num >= 1)
	{
		m_num--;
		return true;
	}
	return false;
}

void Book::showInfo()
{
	cout<<"作者:" << m_author << " "<<"isbn号码:" << m_isbn << " " <<"书本名称:"<< m_name << " "
		<<"总页数:" << m_page << " " <<"出版社:" << m_pressInfo << " " <<"价格:" << m_price
		<< " " <<"剩余本数:"<<m_num<< endl;
}

std::ostream& operator <<(std::ostream& os, const Book& book)
{
	os << endl <<book.m_name << " " <<book.m_isbn << " " << book.m_pressInfo << " " <<book.m_price << " " << book.m_page << " " << book.m_author << " " << book.m_num;
	return os;
}

std::istream& operator>>(std::istream& is,  Book& book)	//加入了const可能报错 
{
	is >> book.m_name >> book.m_isbn >> book.m_pressInfo >> book.m_price >>book.m_page >> book.m_author >> book.m_num;
	return is;
}
