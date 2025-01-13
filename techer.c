#include "stulibsystem.h"

int InitTeacher(Teacher* ps)
{
	ps->count = 0;
	ps->data = (TecInf*)calloc(DEFAULT_NUM, sizeof(TecInf));
	if (!ps->data)
	{
		printf("InitTeacher::error:%s", strerror(errno));
		return -1;
	}
	ps->allnum = DEFAULT_NUM;
	LoadTec(ps);
	return 0;
}

void LoadTec(Teacher* ps)
{
	printf("加载教师信息...\n"); Sleep(500);
	FILE* tecread = fopen("tecinfo.txt", "rb");
	if (tecread == NULL)
	{
		perror("LoadTecinf");
		return;
	}
	TecInf tmp = { 0 };
	while (fread(&tmp, sizeof(TecInf), 1, tecread)) //fread返回成功读取的元素总数
	{
		DilationtTec(ps);
		ps->data[ps->count] = tmp;
		ps->count++;
	}
	printf("->OK\n");
	Sleep(300);
}
void DilationtTec(Teacher* pc)
{
	if (pc->count == pc->allnum)
	{
		TecInf* ptr = (TecInf*)realloc(pc->data, (pc->allnum + DEFAULT_ADD) * sizeof(TecInf));
		if (!ptr)
		{
			printf("DilationtTec::error:%s", strerror(errno));
			return;
		}
		else
		{
			pc->data = ptr;
			pc->allnum += DEFAULT_ADD;
		}
		//printf("DilationtTec:已扩容\n");
	}
}
void AddTec(Teacher* ps)
{
	assert(ps);
	DilationtTec(ps);
	printf("请输入姓名->");
	scanf("%s", ps->data[ps->count].name);
	printf("请输入性别->");
	scanf("%s", ps->data[ps->count].gender);
	printf("请输入工号->");
	scanf("%s", ps->data[ps->count].id);
	printf("请输入初始密码->");
	scanf("%s", ps->data[ps->count].passward);
	ps->count++;
	printf("**ROOT:添加成功**\n");
}
static int FindTecByname(Teacher* ps, char name[])
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
int FindTecByid(Teacher* ps, char id[20])
{
	int i;
	for (i = 0; i < ps->count; i++)
	{
		if (strcmp(ps->data[i].id, id) == 0)
		{
			return i;
		}
	}
	return -1;
}
void FindTec(Teacher* ps)
{
	if (ps->count == 0)
	{
		printf("没有教师,无法查找\n");
		return;
	}
	printf("请输入要查找的教师的姓名->");
	char name[20] = { 0 };
	scanf("%s", &name);
	int ret = FindTecByname(ps, name);
	if (ret == -1)
	{
		printf("**ROOT:没找到该教师**\n");
		return;
	}
	printf("该教师信息如下\n");
	printf("%10s%10s%10s\n", ps->data[ret].name, ps->data[ret].gender, ps->data[ret].id);
	return;
}

void ShowAllTec(Teacher* ps)
{
	int i;
	printf("%20s %20s %20s", "姓名", "性别", "工号\n");
	for (i = 0; i < ps->count; i++)
	{
		printf("%20s %20s %20s\n", ps->data[i].name, ps->data[i].gender, ps->data[i].id);
	}
}

void DelTec(Teacher* ps)
{
	if (ps->count == 0)
	{
		printf("没有教师,无法删除\n");
		return;
	}
	char d_name[20] = { 0 };
	ShowAllTec(ps);
	printf("请输入要删除的教师姓名->");
	scanf("%s", d_name);
	int ret = FindTecByname(ps, d_name), i;
	if (ret == -1)
	{
		printf("**没有找到该书**\n");
		return;
	}
	printf("请确认是否删除教师: %s (y/n)->", ps->data[ret].name);
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

void ModifyTec(Teacher* ps)
{
	if (ps->count == 0)
	{
		printf("没有教师,无法修改\n");
		return;
	}
	char m_name[20] = { 0 };
	printf("请输入要修改的教师姓名->");
	scanf("%s", m_name);
	int ret = FindTecByname(ps, m_name);
	if (ret == -1)
	{
		printf("**没有找到该教师**\n");
		return;
	}
	char new_name[20] = { 0 }, new_gender[10] = { 0 }, new_id[20] = { 0 }, new_passward[20] = {0};
	printf("请输入新姓名->");
	scanf("%s", new_name);
	printf("请输入新性别->");
	scanf("%s", new_gender);
	printf("请输入新工号->");
	scanf("%s", new_id);
	printf("请输入新密码");
	scanf("%s", new_passward);
	strcpy(ps->data[ret].name, new_name);
	strcpy(ps->data[ret].gender, new_gender);
	strcpy(ps->data[ret].id, new_id);
	strcpy(ps->data[ret].passward, new_passward);
	printf("ROOT:**修改完成**\n");
}

void SaveTecinfo(Teacher* ps)
{
	FILE* tecread = fopen("tecinfo.txt", "wb");
	int i;
	for (i = 0; i < ps->count; i++)
	{
		fwrite(ps->data + i, sizeof(TecInf), 1, tecread);
	}
	fclose(tecread);
	tecread = NULL;
}
void modifytecmm(Teacher* tec,int* num)
{
	printf("请输入初始密码->");
	char fpassward[20] = { 0 }, npassward[20] = { 0 };
	scanf("%s", &fpassward);
	if (strcmp(fpassward, tec->data[*num].passward) == 0)
	{
		printf("请输入新密码->");
		scanf("%s", &npassward);
		strcpy(tec->data[*num].passward, npassward);
	}
	else
		printf("初始密码输入错误\n");
	return;
}
int t_main_root(Teacher* tec)
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
			AddTec(tec);
			break;
		case DEL:
			DelTec(tec);
			break;
		case MODIFY:
			ModifyTec(tec);
			break;
		case FIND:
			FindTec(tec);
			break;
		case 5:
			ShowAllTec(tec);
			break;
		case EXIT:
			SaveTecinfo(tec);
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