#include"cup.h"
int main(void)
{
	Creat_file();
	denglu();

	return 0;
}
//������
void denglu()
{
	char ch_i;
	char err;
	struct denglu users;
	system("cls");
	printf("\t\t------------------------------------------------------------\n");
	printf("\t\t|                                                          |\n");
	printf("\t\t|                         ��¼����                         |\n");
	printf("\t\t|                         1.�û���¼                       |\n");
	printf("\t\t|                         2.�û�ע��                       |\n");
	printf("\t\t|                         0.�˳�                           |\n");
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
		//��һ�����users.name�ĺ��� ��������ɶ///////////////////////////////////////////////
		printf("\n�������û�����");
		err = shuru1(users.name);
		if (err != '\0')
		{
			printf("\n%c\n", err);
			goto flag_1;
		}
		err = '0';
		printf("\n���������룺");
		err = shuru2(users.password);
		if (err != '\0')
		{
			goto flag_1;
		}
		//����������Ա����ʱ��
		err = '0';
		err = i_comparison(users);
		//����ȶ�
		err = '0';
		err = comparison(users);
	}
	if (ch_i == '2')
	{
		registers();
	}
}
//��¼
char comparison(struct denglu x)
{
	FILE *fp;
	struct denglu pa;
	fp = fopen("denglu.txt", "r");
	fread(&pa, sizeof(struct denglu), 1, fp);  //��һ���������
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
				printf("\n���У�û�ҵ�������ˣ�\n");
				fclose(fp);
				system("pause");
				denglu();
			}
		}
	}
	fclose(fp);
	//�����Ѿ��ҵ��������
	if (strcmp(pa.password, x.password) == 0)
	{
		if (pa.i_condition == 0)
		{
			printf("\n���ѱ���š�");
			denglu();
		}
		else
		{
			printf("\n��¼�ɹ���");
			users_menu();
		}
	}
}
//�û�����¼�ȶ�
char i_comparison(struct denglu x)
{
	FILE *fp;
	struct denglu a;
	fp = fopen("import.txt", "r");
	fread(&a, sizeof(struct denglu), 1, fp);
	if (strcmp(a.name, x.name) == 0 && strcmp(a.password, x.password) == 0)
	{
		printf("\n����Ա��û�ӭ���룡");
		import_menu();
	}
	return 0;
}
//����Աʱ�䵽
char shuru1(char chs_p[17])
{
	int i_i = 0;
	char ch_p, chs_p1[17];
	while (1)//�ж��Ƿ��ǻس�
	{
		getch();		//Ϊɶ�и���Ҫ���ѽ��
		ch_p = getche();
		if (ch_p == '\r')
		{
			break;//����1
		}
		if (ch_p == 8 && i_i>0)
		{
			putchar(' ');
			putchar('\b');
			i_i--;
		}//ɾ����ʵ��backspace
		else if (!isdigit(ch_p) && !isalpha(ch_p))
		{
			getch();
			return 1;//����2
		}
		if (i_i > 15)
		{
			getch();
			return 2;//����3
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
//��ʾ����16λ_ok
char shuru2(char chs_p[17])
{
	int i_i = 0;
	char ch_p, chs_p1[17];
	while (1)//�ж��Ƿ��ǻس�
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
		}//ɾ����ʵ��backspace
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
//��������16λ_ok
void Creat_file()
{
	Create_team();
	Create_denglu();
	Create_import();
}
//�����ļ�_ok
void Create_denglu()
{
	errno_t err;
	FILE *fp;
	err = fopen_s(&fp, "denglu.txt", "r+");
	if (err != 0)//������ļ�������
	{
		err = fopen_s(&fp, "denglu.txt", "w+");
		if (err != 0)
		{
			printf("�޷������ļ���");
		}
	}
	fclose(fp);
}
//������¼�ļ�_ok
void Create_import()
{
	errno_t err;
	FILE *fp;
	struct denglu a;
	strcpy(a.name, "import");
	strcpy(a.password, "123456");
	err = fopen_s(&fp, "import.txt", "r+");
	if (err != 0)//������ļ�������
	{
		err = fopen_s(&fp, "import.txt", "w+");
		if (err != 0)
		{
			printf("�޷������ļ���");
		}
		fwrite(&a, sizeof(struct denglu), 1, fp);
	}
	fclose(fp);
}
//��������Ա�ļ�
void Create_team()
{
	errno_t err;
	FILE *fp;
	err = fopen_s(&fp, "team.txt", "r+");
	if (err != 0)//������ļ�������
	{
		err = fopen_s(&fp, "team.txt", "w+");
		if (err != 0)
		{
			printf("�޷������ļ���");
		}
	}
	fclose(fp);
}
//��������ļ�_ok
void registers()
{
	char x[17];
	char err, ch_i;
	struct denglu a, b;
	FILE *fp;
flag_2:
	memset(x, '0', sizeof(x));
	printf("\n�������û�����16λ����Ӣ�Ĵ�Сд����ĸ");
	err = shuru1(x);
	if (err != 0)
	{
		printf("\n�������,�˳����� ����� or �������� 1 ");
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
	//�����ļ��ȶԻ��ڣ�Ҳ�����û�������
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
				break;//û�����Ŀ��Լ������� fp�����ļ�β
			}
		}
		else
		{
			printf("\n���û����Ѿ�������");
			fclose(fp);
			getchar();
			getchar();
			printf("\n�� 1 �������룬���������˳�����");
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
	//���ʱ�� a.name����һ���µ��û����ˡ���ʼ���������������
flag_3:
	memset(x, '0', sizeof(x));
	printf("\n���������룺");
	err = shuru2(x);
	if (err != 0)
	{
		printf("\n�����������,�˳����� ����� or ������������ 1��");
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
	printf("\n��ȷ�����룺");
	err = shuru2(x);
	if (err != 0)
	{
		printf("\n����,�˳����� ����� or ������������ 1��");
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
		printf("\n�����������벻ͬ����1ѡ���������룬�������ѡ���˳����룡");
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
	//���ļ���
	fwrite(&a, sizeof(struct denglu), 1, fp);
	fclose(fp);
	printf("\nע��ɹ�������������ص�¼���棡");
	system("pause");
	denglu();
}
//�û�ע��
void import_menu()
{
	char ch_1;
	system("cls");
	printf("\t\t------------------------------------------------------------\n");
	printf("\t\t|                                                          |\n");
	printf("\t\t|                         ����Ա����                       |\n");
	printf("\t\t|                         1.�����Ϣ����                   |\n");
	printf("\t\t|                         2.�����Ϣ�޸�                   |\n");
	printf("\t\t|                         3.�����Ϣɾ��                   |\n");
	printf("\t\t|                         4.�����Ϣ��ѯ                   |\n");
	printf("\t\t|                         5.�����Ϣ����                   |\n");
	printf("\t\t|                         6.�������                     |\n");
	printf("\t\t|                         0.�޸�����                       |\n");
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
//����Ա�˵�
void users_menu()
{
	printf("users_menu");
	system("pause");
}
//�û��˵�
void input_all()
{
	FILE *fp;
	Node *pa, *pb;
	char err,ch_1;
	pa = (Node*)malloc(sizeof(Node));
	pb = (Node*)malloc(sizeof(Node));
flag_1:
	printf("\n������16λ��ӱ��룺");
	err = shuru2(pa->chs_number);
	if (err != 0||strlen(pa->chs_number)<16)
	{
		printf("\n������󣡰� 1 �������룬��������˳����룺");
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
	//��ӱ������
	fp = fopen("team.txt", "r+");
	fread(pb, sizeof(Node), 1, fp);
	while (1)
	{
		if (strcmp(pa->chs_number, pb->chs_number) == 0)
		{
			printf("\n�ظ��ˣ��� 1 �������룬�� ����� �˳����룺");
			ch_1 = getche();
			getch();

		}
	}

	system("pause");
}
//������� ��
void modify_all()
{
	printf("modify_all");
	system("pause");
}
//�޸������Ϣ ��
void del()
{
	printf("del");
	system("pause");
}
//ɾ�����
void find_all()
{
	printf("find_all");
	system("pause");
}
//���������Ϣ
void find(int i)
{
	printf("find");
	system("pause");
}
//���ң�Ŀ¼��
void table()
{
	printf("table");
	system("pause");
}
//����
linklist link_list(int *n)
{
	FILE *fp;		//�ļ�ָ��
	Node * p, *pnew;	//������
	linklist phead;	//ͷ����ָ��	
	Node temp;
	*n = 0;			//���������
	phead = (linklist)malloc(sizeof(Node));//��ͷָ��ռ�
	phead->next = NULL;//ָ���
	p = (Node *)malloc(sizeof(Node));//���������ռ�
	p = phead;//�ñ�������ͷ�ڵ㿪ʼ����
	fp = fopen("team.txt", "r");//���ļ�
	while (fread(&temp, sizeof(Node), 1, fp) != 0)//����feof();
	{
		pnew = (Node*)malloc(sizeof(Node));//���½��ռ�

		*pnew = temp;

		pnew->next = NULL;//�½���NEXTָ���
		p->next = pnew;//pָ��Pnew
		p = p->next;//p�����һ��
		*n += 1;//��һ���� ����ʹ��*n+=1,������*n++;(���ȼ�������)
	}
	fclose(fp);//�ر��ļ�
	return phead;//����ֵ��ͷָ��
}
//�������Ϣ���ļ�ȡ��������
void voice()
{
	printf("voice");
	system("pause");
}
//�������