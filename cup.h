#include<stdlib.h>
#include<malloc.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include<conio.h>
struct denglu {
	char name[17];
	char password[17];
	int i_condition;//��� 0������ 1�� 
};
//��¼��Ϣ
struct sport_boy {
	char chs_name[21];
	int i_position;			//�Ž� 0������ 1���г� 2��ǰ�� 3��
	char chs_national_team_number[3];
	int i_goal;
	int i_number;			//��ӱ��� 
};
//��Ա��Ϣ
typedef struct agenda1 {
	char xiaozu_1[41];
	char chs_bifen_xiaozu_1[11];
	char chs_date_xiaozu_1[12];
	char xiaozu_2[41];
	char chs_bifen_xiaozu_2[11];
	char chs_date_xiaozu_2[12];
	char xiaozu_3[41];
	char chs_bifen_xiaozu_3[11];
	char chs_date_xiaozu_3[12];
	char taotai_8[41];
	char chs_bifen_taotai_8[11];
	char chs_date_taotai_8[12];
	char taotai_4[41];
	char chs_bifen_taotai_4[11];
	char chs_date_taotai_4[12];
	char taotai_2[41];
	char chs_bifen_taotai_2[11];
	char chs_date_taotai_2[12];
	char juesai[41];
	char chs_bifen_juesai[11];
	char chs_date_juesai[12];
}Agenda;
//������Ϣ
typedef struct team {
	char chs_number;			//��ӱ���(�����) 
	int i_goal;
	char chs_national[41];
	struct sport_boy boys[23];
	char xiaozu;        //�Ǹ����
	Agenda agenda;
	int i_condition;	//��̭ 0 orС���� 1 or1/8 2 or1/4 3 or1/2 4 or���� 5
	struct team* next;
}Node, *linklist;
//�����Ϣ
void Creat_file();
void denglu();
void registers();
void Create_team();
void Create_denglu();
void Create_import();
char shuru1(char chs_p1[17]);
char shuru2(char chs_p1[17]);
char comparison(struct denglu x);
char i_comparison(struct denglu x);
void import_menu();
void users_menu();
void input_all();
void modify_all();
void del();
void find_all();
void find(int i);
linklist link_list(int *n);
void table();
void voice();