#ifndef BOOK_H
#define BOOK_H
#include <string>
using namespace std;
class Book
{
private:
	string m_name;		//�鼮�� 
	string m_isbn;		//�鼮isbn�� 
	string m_pressInfo; //�鼮������ 
	double m_price;		//�鼮�۸� 
	int m_page;			//�鼮��ҳ�� 
	string m_author;	//�鼮���� 
	int m_num;			//�鼮���� 
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
	void checkIsnb();	//���isbn�� 
	bool isBorrowed();	//�Ƿ񱻽���״̬ 
	void showInfo();	//չʾ���鼮�������Ϣ 
	friend std::ostream& operator <<(std::ostream& os, const Book& book);	//����<< 
	friend std::istream& operator >>(std::istream& is,  Book& book);	//����>> 
};
#endif
