#ifndef BOOK_H
#define BOOK_H
#include <string>
using namespace std;
class Book
{
private:
	string m_name;		//书籍名 
	string m_isbn;		//书籍isbn号 
	string m_pressInfo; //书籍出版社 
	double m_price;		//书籍价格 
	int m_page;			//书籍总页数 
	string m_author;	//书籍作者 
	int m_num;			//书籍数量 
	//int borrowtime;
public:
	Book(string m_name, string m_isbn,string m_pressInfo,double m_price,string m_author,int m_num)
	:m_name(m_name), m_isbn(m_isbn), m_pressInfo( m_pressInfo), m_price(m_price), 
	m_author(m_author),m_num(m_num) {}
	Book();
	void setNum(int num);
	int getNum();
	void setName(string name);
	string getName();
	void setIsbn(string isbn);
	string getIsbn();
	void setPressInfo(string perssInfo);
	string getPressInfo();
	void setPrice(double price);
	double getPrice();
	void setPage(int page);
	int getPage();
	void setAuthor(string author);
	string getAuthor();
	void checkIsnb();	//检查isbn号 
	bool isBorrowed();	//是否被借走状态 
	void showInfo();	//展示该书籍的相关信息 
	friend std::ostream& operator <<(std::ostream& os, const Book& book);	//重载<< 
	friend std::istream& operator >>(std::istream& is,  Book& book);	//重载>> 
};
#endif
