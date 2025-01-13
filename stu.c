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
	printf("����ѧ����Ϣ...\n"); Sleep(300);
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
		//printf("DilationtStu:������\n");
	}
}
void AddStu(Student* ps)
{
	assert(ps);
	DilationtStu(ps);
	printf("����������->");
	scanf("%s", ps->data[ps->count].name);
	printf("�������Ա�->");
	scanf("%s", ps->data[ps->count].gender);
	printf("������ѧ��->");
	scanf("%s", ps->data[ps->count].id);
	ps->count++;
	printf("**ROOT:��ӳɹ�**\n");
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
		printf("û��ѧ��,�޷�����\n");
		return;
	}
	printf("������Ҫ���ҵ�ѧ��������->");
	char name[20] = { 0 };
	scanf("%s", &name);
	int ret = FindStuByname(ps,name);
	if (ret == -1)
	{
		printf("**ROOT:û�ҵ���ѧ��**\n");
		return;
	}
		printf("��ѧ����Ϣ����\n");
		printf("%10s%10s%10s\n", ps->data[ret].name, ps->data[ret].gender, ps->data[ret].id);
	return;
}
void ShowAllStu(Student* ps)
{
	int i;
	printf("%20s %20s %20s", "����", "�Ա�", "ѧ��\n");
	for (i = 0; i < ps->count; i++)
	{
		printf("%20s %20s %20s\n", ps->data[i].name, ps->data[i].gender, ps->data[i].id);
	}
}
void DelStu(Student* ps)
{
	if (ps->count == 0)
	{
		printf("û��ѧ��,�޷�ɾ��\n");
		return;
	}
	char d_name[20] = { 0 };
	ShowAllStu(ps);
	printf("������Ҫɾ����ѧ������->");
	scanf("%s", d_name);
	int ret = FindStuByname(ps, d_name), i;
	if (ret == -1)
	{
		printf("**û���ҵ���ѧ��**\n");
		return;
	}
	printf("��ȷ���Ƿ�ɾ��ѧ��: %s (y/n)->", ps->data[ret].name);
	char cho;
	scanf(" %c", &cho);										// ע����%cǰ��һ���ո����ں���ǰ��Ļ��з�
	if (cho == 'y' || cho == 'Y')
	{
		for (i = ret; i < ps->count - 1; i++)
		{
			ps->data[i] = ps->data[i + 1];					//�����������ǰ������ɾ��
		}
		ps->count--;
		printf("**ROOT:ɾ���ɹ�**\n");
	}
	else
		printf("**ROOT:ȡ������**\n");
}
void ModifyStu(Student* ps)
{
	if (ps->count == 0)
	{
		printf("û��ѧ��,�޷��޸�\n");
		return;
	}
	char m_name[20] = { 0 };
	printf("������Ҫ�޸ĵ�ѧ������->");
	scanf("%s", m_name);
	int ret = FindStuByname(ps, m_name);
	if (ret == -1)
	{
		printf("**û���ҵ���ѧ��**\n");
		return;
	}
	char new_name[20] = { 0 }, new_gender[10] = { 0 }, new_id[20] = {0};
	printf("������������->");
	scanf("%s", new_name);
	printf("���������Ա�->");
	scanf("%s", new_gender);
	printf("��������ѧ��->");
	scanf("%s", new_id);
	strcpy(ps->data[ret].name, new_name);
	strcpy(ps->data[ret].gender, new_gender);
	strcpy(ps->data[ret].id, new_id);
	printf("ROOT:**�޸����**\n");
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
		printf("��ѡ��-->");
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
			printf("ȷ���˳�ϵͳ?(y/n)-->");
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
			printf("**ROOT:��������ȷ�����**\n\n");
			break;
		}
	} while (cho);
	return 0;
}