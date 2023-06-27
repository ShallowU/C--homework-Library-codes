#ifndef MANAGEMENTBOOKS_H
#define MANAGEMENTBOOKS_H
#include<iostream>
#include"Book.h"
#include<vector>		//使用vector这样的动态数组来储存书籍信息 
#include<unordered_map>	//用来储存借书人以及借走书的信息 
#include<fstream>
#include<string>
using namespace std;
class ManagementBooks
{
private:
	vector<Book> m_books;//可视为储存Book类的数据动态数组 
	int m_allBookNum;  	 //书籍总数 
	unordered_multimap<string, string>m_outBookMap;//运用哈希便于查找借书人与借走书籍的联系 

public:
	void showCurrentAllBook();
	ManagementBooks();
	void addBook(Book book);
	void findBook();
	bool deleteBook(string bookname) ;
	bool modifyBook(Book book,string oldname) ;
	void clearallbook();
	void outclear();
	int getAllBookNum();
	void showAllBooksInfo();
	bool borrow(string name);
	void Return(string id,string bookName);
	void initOutBook();
	void checekOutBook();
	void popularbook();
	void initBooks();
	int checkBorrowedBook(string userId);
	void viewBorrowerDetails(string id);
	bool checkTrueBorrow(string id,string bookName);
	void setMapValue(string userId, string bookName);
};
#endif
