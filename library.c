#define _CRT_SECURE_NO_WARNINGS

#include "stulibsystem.h"

//菜单
void menu()
{
	printf("+----------------------------------------------+\n");
	printf("|*******1.添加图书            2.删除图书*******│\n");
	printf("|******3.图书信息修改      4.图书信息查询******│\n");
	printf("|*******5.展示全部图书      6.借还书记录*******│\n");
	printf("|***************** 0.退出系统  ****************│\n");
	printf("+----------------------------------------------+\n");
}

void LoadBookinf(Library* pc)
{
	printf("加载图书文件...\n"); Sleep(300);
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
//初始化内存
int InitLibrary(Library* pc)
{
	assert(pc);//断言防止传NULL
	pc->count = 0;
	pc->data = (BookInf*)calloc(DEFAULT_NUM, sizeof(BookInf));
	if (pc->data == NULL)
	{
		printf("InitLibrary::error:%s", strerror(errno));//报出错误信息
		return 1;
	}
	pc->allnum = DEFAULT_NUM;
	LoadBookinf(pc); //加载文件信息
	return 0;
}

/**动态内存管理**/
void DilationBok(Library* pc)//扩容
{
	if (pc->count == pc->allnum)
	{
		BookInf* ptr = (BookInf*)realloc(pc->data, (pc->allnum + DEFAULT_ADD) * sizeof(BookInf));
		if (ptr == NULL)
		{
			printf("AddBook::error:%s", strerror(errno)); //开辟失败报错
			return;
		}
		else
		{
			pc->data = ptr;
			pc->allnum += DEFAULT_ADD;
		}
		//printf("**已扩容**\n");
	}
}

void AddBook(Library* pc)
{
	assert(pc);
	DilationBok(pc);
	printf("请输入书名->");
	scanf("%s", pc->data[pc->count].name);
	printf("请输入作者->");
	scanf("%s", pc->data[pc->count].author);
	printf("请输入图书编号->");
	scanf("%s", pc->data[pc->count].bokid);
	printf("请输入图书位置->");
	scanf("%s", pc->data[pc->count].bokwher);
	//检查是否小于零
examine:
	printf("请输入图书册数->");
	scanf("%d", &(pc->data[pc->count].boknum)); //int类型要取地址!!!
	if (pc->data[pc->count].boknum < 0)
	{
		printf("**输入的图书册数不合法**\n");
		goto examine;
	}
	pc->count++;
	printf("**添加成功**\n");
}

static int FindByname(const Library* pc, char name[])
{
	assert(pc);
	int i;
	for (i = 0; i < pc->count; i++)
	{
		if (strcmp(pc->data[i].name, name) == 0)
			return i; //找到了返回下标
	}
	return -1;    //没找到返回-1
}
void ShowAllBook(Library* pc)
{
	printf("AllBookInfo:\n");
	int i;
	printf("%20s%15s%15s%15s%10s\n", "书名", "作者", "图书编号", "图书位置", "图书册数");
	for (i = 0; i < pc->count; i++)
		printf("%20s%15s%15s%15s%10d\n\n", pc->data[i].name,
			pc->data[i].author, pc->data[i].bokid, pc->data[i].bokwher, pc->data[i].boknum);
}
void DelBook(Library* pc)
{
	if (pc->count == 0)
	{
		printf("没有图书,无法删除\n");
		return;
	}
	char d_name[20] = { 0 };
	ShowAllBook(pc);
	printf("请输入要删除的书名->");
	scanf("%s", d_name);
	int ret = FindByname(pc, d_name), i;
	if (ret == -1)
	{
		printf("**没有找到该书**\n");
		return;
	}
	printf("请确认是否删除《%s》(y/n)->\n", pc->data[ret].name);
	char cho;
	scanf(" %c", &cho);										// 注意在%c前有一个空格，用于忽略前面的换行符
	if (cho == 'y' || cho == 'Y')
	{
		for (i = ret; i < pc->count - 1; i++)
			pc->data[i] = pc->data[i + 1];					//后面的内容向前覆盖以删除
		pc->count--;
		printf("**删除成功**\n");
	}
	else
		printf("**用户取消操作**\n");
}
//模糊匹配字符串
int BF(char s[20], char t[20])
{
	int i = 0, j = 0;
	if (strstr(s, t) != NULL) return 0;
	else return -1;
}
//推荐
void RecommendBook(Library* pc, char ch[20])
{
	printf("\n  **猜你想搜**\n");
	assert(pc);
	int i, ret, sum = 0;
	for (i = 0; i < pc->count; i++)
	{
		ret = BF(pc->data[i].name, ch);
		if (ret == 0)
			printf("《%s》\n", pc->data[i].name);
		sum += ret;
	}
	if (sum == -pc->count) printf("无\n"); printf("\n");
}

void FindBook(Library* pc)
{
	if (pc->count == 0)
	{
		printf("没有图书,无法查找\n");
		return;
	}
	char f_name[20] = { 0 };
	printf("请输入要查找的书名->");
	scanf("%s", f_name);
	int ret = FindByname(pc, f_name);
	if (ret == -1)
	{
		printf("**没有找到该书**\n");
		RecommendBook(pc, f_name);   //推荐
		return;
	}
	printf("该书信息为:\n");
	printf("%20s%20s%13s%13s%10s\n", "书名", "作者", "图书编号", "图书位置", "图书册数");
	printf("%20s%20s%13s%13s%10d\n\n", pc->data[ret].name, pc->data[ret].author, pc->data[ret].bokid,
		pc->data[ret].bokwher, pc->data[ret].boknum);
}

void ModifyBook(Library* pc)
{
	if (pc->count == 0)
	{
		printf("没有图书,无法修改\n");
		return;
	}
	char m_name[20] = { 0 };
	printf("请输入要查找的书名->");
	scanf("%s", m_name);
	int ret = FindByname(pc, m_name);
	if (ret == -1)
	{
		printf("**没有找到该书**\n");
		return;
	}
	char new_auther[20] = { 0 }, new_bokid[10] = { 0 }, new_bokwher[20] = {0}; int new_boknum;
	printf("请输入该图书新的作者->");
	scanf("%s", new_auther);
	printf("请输入该图书新的编号->");
	scanf("%s", new_bokid);
	printf("请输入该图书新的位置->");
	scanf("%s", new_bokwher);
examine:
	printf("请输入该图书新的册数->");
	scanf("%d", &(new_boknum));
	if (new_boknum < 0)
	{
		printf("**输入的图书册数不合法**\n");
		goto examine;
	}
	strcpy(pc->data[ret].author, new_auther);
	strcpy(pc->data[ret].bokid, new_bokid);
	strcpy(pc->data[ret].bokwher, new_bokwher);
	pc->data[ret].boknum = new_boknum;
	printf("**修改完成**\n");
}

char* GetTime()
{
	time_t now = time(NULL);				//获取当前时间戳
	struct tm* local_time = localtime(&now);// 将时间戳转换为本地时间
	// 打印当前时间
	static char time[20] = { 0 };
	strftime(time, sizeof(time), "%Y-%m-%d %H:%M:%S", local_time);
	return time;
	//printf("%d-%02d-%02d %02d:%02d:%02d\n",
	//	local_time->tm_year + 1900,			// 年份从1900开始计数
	//	local_time->tm_mon + 1,				// 月份从0开始计数
	//	local_time->tm_mday,				// 一个月中的第几天
	//	local_time->tm_hour,				// 小时
	//	local_time->tm_min,				 // 分钟
	//	local_time->tm_sec				 // 秒
	//);
}

void BorBook(Student*stu,Library* pc,Rb* rb,int* num)
{
	DilationRb(rb);
	if (pc->count == 0)
	{
		printf("没有图书,无法借阅\n");
		return;
	}
	char b_name[20] = { 0 };
	printf("请输入要借的书名->");
	scanf("%s", b_name);
	int ret = FindByname(pc, b_name);
	if (ret == -1)
	{
		printf("**没有找到该书**\n");
		RecommendBook(pc, b_name);
		return;
	}
	if (pc->data[ret].boknum == 0)//boknum为0时不能借
	{
		printf("**该书已被借完**\n");
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
	strcpy(rb->data[rb->count].state, "未还");
	rb->count++;
	printf("借书时间为:%s\n",time);
}


//return book
void RetBook(Student* stu, Library* pc, Rb* rb, int* num)
{
	if (pc->count == 0)
	{
		printf("没有图书,无法还书\n");
		return;
	}
	int i,bor_num = 0;
	for (i = 0; i < rb->count; i++)
	{
		if ((strcmp(stu->data[*num].name, rb->data[i].sname) == 0) && (strcmp(rb->data[i].state, "未还") == 0))
		{
			bor_num++;
			printf("%20s%15s\t%20s\n", rb->data[i].bname, rb->data[i].bid, rb->data[i].btime);
		}
	}
	if (bor_num == 0)
	{
		printf("没有找到 %s 的借书记录，无法还书\n",stu->data[(*num)].name);
		return;
	}
	printf("当前有%d本书未还\n", bor_num);
	char r_name[20] = { 0 };
	printf("请输入要还的书名->");
	scanf("%s", r_name);
	//int ret = FindByname(pc, r_name);
	//if (ret == -1)
	//{
	//	printf("**没有找到该书**\n");
	//	return;
	//}
	char* time = GetTime();
	for (i = 0; i < rb->count; i++)
	{
		if ((strcmp(rb->data[i].bname, r_name) == 0) && (strcmp(rb->data[i].state, "未还") == 0)&&
			(strcmp(stu->data[*num].name,rb->data[i].sname) == 0))
		{
			strcpy(rb->data[i].rtime, time);
			strcpy(rb->data[i].state, "已还");
			int ret = FindByname(pc, r_name);
			pc->data[ret].boknum += 1;
			printf("还书时间为:%s\n",time);
			return;
		}
	}
	printf("未找到借该书的记录\n");
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
	//InitLibrary(&lib); //初始化
	do
	{
	CONTINUE:
		menu();
		printf("请选择-->");
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
			printf("确认退出系统?(y/n)-->");
			char ch;
			scanf(" %c", &ch);
			if (ch == 'y' || ch == 'Y') {
				break;
			}
			else
				goto CONTINUE;
		default:
			printf("**请输入正确的序号**\n\n");
			break;
		}
	} while (cho);
	return 0;
}
