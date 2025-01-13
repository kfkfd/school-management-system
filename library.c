#define _CRT_SECURE_NO_WARNINGS

#include "stulibsystem.h"

//�˵�
void menu()
{
	printf("+----------------------------------------------+\n");
	printf("|*******1.���ͼ��            2.ɾ��ͼ��*******��\n");
	printf("|******3.ͼ����Ϣ�޸�      4.ͼ����Ϣ��ѯ******��\n");
	printf("|*******5.չʾȫ��ͼ��      6.�軹���¼*******��\n");
	printf("|***************** 0.�˳�ϵͳ  ****************��\n");
	printf("+----------------------------------------------+\n");
}

void LoadBookinf(Library* pc)
{
	printf("����ͼ���ļ�...\n"); Sleep(300);
	FILE* bookread = fopen("bookinfo.txt", "rb");
	if (bookread == NULL)
	{
		perror("LoadBookinf");
		return;
	}
	BookInf tmp = { 0 };
	while (fread(&tmp, sizeof(BookInf), 1, bookread))
	{
		DilationBok(pc);
		pc->data[pc->count] = tmp;
		pc->count++;
	}
	printf("->OK\n");
	Sleep(300);
}
//��ʼ���ڴ�
int InitLibrary(Library* pc)
{
	assert(pc);//���Է�ֹ��NULL
	pc->count = 0;
	pc->data = (BookInf*)calloc(DEFAULT_NUM, sizeof(BookInf));
	if (pc->data == NULL)
	{
		printf("InitLibrary::error:%s", strerror(errno));//����������Ϣ
		return 1;
	}
	pc->allnum = DEFAULT_NUM;
	LoadBookinf(pc); //�����ļ���Ϣ
	return 0;
}

/**��̬�ڴ����**/
void DilationBok(Library* pc)//����
{
	if (pc->count == pc->allnum)
	{
		BookInf* ptr = (BookInf*)realloc(pc->data, (pc->allnum + DEFAULT_ADD) * sizeof(BookInf));
		if (ptr == NULL)
		{
			printf("AddBook::error:%s", strerror(errno)); //����ʧ�ܱ���
			return;
		}
		else
		{
			pc->data = ptr;
			pc->allnum += DEFAULT_ADD;
		}
		//printf("**������**\n");
	}
}

void AddBook(Library* pc)
{
	assert(pc);
	DilationBok(pc);
	printf("����������->");
	scanf("%s", pc->data[pc->count].name);
	printf("����������->");
	scanf("%s", pc->data[pc->count].author);
	printf("������ͼ����->");
	scanf("%s", pc->data[pc->count].bokid);
	printf("������ͼ��λ��->");
	scanf("%s", pc->data[pc->count].bokwher);
	//����Ƿ�С����
examine:
	printf("������ͼ�����->");
	scanf("%d", &(pc->data[pc->count].boknum)); //int����Ҫȡ��ַ!!!
	if (pc->data[pc->count].boknum < 0)
	{
		printf("**�����ͼ��������Ϸ�**\n");
		goto examine;
	}
	pc->count++;
	printf("**��ӳɹ�**\n");
}

static int FindByname(const Library* pc, char name[])
{
	assert(pc);
	int i;
	for (i = 0; i < pc->count; i++)
	{
		if (strcmp(pc->data[i].name, name) == 0)
			return i; //�ҵ��˷����±�
	}
	return -1;    //û�ҵ�����-1
}
void ShowAllBook(Library* pc)
{
	printf("AllBookInfo:\n");
	int i;
	printf("%20s%15s%15s%15s%10s\n", "����", "����", "ͼ����", "ͼ��λ��", "ͼ�����");
	for (i = 0; i < pc->count; i++)
		printf("%20s%15s%15s%15s%10d\n\n", pc->data[i].name,
			pc->data[i].author, pc->data[i].bokid, pc->data[i].bokwher, pc->data[i].boknum);
}
void DelBook(Library* pc)
{
	if (pc->count == 0)
	{
		printf("û��ͼ��,�޷�ɾ��\n");
		return;
	}
	char d_name[20] = { 0 };
	ShowAllBook(pc);
	printf("������Ҫɾ��������->");
	scanf("%s", d_name);
	int ret = FindByname(pc, d_name), i;
	if (ret == -1)
	{
		printf("**û���ҵ�����**\n");
		return;
	}
	printf("��ȷ���Ƿ�ɾ����%s��(y/n)->\n", pc->data[ret].name);
	char cho;
	scanf(" %c", &cho);										// ע����%cǰ��һ���ո����ں���ǰ��Ļ��з�
	if (cho == 'y' || cho == 'Y')
	{
		for (i = ret; i < pc->count - 1; i++)
			pc->data[i] = pc->data[i + 1];					//�����������ǰ������ɾ��
		pc->count--;
		printf("**ɾ���ɹ�**\n");
	}
	else
		printf("**�û�ȡ������**\n");
}
//ģ��ƥ���ַ���
int BF(char s[20], char t[20])
{
	int i = 0, j = 0;
	if (strstr(s, t) != NULL) return 0;
	else return -1;
}
//�Ƽ�
void RecommendBook(Library* pc, char ch[20])
{
	printf("\n  **��������**\n");
	assert(pc);
	int i, ret, sum = 0;
	for (i = 0; i < pc->count; i++)
	{
		ret = BF(pc->data[i].name, ch);
		if (ret == 0)
			printf("��%s��\n", pc->data[i].name);
		sum += ret;
	}
	if (sum == -pc->count) printf("��\n"); printf("\n");
}

