//
// stulibsystem.h
//
//      Copyright (c) JinlongHan Corporation. All rights reserved.
//
// The The Student And Library System <stulibsystem.h> header.
//

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>
#include <conio.h>


#define DEFAULT_NUM 3
#define DEFAULT_ADD 5
#define MAX_TIME_DAY 180

//枚举选择
enum Cho {
	EXIT, ADD, DEL, MODIFY, FIND,BOR,RET
};

/*
*
*
*    定义信息
*
*/

//图书
typedef struct BookInf {
	char name[40];
	char author[20];
	char bokid[10];
	char bokwher[20];
	int boknum;
}BookInf;

typedef struct Library {
	BookInf* data;
	int count;
	int allnum;
}Library;

//学生
typedef struct StuInf {
	char name[20];
	char gender[6];
	char id[20];
}StuInf;

typedef struct Student {
	StuInf* data;
	int count;
	int allnum;  //allnum是当前分配的总容量
}Student;

//教师
typedef struct TecInf {
	char name[20];
	char gender[6];
	char id[20];
	char passward[20];
}TecInf;
typedef struct Teacher {
	TecInf* data;
	int count;
	int allnum;
}Teacher;

//借还书信息
typedef struct RBinfo {
	char sname[20];
	char sid[20];

	char bname[20];
	char bid[20];

	char btime[20];
	char rtime[20];

	char state[8];//未还，已还，逾期
}Rbinfo;

typedef struct Rb {
	Rbinfo* data;
	int count;
	int allnum;
}Rb;

/*
*
*
*    函数声明
*
*/
int Login(Teacher* tec,Student* stu,int* num);



//about book
int InitLibrary(Library* pc);
void AddBook(Library* pc);
void DilationBok(Library* pc);
void FindBook(Library* pc);
void BorBook(Student* stu, Library* pc, Rb* rb, int* num);
void RetBook(Student* stu, Library* pc, Rb* rb, int* num);
int l_main(Library* lib,Rb*rb);
void SaveBokinfo(Library* pc);


//about teacher
int InitTeacher(Teacher* ps);
void LoadTec(Teacher* ps);
void DilationtTec(Teacher* pc);
int FindTecByid(Teacher* ps, char id[20]);
int t_main_root(Teacher* tec);

void modifytecmm(tec, num);
void SaveTecinfo(Teacher* ps);


//about student
int InitStudent(Student* stu);
void DilationtStu(Student* pc);
void ShowAllStu(Student* ps);
void LoadStu(Student* stu);
int s_main(Student* stu);
int FindByid(Student* ps, char id[20]);

//about rb
int InitRbinfo(Rb* rb);
void SaveRbinfo(Rb* rb);
void DilationRb(Rb* pc);
void ShowAllRbinfo(Rb* rb);