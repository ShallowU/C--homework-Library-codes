#ifndef TEACHER_H
#define TEACHER_H   
#include "User.h"
#include"ManagementBooks.h"
#include<fstream>
class Teacher : public User//¹«ÓÐ¼Ì³Ð 
{
public:
    Teacher();
    void borrowBookFromLibrary(ManagementBooks& mb);
    void showInfo();
};
#endif
