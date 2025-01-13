#include "stulibsystem.h"
#define _CRT_SECURE_NO_WARNINGS

 static bool LoginRoot(int* count)
{
	printf("Please enter the administrator account->");
	char a[20] = { 0 }, p[20] = {0};
	scanf(" %s", &a);
	printf("Please enter the administrator password->_____\b\b\b\b\b");
	scanf(" %s", &p);
	if (strcmp("administr", a) == 0 && strcmp("12345", p) == 0)
	{
		printf("ROOT::Login Successful!\n");
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
	 printf("�����빤��");
	 char id[20] = { 0 }, passward[20] = {0};
	 scanf("%s", &id);
	 printf("����������");
	 scanf("%s", &passward);
	 int ret = FindTecByid(ps,id); 
	 if (ret != -1)
	 {
		 if (strcmp(ps->data[ret].passward, passward) == 0)
		 {
			 printf("%s : Login Successful!\n",ps->data[ret].name);
			 (*num) = ret;
			 return true;
		 }
		 else
		 {
			 (*count)++; //�������
			 return false;
		 }
	 }
	 else
	 {
		 (*count)++;
		 printf("�Ҳ������û�\n");
		 return false;
	 }
 }
 static int LoginStu(Student* stu,int* num)
 {
	 printf("������ѧ��->");
	 char id[20] = { 0 };
	 scanf("%s", &id);
	 int ret = FindByid(stu, id);
	 if (ret == -1)
	 {
		 printf("��������ȷ��ѧ��\n");
		 return 0;
	 }
	 else
	 {
		 (*num) = ret;
		 printf("%s ͬѧ:Login Successful!\n", stu->data[ret].name);
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
			 printf("**��лʹ��**");
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
		 printf("|  1.�޸�����  |\n|2.ѧ����Ϣ����|\n|    0.�˳�    |\n");
		 printf("+--------------+\n");
		 printf("��ѡ��->");
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
		 printf("|1.����ͼ����Ϣ|\n|    2.����    |\n|    3.����    |\n|    0.�˳�    |\n");
		 printf("+--------------+\n");
		 printf("��ѡ��->");
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
			 printf("��������ȷ��ѡ��");
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
	//��ӭʹ��ѧУͼ����ۺϹ���ϵͳ
	//��ʼ�������ṹ��
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