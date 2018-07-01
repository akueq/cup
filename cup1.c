#include"cup.h"
int main(void)
{
	Creat_file();
	denglu();

	return 0;
}
//主函数
void denglu()
{
	char ch_i;
	char err;
	struct denglu users;
	system("cls");
	printf("\t\t------------------------------------------------------------\n");
	printf("\t\t|                                                          |\n");
	printf("\t\t|                         登录界面                         |\n");
	printf("\t\t|                         1.用户登录                       |\n");
	printf("\t\t|                         2.用户注册                       |\n");
	printf("\t\t|                         0.退出                           |\n");
	printf("\t\t|                                                          |\n");
	printf("\t\t------------------------------------------------------------\n");
	ch_i = getche();
	if (ch_i == '0')
	{
		exit(0);
	}
	if (ch_i == '1')
	{
	flag_1:
		err = '0';
		//放一个清空users.name的函数 我忘啦是啥///////////////////////////////////////////////
		printf("\n请输入用户名：");
		err = shuru1(users.name);
		if (err != '\0')
		{
			printf("\n%c\n", err);
			goto flag_1;
		}
		err = '0';
		printf("\n请输入密码：");
		err = shuru2(users.password);
		if (err != '\0')
		{
			goto flag_1;
		}
		//下面进入管理员特制时间
		err = '0';
		err = i_comparison(users);
		//下面比对
		err = '0';
		err = comparison(users);
	}
	if (ch_i == '2')
	{
		registers();
	}
}
//登录
char comparison(struct denglu x)
{
	FILE *fp;
	struct denglu pa;
	fp = fopen("denglu.txt", "r");
	fread(&pa, sizeof(struct denglu), 1, fp);  //读一个块出来先
	while (1)
	{
		if (strcmp(pa.name, x.name) == 0)
		{
			break;
		}
		else
		{
			if (!feof(fp))
			{
				fread(&pa, sizeof(struct denglu), 1, fp);
			}
			else
			{
				printf("\n不行，没找到你这个人！\n");
				fclose(fp);
				system("pause");
				denglu();
			}
		}
	}
	fclose(fp);
	//现在已经找到这个人了
	if (strcmp(pa.password, x.password) == 0)
	{
		if (pa.i_condition == 0)
		{
			printf("\n你已被封号。");
			denglu();
		}
		else
		{
			printf("\n登录成功。");
			users_menu();
		}
	}
}
//用户名登录比对
char i_comparison(struct denglu x)
{
	FILE *fp;
	struct denglu a;
	fp = fopen("import.txt", "r");
	fread(&a, sizeof(struct denglu), 1, fp);
	if (strcmp(a.name, x.name) == 0 && strcmp(a.password, x.password) == 0)
	{
		printf("\n管理员你好欢迎进入！");
		import_menu();
	}
	return 0;
}
//管理员时间到
char shuru1(char chs_p[17])
{
	int i_i = 0;
	char ch_p, chs_p1[17];
	while (1)//判断是否是回车
	{
		getch();		//为啥有个需要清的呀！
		ch_p = getche();
		if (ch_p == '\r')
		{
			break;//出口1
		}
		if (ch_p == 8 && i_i>0)
		{
			putchar(' ');
			putchar('\b');
			i_i--;
		}//删除键实现backspace
		else if (!isdigit(ch_p) && !isalpha(ch_p))
		{
			getch();
			return 1;//出口2
		}
		if (i_i > 15)
		{
			getch();
			return 2;//出口3
		}
		chs_p1[i_i++] = ch_p;
	}
	chs_p1[i_i] = 0;
	if (i_i > 16)
	{
		getch();
		return 3;
	}
	getch();
	strcpy(chs_p, chs_p1);
	return 0;
}
//显示输入16位_ok
char shuru2(char chs_p[17])
{
	int i_i = 0;
	char ch_p, chs_p1[17];
	while (1)//判断是否是回车
	{
		ch_p = getch();
		getch();
		if (ch_p == '\r')
		{
			break;
		}
		if (ch_p == 8 && i_i>0)
		{
			putchar('\b');
			putchar(' ');
			putchar('\b');
			i_i--;
			continue;
		}//删除键实现backspace
		else if (!isdigit(ch_p) && !isalpha(ch_p))
		{
			return 1;
		}
		if (i_i > 15)
		{
			return 2;
		}
		putchar('*');
		chs_p1[i_i++] = ch_p;
	}
	chs_p1[i_i] = 0;
	if (i_i > 16)
	{
		return 3;
	}
	strcpy(chs_p, chs_p1);
	return 0;
}
//密文输入16位_ok
void Creat_file()
{
	Create_team();
	Create_denglu();
	Create_import();
}
//创建文件_ok
void Create_denglu()
{
	errno_t err;
	FILE *fp;
	err = fopen_s(&fp, "denglu.txt", "r+");
	if (err != 0)//如果此文件不存在
	{
		err = fopen_s(&fp, "denglu.txt", "w+");
		if (err != 0)
		{
			printf("无法建立文件！");
		}
	}
	fclose(fp);
}
//创建登录文件_ok
void Create_import()
{
	errno_t err;
	FILE *fp;
	struct denglu a;
	strcpy(a.name, "import");
	strcpy(a.password, "123456");
	err = fopen_s(&fp, "import.txt", "r+");
	if (err != 0)//如果此文件不存在
	{
		err = fopen_s(&fp, "import.txt", "w+");
		if (err != 0)
		{
			printf("无法建立文件！");
		}
		fwrite(&a, sizeof(struct denglu), 1, fp);
	}
	fclose(fp);
}
//创建管理员文件
void Create_team()
{
	errno_t err;
	FILE *fp;
	err = fopen_s(&fp, "team.txt", "r+");
	if (err != 0)//如果此文件不存在
	{
		err = fopen_s(&fp, "team.txt", "w+");
		if (err != 0)
		{
			printf("无法建立文件！");
		}
	}
	fclose(fp);
}
//创建球队文件_ok
void registers()
{
	char x[17];
	char err, ch_i;
	struct denglu a, b;
	FILE *fp;
flag_2:
	memset(x, '0', sizeof(x));
	printf("\n请输入用户名，16位以内英文大小写及字母");
	err = shuru1(x);
	if (err != 0)
	{
		printf("\n输入错了,退出输入 任意键 or 重新输入 1 ");
		ch_i = getche();
		printf("%c", ch_i);
		system("pause");
		if (ch_i == '1')
		{
			goto flag_2;
		}
		else
		{
			denglu();
		}
	}
	strcpy(a.name, x);
	//进入文件比对环节，也就是用户名查重
	fp = fopen("denglu.txt", "r+");
	fread(&b, sizeof(struct denglu), 1, fp);
	while (1)
	{
		if (strcmp(a.name, b.name) != 0)
		{
			if (!feof(fp))
			{
				fread(&b, sizeof(struct denglu), 1, fp);
			}
			else
			{
				break;//没重名的可以继续用了 fp就在文件尾
			}
		}
		else
		{
			printf("\n该用户名已经存在了");
			fclose(fp);
			getchar();
			getchar();
			printf("\n按 1 重新输入，按其他键退出输入");
			ch_i = getche();
			if (ch_i == '1')
			{
				goto flag_2;
			}
			else
			{
				denglu();
			}
		}
	}
	//这个时候 a.name就是一个新的用户名了。开始输入密码这个事情
flag_3:
	memset(x, '0', sizeof(x));
	printf("\n请输入密码：");
	err = shuru2(x);
	if (err != 0)
	{
		printf("\n密码输入错了,退出输入 任意键 or 重新输入密码 1：");
		ch_i = getche();
		if (ch_i == '1')
		{
			goto flag_3;
		}
		else
		{
			denglu();
		}
	}
	else 
	{
		strcpy(a.password, x);
	}
	memset(x, '0', sizeof(x));
	printf("\n请确认密码：");
	err = shuru2(x);
	if (err != 0)
	{
		printf("\n错了,退出输入 任意键 or 重新输入密码 1：");
		ch_i = getche();
		if (ch_i == '1')
		{
			memset(a.password, '0', sizeof(a.password));
			goto flag_3;
		}
		else
		{
			denglu();
		}
	}
	if (strcmp(a.password, x) != 0)
	{
		printf("\n两次密码输入不同，按1选择重新输入，按任意键选择退出输入！");
		ch_i = getche();
		if (ch_i == '1')
		{
			memset(a.password, '0', sizeof(a.password));
			goto flag_3;
		}
		else
		{
			denglu();
		}
	}
	a.i_condition = 1;
	//到文件啦
	fwrite(&a, sizeof(struct denglu), 1, fp);
	fclose(fp);
	printf("\n注册成功！按任意键返回登录界面！");
	system("pause");
	denglu();
}
//用户注册
void import_menu()
{
	char ch_1;
	system("cls");
	printf("\t\t------------------------------------------------------------\n");
	printf("\t\t|                                                          |\n");
	printf("\t\t|                         管理员界面                       |\n");
	printf("\t\t|                         1.球队信息输入                   |\n");
	printf("\t\t|                         2.球队信息修改                   |\n");
	printf("\t\t|                         3.球队信息删除                   |\n");
	printf("\t\t|                         4.球队信息查询                   |\n");
	printf("\t\t|                         5.球队信息报表                   |\n");
	printf("\t\t|                         6.封号与解禁                     |\n");
	printf("\t\t|                         0.修改密码                       |\n");
	printf("\t\t|                                                          |\n");
	printf("\t\t------------------------------------------------------------\n");
	ch_1 = getche();
	switch (ch_1)
	{
	case '1': input_all(); break;
	case '2': modify_all(); break;
	case '3': del(); break;
	case '4': find_all(); break;
	case '5': table(); break;
	case '6': voice(); break;
	}
	system("pause");
}
//管理员菜单
void users_menu()
{
	printf("users_menu");
	system("pause");
}
//用户菜单
void input_all()
{
	FILE *fp;
	Node *pa, *pb;
	char err,ch_1;
	pa = (Node*)malloc(sizeof(Node));
	pb = (Node*)malloc(sizeof(Node));
flag_1:
	printf("\n请输入16位球队编码：");
	err = shuru2(pa->chs_number);
	if (err != 0||strlen(pa->chs_number)<16)
	{
		printf("\n输入错误！按 1 重新输入，按任意键退出输入：");
		ch_1 = getche();
		getch();
		if (ch_1 == '1')
		{
			goto flag_1;
		}
		else
		{
			import_menu();
		}
	}
	//球队编码查重
	fp = fopen("team.txt", "r+");
	fread(pb, sizeof(Node), 1, fp);
	while (1)
	{
		if (strcmp(pa->chs_number, pb->chs_number) == 0)
		{
			printf("\n重复了，按 1 重新输入，按 任意键 退出输入：");
			ch_1 = getche();
			getch();

		}
	}

	system("pause");
}
//增加球队 总
void modify_all()
{
	printf("modify_all");
	system("pause");
}
//修改球队信息 总
void del()
{
	printf("del");
	system("pause");
}
//删除球队
void find_all()
{
	printf("find_all");
	system("pause");
}
//查找球队信息
void find(int i)
{
	printf("find");
	system("pause");
}
//查找（目录）
void table()
{
	printf("table");
	system("pause");
}
//报表
linklist link_list(int *n)
{
	FILE *fp;		//文件指针
	Node * p, *pnew;	//链表结点
	linklist phead;	//头结点的指针	
	Node temp;
	*n = 0;			//存链表个数
	phead = (linklist)malloc(sizeof(Node));//给头指针空间
	phead->next = NULL;//指向空
	p = (Node *)malloc(sizeof(Node));//给遍历结点空间
	p = phead;//让遍历结点从头节点开始遍历
	fp = fopen("team.txt", "r");//打开文件
	while (fread(&temp, sizeof(Node), 1, fp) != 0)//不用feof();
	{
		pnew = (Node*)malloc(sizeof(Node));//给新结点空间

		*pnew = temp;

		pnew->next = NULL;//新结点的NEXT指向空
		p->next = pnew;//p指向Pnew
		p = p->next;//p向后走一个
		*n += 1;//这一句是 必须使用*n+=1,不能用*n++;(优先级的问题)
	}
	fclose(fp);//关闭文件
	return phead;//返回值是头指针
}
//把球队信息从文件取出到链表
void voice()
{
	printf("voice");
	system("pause");
}
//封号与解禁