void FindBook(Library* pc)
{
	if (pc->count == 0)
	{
		printf("û��ͼ��,�޷�����\n");
		return;
	}
	char f_name[20] = { 0 };
	printf("������Ҫ���ҵ�����->");
	scanf("%s", f_name);
	int ret = FindByname(pc, f_name);
	if (ret == -1)
	{
		printf("**û���ҵ�����**\n");
		RecommendBook(pc, f_name);   //�Ƽ�
		return;
	}
	printf("������ϢΪ:\n");
	printf("%20s%20s%13s%13s%10s\n", "����", "����", "ͼ����", "ͼ��λ��", "ͼ�����");
	printf("%20s%20s%13s%13s%10d\n\n", pc->data[ret].name, pc->data[ret].author, pc->data[ret].bokid,
		pc->data[ret].bokwher, pc->data[ret].boknum);
}

void ModifyBook(Library* pc)
{
	if (pc->count == 0)
	{
		printf("û��ͼ��,�޷��޸�\n");
		return;
	}
	char m_name[20] = { 0 };
	printf("������Ҫ���ҵ�����->");
	scanf("%s", m_name);
	int ret = FindByname(pc, m_name);
	if (ret == -1)
	{
		printf("**û���ҵ�����**\n");
		return;
	}
	char new_auther[20] = { 0 }, new_bokid[10] = { 0 }, new_bokwher[20] = {0}; int new_boknum;
	printf("�������ͼ���µ�����->");
	scanf("%s", new_auther);
	printf("�������ͼ���µı��->");
	scanf("%s", new_bokid);
	printf("�������ͼ���µ�λ��->");
	scanf("%s", new_bokwher);
examine:
	printf("�������ͼ���µĲ���->");
	scanf("%d", &(new_boknum));
	if (new_boknum < 0)
	{
		printf("**�����ͼ��������Ϸ�**\n");
		goto examine;
	}
	strcpy(pc->data[ret].author, new_auther);
	strcpy(pc->data[ret].bokid, new_bokid);
	strcpy(pc->data[ret].bokwher, new_bokwher);
	pc->data[ret].boknum = new_boknum;
	printf("**�޸����**\n");
}

char* GetTime()
{
	time_t now = time(NULL);				//��ȡ��ǰʱ���
	struct tm* local_time = localtime(&now);// ��ʱ���ת��Ϊ����ʱ��
	// ��ӡ��ǰʱ��
	static char time[20] = { 0 };
	strftime(time, sizeof(time), "%Y-%m-%d %H:%M:%S", local_time);
	return time;
	//printf("%d-%02d-%02d %02d:%02d:%02d\n",
	//	local_time->tm_year + 1900,			// ��ݴ�1900��ʼ����
	//	local_time->tm_mon + 1,				// �·ݴ�0��ʼ����
	//	local_time->tm_mday,				// һ�����еĵڼ���
	//	local_time->tm_hour,				// Сʱ
	//	local_time->tm_min,				 // ����
	//	local_time->tm_sec				 // ��
	//);
}

