#include "stulibsystem.h"
#define _CRT_SECURE_NO_WARNINGS

//Get the password, don't show it

static char* getpassword(void) {
	char password[20];
	int i = 0;
	while (1) {
		password[i] = _getch();  // 读取一个字符，不回显到控制台
		if (password[i] == '\r' || password[i] == '\n') {  // 按下回车键结束输入
			password[i] = '\0';
			break;
		}
		else if (password[i] == '\b') {  // 按下退格键
			if (i > 0) {
				i--;
				printf("\b \b");  // 删除最后一个星号
			}
		}
		else {
			printf("*");  // 显示星号
			i++;
		}
	}
	return password;
}

 static bool LoginRoot(int* count)
{
	printf("Please enter the administrator account->");
	char a[20] = { 0 };
	scanf(" %s", &a);
	printf("Please enter the administrator password->_____\b\b\b\b\b");
	char* p = getpassword();
	if (strcmp("administr", a) == 0 && strcmp("12345", p) == 0)
	{
		printf("\nROOT::Login Successful!\n");
		return true;
	}
	else
	{
		(*count)++;
		printf("Incorrect account or password!\n");
		return false;
	}
}
 static bool LoginTec(Teacher* ps,int* count,int* num)
 {
	 printf("请输入工号->");
	 char id[20] = { 0 };
	 scanf("%s", &id);
	 printf("请输入密码->");
	 char* password = getpassword();
	 int ret = FindTecByid(ps,id); 
	 if (ret != -1)
	 {
		 if (strcmp(ps->data[ret].passward, password) == 0)
		 {
			 printf("\n%s : Login Successful!\n",ps->data[ret].name);
			 (*num) = ret;
			 return true;
		 }
		 else
		 {
			 (*count)++; //错误叠加
			 return false;
		 }
	 }
	 else
	 {
		 (*count)++;
		 printf("找不到该用户\n");
		 return false;
	 }
 }
 static int LoginStu(Student* stu,int* num)
 {
	 printf("请输入学号->");
	 char id[20] = { 0 };
	 scanf("%s", &id);
	 int ret = FindByid(stu, id);
	 if (ret == -1)
	 {
		 printf("请输入正确的学号\n");
		 return 0;
	 }
	 else
	 {
		 (*num) = ret;
		 printf("%s 同学:Login Successful!\n", stu->data[ret].name);
		 return 1;
	 }
 }
 void Root(Library* lib,Student* stu,Teacher* tec,Rb*rb)
 {
	 int cho;
	 do {
		 printf("+---------+\n");
		 printf("|1.student|\n|2.teacher|\n| 3.book  |\n| 0.exit  |\n");
		 printf("+---------+\n");
		 printf("Root::Select operation object->");
		 scanf("%d", &cho);
		 switch (cho)
		 {
		 case 1:
			 s_main(stu);
			 break;
		 case 2:
			 t_main_root(tec);
			 break;
		 case 3:
			 l_main(lib, rb);
			 break;
		 case 0:
			 printf("EXIT\n");
			 printf("**感谢使用**");
			 break;
		 default:
			 printf("Please choose true num!\n");
			 break;
		 }
	 }while (cho);
	 
 }
 void TecSys(Student* stu,Teacher* tec,int* num)
 {
	 int cho = 0;
	 do {
		 printf("+--------------+\n");
		 printf("|  1.修改密码  |\n|2.学生信息操作|\n|    0.退出    |\n");
		 printf("+--------------+\n");
		 printf("请选择->");
		 scanf("%d", &cho);
		 switch (cho)
		 {
		 case 1:
			 modifytecmm(tec,num);
			 break;
		 case 2:
			 s_main(stu);
			 break;
		 case 0:
			 SaveTecinfo(tec);
			 break;
		 }
	 }while(cho);
 }
 void StuSys(Student* stu,Library* lib,Rb* rb,int* num)
 {
	 int cho =0;
	 do
	 {
		 printf("+--------------+\n");
		 printf("|1.查找图书信息|\n|    2.借书    |\n|    3.还书    |\n|    0.退出    |\n");
		 printf("+--------------+\n");
		 printf("请选择->");
		 scanf("%d", &cho);
		 switch (cho)
		 {
		 case 1:
			 FindBook(lib);
			 break;
		 case 2:
			 BorBook(stu,lib,rb,num);
			 break;
		 case 3:
			 RetBook(stu, lib, rb, num);
			 break;
		 case 0:
			 break;
		 default:
			 printf("请输入正确的选项");
		 }
	 } while (cho);
	 SaveBokinfo(lib);
	 SaveRbinfo(rb);
	 return;
 }
int Login(Teacher* tec, Student* stu,int* num)
{
	printf("\nLogin...\n");
	int cho = 0;
	do {
	printf("1.teacher\n2.student\n3.administrator\n0.EXIT");
	printf("\nPlease choose your identity-->");
	int count = 1;
	scanf("%d", &cho);
		if (cho == 1)
		{
			if (LoginTec(tec, &count,num))
			{
				return 1;
			}
			else
			{
				if (count > 3)
				{
					printf("Entered incorrectly 3 times in a row\n");
					count = 1;
					return -1;
				}
				printf("please try again\n");
			}
		}
		else if (cho == 2)
		{
			if (LoginStu(stu, num))
				return 2;
		}
		else if (cho == 3)
		{
			if (LoginRoot(&count))
			{
				return 3;
			}
			else
			{
				if (count > 3)
				{
					printf("Entered incorrectly 3 times in a row\n");
					count = 1;
					return -1;
				}
				printf("Please try again\n");
			}
		}
		else if (cho == 0)
			return 0;
		else
		{
			printf("Please choose true num!\n");
		}
	} while (cho);
	return 0;
}

int main()
{
	printf("Welcome to the School Library Integrated Management System\n");
	//欢迎使用学校图书馆综合管理系统
	//初始化各个结构体
	Library lib;
	InitLibrary(&lib);
	Student stu;
	InitStudent(&stu);
	Teacher tec;
	InitTeacher(&tec);
	Rb rbi;
	InitRbinfo(&rbi);
	int num = 0;
	int ret = Login(&tec,&stu,&num);
	switch (ret)
	{
	case 1:
		TecSys(&stu,&tec,&num);
		break;
	case 2:
		StuSys(&stu,&lib,&rbi,&num);
		break;
	case 3:
		Root(&lib,&stu,&tec,&rbi);
		break;
	default:
		break;
	}
	SaveBokinfo(&lib);
	return 0;
}
/*write by Jinlon Han*/