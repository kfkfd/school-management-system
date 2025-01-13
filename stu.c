#include "stulibsystem.h"

int InitStudent(Student* stu)
{
	stu->count = 0;
	stu->data = (StuInf*)calloc(DEFAULT_NUM, sizeof(StuInf));
	if (!stu->data)
	{
		printf("InitStudent::error:%s", strerror(errno));
		return -1;
	}
	stu->allnum = DEFAULT_NUM;
	LoadStu(stu);
	return 0;
}

void LoadStu(Student* stu)
{
	printf("加载学生信息...\n"); Sleep(300);
	FILE* sturead = fopen("stuinfo.txt", "rb");
	if (sturead == NULL)
	{
		perror("LoadStuinf");
		return;
	}
	StuInf tmp = { 0 };
	while (fread(&tmp, sizeof(StuInf), 1, sturead))
	{
		DilationtStu(stu);
		stu->data[stu->count] = tmp;
		stu->count++;
	}
	printf("->OK\n");
	Sleep(300);
}
void DilationtStu(Student* pc)
{
	if (pc->count == pc->allnum)
	{
		StuInf* ptr = (StuInf*)realloc(pc->data, (pc->allnum + DEFAULT_ADD) * sizeof(StuInf));
		if (!ptr)
		{
			printf("DilationtStu::error:%s", strerror(errno));
			return;
		}
		else
		{
			pc->data = ptr;
			pc->allnum += DEFAULT_ADD;
		}
		//printf("DilationtStu:已扩容\n");
	}
}
void AddStu(Student* ps)
{
	assert(ps);
	DilationtStu(ps);
	printf("请输入姓名->");
	scanf("%s", ps->data[ps->count].name);
	printf("请输入性别->");
	scanf("%s", ps->data[ps->count].gender);
	printf("请输入学号->");
	scanf("%s", ps->data[ps->count].id);
	ps->count++;
	printf("**ROOT:添加成功**\n");
}
static int FindStuByname(Student* ps,char name[])
{
	int i;
	for (i = 0; i < ps->count; i++)
	{
		if (strcmp(ps->data[i].name, name) == 0)
		{
			return i;
		}
	}
	return -1;
}
int FindByid(Student* ps, char id[20])
{
	int i;
	for (i = 0; i < ps->count; i++)
	{
		if (strcmp(ps->data[i].id,id ) == 0)
		{
			return i;
		}
	}
	return -1;
}
void FindStu(Student* ps)
{
	if (ps->count == 0)
	{
		printf("没有学生,无法查找\n");
		return;
	}
	printf("请输入要查找的学生的姓名->");
	char name[20] = { 0 };
	scanf("%s", &name);
	int ret = FindStuByname(ps,name);
	if (ret == -1)
	{
		printf("**ROOT:没找到该学生**\n");
		return;
	}
		printf("该学生信息如下\n");
		printf("%10s%10s%10s\n", ps->data[ret].name, ps->data[ret].gender, ps->data[ret].id);
	return;
}
void ShowAllStu(Student* ps)
{
	int i;
	printf("%20s %20s %20s", "姓名", "性别", "学号\n");
	for (i = 0; i < ps->count; i++)
	{
		printf("%20s %20s %20s\n", ps->data[i].name, ps->data[i].gender, ps->data[i].id);
	}
}
void DelStu(Student* ps)
{
	if (ps->count == 0)
	{
		printf("没有学生,无法删除\n");
		return;
	}
	char d_name[20] = { 0 };
	ShowAllStu(ps);
	printf("请输入要删除的学生姓名->");
	scanf("%s", d_name);
	int ret = FindStuByname(ps, d_name), i;
	if (ret == -1)
	{
		printf("**没有找到该学生**\n");
		return;
	}
	printf("请确认是否删除学生: %s (y/n)->", ps->data[ret].name);
	char cho;
	scanf(" %c", &cho);										// 注意在%c前有一个空格，用于忽略前面的换行符
	if (cho == 'y' || cho == 'Y')
	{
		for (i = ret; i < ps->count - 1; i++)
		{
			ps->data[i] = ps->data[i + 1];					//后面的内容向前覆盖以删除
		}
		ps->count--;
		printf("**ROOT:删除成功**\n");
	}
	else
		printf("**ROOT:取消操作**\n");
}
void ModifyStu(Student* ps)
{
	if (ps->count == 0)
	{
		printf("没有学生,无法修改\n");
		return;
	}
	char m_name[20] = { 0 };
	printf("请输入要修改的学生姓名->");
	scanf("%s", m_name);
	int ret = FindStuByname(ps, m_name);
	if (ret == -1)
	{
		printf("**没有找到该学生**\n");
		return;
	}
	char new_name[20] = { 0 }, new_gender[10] = { 0 }, new_id[20] = {0};
	printf("请输入新姓名->");
	scanf("%s", new_name);
	printf("请输入新性别->");
	scanf("%s", new_gender);
	printf("请输入新学号->");
	scanf("%s", new_id);
	strcpy(ps->data[ret].name, new_name);
	strcpy(ps->data[ret].gender, new_gender);
	strcpy(ps->data[ret].id, new_id);
	printf("ROOT:**修改完成**\n");
}

void SaveStuinfo(Student* ps)
{
	FILE* sturead = fopen("stuinfo.txt", "wb");
	int i;
	for (i = 0; i < ps->count; i++)
	{
		fwrite(ps->data + i, sizeof(StuInf), 1, sturead);
	}
	fclose(sturead);
	sturead = NULL;
}
int s_main(Student* stu)
{
	int cho = 0;
	do
	{
	CONTINUE:
		printf("+----------+\n");
		printf("|  1.add   |\n| 2.delete |\n| 3.modify |\n|  4.find  |\n|5.show all|\n|  0.exit  |\n");
		printf("+----------+\n");
		printf("请选择-->");
		scanf("%d", &cho);
		switch (cho)
		{
		case ADD:
			AddStu(stu); 
			break;
		case DEL:
			DelStu(stu); 
			break;
		case MODIFY:
			ModifyStu(stu); 
			break;
		case FIND:
			FindStu(stu); 
			break;
		case 5:
			ShowAllStu(stu);
			break;
		case EXIT:
			SaveStuinfo(stu);
			printf("确认退出系统?(y/n)-->");
			char ch;
			scanf(" %c", &ch);
			if (ch == 'y' || ch == 'Y') 
			{
				printf("ROOT:break\n");
				break;
			}
			else
				goto CONTINUE;
		default:
			printf("**ROOT:请输入正确的序号**\n\n");
			break;
		}
	} while (cho);
	return 0;
}