void BorBook(Student*stu,Library* pc,Rb* rb,int* num)
{
	DilationRb(rb);
	if (pc->count == 0)
	{
		printf("û��ͼ��,�޷�����\n");
		return;
	}
	char b_name[20] = { 0 };
	printf("������Ҫ�������->");
	scanf("%s", b_name);
	int ret = FindByname(pc, b_name);
	if (ret == -1)
	{
		printf("**û���ҵ�����**\n");
		RecommendBook(pc, b_name);
		return;
	}
	if (pc->data[ret].boknum == 0)//boknumΪ0ʱ���ܽ�
	{
		printf("**�����ѱ�����**\n");
		return;
	}
	char* time = GetTime();
	pc->data[ret].boknum -= 1;
	strcpy(rb->data[rb->count].sname, stu->data[*num].name);
	strcpy(rb->data[rb->count].sid, stu->data[*num].id);
	strcpy(rb->data[rb->count].bname, pc->data[ret].name);
	strcpy(rb->data[rb->count].bid, pc->data[ret].bokid);
	strcpy(rb->data[rb->count].btime, time);
	strcpy(rb->data[rb->count].rtime, "\\");
	strcpy(rb->data[rb->count].state, "δ��");
	rb->count++;
	printf("����ʱ��Ϊ:%s\n",time);
}


//return book
void RetBook(Student* stu, Library* pc, Rb* rb, int* num)
{
	if (pc->count == 0)
	{
		printf("û��ͼ��,�޷�����\n");
		return;
	}
	int i,bor_num = 0;
	for (i = 0; i < rb->count; i++)
	{
		if ((strcmp(stu->data[*num].name, rb->data[i].sname) == 0) && (strcmp(rb->data[i].state, "δ��") == 0))
		{
			bor_num++;
			printf("%20s%15s\t%20s\n", rb->data[i].bname, rb->data[i].bid, rb->data[i].btime);
		}
	}
	if (bor_num == 0)
	{
		printf("û���ҵ� %s �Ľ����¼���޷�����\n",stu->data[(*num)].name);
		return;
	}
	printf("��ǰ��%d����δ��\n", bor_num);
	char r_name[20] = { 0 };
	printf("������Ҫ��������->");
	scanf("%s", r_name);
	//int ret = FindByname(pc, r_name);
	//if (ret == -1)
	//{
	//	printf("**û���ҵ�����**\n");
	//	return;
	//}
	char* time = GetTime();
	for (i = 0; i < rb->count; i++)
	{
		if ((strcmp(rb->data[i].bname, r_name) == 0) && (strcmp(rb->data[i].state, "δ��") == 0)&&
			(strcmp(stu->data[*num].name,rb->data[i].sname) == 0))
		{
			strcpy(rb->data[i].rtime, time);
			strcpy(rb->data[i].state, "�ѻ�");
			int ret = FindByname(pc, r_name);
			pc->data[ret].boknum += 1;
			printf("����ʱ��Ϊ:%s\n",time);
			return;
		}
	}
	printf("δ�ҵ������ļ�¼\n");
	return;
}
void SaveBokinfo(Library* pc)
{
	assert("pc");
	FILE* bookwrite = fopen("bookinfo.txt", "wb");
	int i;
	for (i = 0; i < pc->count; i++)
		fwrite(pc->data + i, sizeof(BookInf), 1, bookwrite);
	fclose(bookwrite);
	bookwrite = NULL;
}

int l_main(Library* lib,Rb*rb)
{
	int cho = 0;
	//Library lib;
	//InitLibrary(&lib); //��ʼ��
	do
	{
	CONTINUE:
		menu();
		printf("��ѡ��-->");
		scanf("%d", &cho);
		switch (cho)
		{
		case ADD:
			AddBook(lib); 
			break;
		case DEL:
			DelBook(lib); 
			break;
		case MODIFY:
			ModifyBook(lib); 
			break;
		case FIND:
			FindBook(lib); 
			break;
		case 5:
			ShowAllBook(lib); 
			break;
		case 6:
			ShowAllRbinfo(rb);
			break;
		//case BOR:
		//	BorBook(lib,); break;
		//case RET:
		//	RetBook(lib); break;
		case EXIT:
			SaveBokinfo(lib);
			printf("ȷ���˳�ϵͳ?(y/n)-->");
			char ch;
			scanf(" %c", &ch);
			if (ch == 'y' || ch == 'Y') {
				break;
			}
			else
				goto CONTINUE;
		default:
			printf("**��������ȷ�����**\n\n");
			break;
		}
	} while (cho);
	return 0;
}
