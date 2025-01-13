#include "stulibsystem.h"

void DilationRb(Rb* pc)
{
	if (pc->count == pc->allnum)
	{
		Rbinfo* ptr = (Rbinfo*)realloc(pc->data, (pc->allnum + 5) * sizeof(Rbinfo));
		if (ptr == NULL)
		{
			printf("AddBook::error:%s", strerror(errno)); //����ʧ�ܱ���
			return;
		}
		else
		{
			pc->data = ptr;
			pc->allnum += 5;
		}
		//printf("**DilationRb��������**\n");
	}
}

void LoadRbinfo(Rb* rb)
{
	printf("���ؽ軹���¼\n"); Sleep(1500);
	FILE* readrb = fopen("rbinfo.txt", "rb");
	if (readrb == NULL)
	{
		perror("LoadRbinfo");
		return;
	}
	Rbinfo tmp = { 0 };
	while (fread(&tmp, sizeof(Rbinfo), 1, readrb))
	{
		DilationRb(rb);
		rb->data[rb->count] = tmp;
		rb->count++;
	}
	printf("->OK\n");
}
int InitRbinfo(Rb* rb)
{
	rb->count = 0;
	rb->data = (Rbinfo*)calloc(DEFAULT_NUM, sizeof(Rbinfo));
	if (!rb->data)
	{
		printf("InitRbinfo::error:%s", strerror(errno));
		return -1;
	}
	rb->allnum = DEFAULT_NUM;
	LoadRbinfo(rb);
	return 0;
}
void SaveRbinfo(Rb* rb)
{
	FILE* writerb = fopen("rbinfo.txt", "wb");
	int i;
	for (i = 0; i < rb->count; i++)
	{
		fwrite(rb->data + i, sizeof(Rbinfo), 1, writerb);
	}
	fclose(writerb);
	writerb = NULL;
	return;
}


//show all return-borrow book information
void ShowAllRbinfo(Rb* rb)
{
	if (rb->count == 0)
	{
		printf("û�н軹����Ϣ\n");
		return;
	}
	int i;
	printf("%18s%18s%20s%10s%20s%20s%10s\n", "����", "ѧ��", "����", "���", "���ʱ��", "�黹ʱ��", "״̬");
	for (i = 0; i < rb->count; i++)
	{
		printf("%18s%18s%20s%10s%20s%20s%10s\n", rb->data[i].sname, rb->data[i].sid, rb->data[i].bname, rb->data[i].bid
			, rb->data[i].btime, rb->data[i].rtime, rb->data[i].state);
	}
}