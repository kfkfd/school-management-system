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
	printf("���ؽ�ʦ��Ϣ...\n"); Sleep(500);
	FILE* tecread = fopen("tecinfo.txt", "rb");
	if (tecread == NULL)
	{
		perror("LoadTecinf");
		return;
	}
	TecInf tmp = { 0 };
	while (fread(&tmp, sizeof(TecInf), 1, tecread)) //fread���سɹ���ȡ��Ԫ������
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
		//printf("DilationtTec:������\n");
	}
}
void AddTec(Teacher* ps)
{
	assert(ps);
	DilationtTec(ps);
	printf("����������->");
	scanf("%s", ps->data[ps->count].name);
	printf("�������Ա�->");
	scanf("%s", ps->data[ps->count].gender);
	printf("�����빤��->");
	scanf("%s", ps->data[ps->count].id);
	printf("�������ʼ����->");
	scanf("%s", ps->data[ps->count].passward);
	ps->count++;
	printf("**ROOT:��ӳɹ�**\n");
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
		printf("û�н�ʦ,�޷�����\n");
		return;
	}
	printf("������Ҫ���ҵĽ�ʦ������->");
	char name[20] = { 0 };
	scanf("%s", &name);
	int ret = FindTecByname(ps, name);
	if (ret == -1)
	{
		printf("**ROOT:û�ҵ��ý�ʦ**\n");
		return;
	}
	printf("�ý�ʦ��Ϣ����\n");
	printf("%10s%10s%10s\n", ps->data[ret].name, ps->data[ret].gender, ps->data[ret].id);
	return;
}

void ShowAllTec(Teacher* ps)
{
	int i;
	printf("%20s %20s %20s", "����", "�Ա�", "����\n");
	for (i = 0; i < ps->count; i++)
	{
		printf("%20s %20s %20s\n", ps->data[i].name, ps->data[i].gender, ps->data[i].id);
	}
}

void DelTec(Teacher* ps)
{
	if (ps->count == 0)
	{
		printf("û�н�ʦ,�޷�ɾ��\n");
		return;
	}
	char d_name[20] = { 0 };
	ShowAllTec(ps);
	printf("������Ҫɾ���Ľ�ʦ����->");
	scanf("%s", d_name);
	int ret = FindTecByname(ps, d_name), i;
	if (ret == -1)
	{
		printf("**û���ҵ�����**\n");
		return;
	}
	printf("��ȷ���Ƿ�ɾ����ʦ: %s (y/n)->", ps->data[ret].name);
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

void ModifyTec(Teacher* ps)
{
	if (ps->count == 0)
	{
		printf("û�н�ʦ,�޷��޸�\n");
		return;
	}
	char m_name[20] = { 0 };
	printf("������Ҫ�޸ĵĽ�ʦ����->");
	scanf("%s", m_name);
	int ret = FindTecByname(ps, m_name);
	if (ret == -1)
	{
		printf("**û���ҵ��ý�ʦ**\n");
		return;
	}
	char new_name[20] = { 0 }, new_gender[10] = { 0 }, new_id[20] = { 0 }, new_passward[20] = {0};
	printf("������������->");
	scanf("%s", new_name);
	printf("���������Ա�->");
	scanf("%s", new_gender);
	printf("�������¹���->");
	scanf("%s", new_id);
	printf("������������");
	scanf("%s", new_passward);
	strcpy(ps->data[ret].name, new_name);
	strcpy(ps->data[ret].gender, new_gender);
	strcpy(ps->data[ret].id, new_id);
	strcpy(ps->data[ret].passward, new_passward);
	printf("ROOT:**�޸����**\n");
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
	printf("�������ʼ����->");
	char fpassward[20] = { 0 }, npassward[20] = { 0 };
	scanf("%s", &fpassward);
	if (strcmp(fpassward, tec->data[*num].passward) == 0)
	{
		printf("������������->");
		scanf("%s", &npassward);
		strcpy(tec->data[*num].passward, npassward);
	}
	else
		printf("��ʼ�����������\n");
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
		printf("��ѡ��-->");
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