#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include<fcntl.h>
#include <setjmp.h>
#define ADUSER_NAME "admin"
#define ADPASSWORD "Admin"
#define STPASSWORD "000000"
//类型首字母大写以和变量区分
typedef struct Student
{
	char cName[50];
	char iNumber[50];
	int  Score;
	char lesson[50];
	struct Student* next;
}STU;
//因为类型相同所以递归定义
STU* phead = NULL;
STU* pEnd = NULL;
int icount;//全局定义链表长度
int judgeadmin = 1;
char Cl[20] = { 0 };
char STusername[50] = { 0 };
void SetPos(int x, int y);
void Login();
int Menu_select();
void Head();
void STHead();
STU* Creat();
void Print(STU* phead);
void ADDstu(char* iNumber, char* cName, int Score);
void sort(STU* pHead);
void Delete(STU* pHead, int index);
STU* delHead(STU* pHead);
STU* FreeAll_LINK(STU* pHead);
void Search_stu(STU* pHead);
void Revise_stu(STU* pHead);
void Caozuowei();
void backlogin_caozuowei();
void Shensucaozuowei();
void Chachong(STU* pHead);
void Savestu();
void Readstu();
void Backlogin();
void print_lessons();
int Stmenu_select();
char* choose_lesson();
void read_lesson();
void save_lesson();
int main()
{
	system("color f0");
	char cName[50];
	char iNumber[50];
	int  Score;
	char lesson[50] = { 0 };
	system("color f0");
	printf("欢迎使用本系统！\n");
	int i;
	printf("\n\n\n\n\n\n\n\n\t\t\t\t\t");
	char heihei[] = { "即将进入学生管理系统..." };
	for (i = 0; i < strlen(heihei); i++)
	{
		printf("%c", heihei[i]);
		Sleep(100);
	}
	system("CLS");
	Login();
	system("cls");
	int iN;
	Readstu();
	if (judgeadmin == 0)
	{
		system("cls");
		STHead();
		printf("\n\t\t\t\t\t*************学生端信息查询************\n");
		int p = 0;
		STU* pTemp = phead;
		while (pTemp != NULL)
		{
			if (strcmp(pTemp->iNumber, STusername) == 0)
			{
				p++;
				while (!judgeadmin)
				{
					iN = Stmenu_select();
					switch (iN)
					{
					case 0:
						system("cls");
						printf("\n\n\n\t ");
						for (int i = 0; i < 50; i++)
						{
							printf("* ");
							Sleep(50);
						}
						printf("\n\t\t\t   ");
						printf("要返回登录界面按任意键\t\t要退出程序请按Esc键\n");
						char cho;
						fflush(stdin);
						cho = getch();
						if (cho == 0x1b)
						{
							FreeAll_LINK(phead);
							exit(0);
						}

						else
						{
							fflush(stdin);
							Savestu();
							system("cls");
							Backlogin();
						}
						break;
					case 1:
						system("cls");
						print_lessons();
						break;
					case 2:
						system("cls");
						printf("\t\t\t\t学生信息如下：\n\t\t\t\t姓名： %s\n\t\t\t\t学号： %s\n\t\t\t\t成绩： %d\n\t\t\t\t课程： %s", pTemp->cName, pTemp->iNumber, pTemp->Score, pTemp->lesson);
						Caozuowei();
						break;
					case 3:
						system("cls");
						save_lesson(choose_lesson());
						strcpy(pTemp->lesson, choose_lesson());
						Caozuowei();
						break;
					}

				}
			}
			break;
		}
		pTemp = pTemp->next;


		if (p == 0)
		{
			printf("\n\n\n\t\t\t\t\t\t管理员还没有添加你的信息哦。");
		}
		free(phead);
		backlogin_caozuowei();
	}
	else
	{
		system("cls");
		Head();
		while (judgeadmin)
		{

			iN = Menu_select();
			switch (iN)
			{
			case 0:
				system("cls");
				printf("\n\n\n\t ");
				for (int i = 0; i < 50; i++)
				{
					printf("* ");
					Sleep(50);
				}
				printf("\n\t\t\t   ");
				printf("要返回登录界面按任意键\t\t要退出程序请按Esc键\n");
				char cho;
				fflush(stdin);
				cho = getch();
				if (cho == 0x1b)
				{
					FreeAll_LINK(phead);
					exit(0);
				}

				else
				{
					fflush(stdin);
					Savestu();
					system("cls");
					Backlogin();
				}

				break;
			case 1:
				//		               创建
				phead = Creat();
				Savestu();
				break;
			case 2:
				//	打印
				Print(phead);
				break;
			case 3:
				for (int in = 1; in <= 3; in++)
				{
					Sleep(200);
					printf(".");
				}
				system("CLS");
				Head();	printf("\n");							//追加
				printf("\t\t\t\t学号：\n\t\t\t\t");
				scanf("%s", iNumber);
				for (int i = 0;iNumber[i];i++)
				{
					if (48 > iNumber[i] || iNumber[i] > 57)
					{
						printf("\n\t●请重新输入学号:");
						fflush(stdin);
						scanf("%s", iNumber);
						i = -1;
					}
				}
				printf("\t\t\t\t姓名：\n\t\t\t\t");
				scanf("%s", cName);
				printf("\t\t\t\t成绩：\n\t\t\t\t");
				scanf("%d", &Score);
				while (Score > 100 || Score < 0)
				{
					printf("\n\t●请重新输入正确成绩:");
					fflush(stdin);
					scanf("%d", &Score);
				}
				ADDstu(iNumber, cName, Score);
				printf("\t\t\t\t");
				printf("\t\t\t\t\n");
				for (int in = 1; in <= 3; in++)
				{
					Sleep(200);
					printf(".");
				}
				printf("\n\t\t\t\t添加成功！");
				getch();
				Caozuowei();
				Savestu();
				break;
			case 4:

				for (int in = 1; in <= 3; in++)
				{
					Sleep(200);
					printf(".");
				}
				system("CLS");
				Head();	puts("");								//排序
				printf("\t\t\t\t\t*************数据排序************\n");
				sort(phead);
				getch();
				Caozuowei();
				fflush(stdin);
				Savestu();
				break;
			case 5:
				Revise_stu(phead);
				Savestu();
				break;
			case 6:
				for (int in = 1; in <= 3; in++)
				{
					Sleep(200);
					printf(".");
				}
				system("CLS");
				Head();	puts("");							//删除
				printf("\t\t\t\t\t*************删除学生信息************\n\t\t\t\t请选择删除方式。\n\t\t\t\t1)删除输入的序号对应的学生。\t2)删除全部学生\n\t\t\t\t");
				char ccho;
				ccho = getche();
				while (ccho != '1' && ccho != '2')
				{
					ccho = getch();
				}
				if (ccho == '1')
				{
					int index;//要删除的学生序号
					printf("\n\t\t\t\t请输入要删除的学生序号：\n\t\t\t\t");
					scanf("%d", &index);
					getchar();
					if (index != 1)
						Delete(phead, index);
					else
					{
						phead = delHead(phead);
					}
					Savestu();
				}
				if (ccho == '2')
				{
					phead = FreeAll_LINK(phead);
					for (int in = 1; in <= 3; in++)
					{
						Sleep(200);
						printf(".");
					}
					phead = NULL;
					printf("\n\t\t\t\t已清空！");
					Savestu();
				}
				getch();
				Caozuowei();
				break;
			case 7:
				Search_stu(phead);
				break;
			}
			system("CLS");

		}
	}
}
void Head()
{
	printf("\n");
	printf("\t\t\t\t\t╭ ⺌ % ╮                           ╭ ```╮  \n");
	printf("\t\t\t\t\t(@^o^@) 学生信息管理系统   管理端(⌒:⌒)\n");
	printf("\t\t\t\t\t(~):(~)                          (~)v(~) \n");
	printf("\n\n\n");
}
void STHead()
{
	printf("\n");
	printf("\t\t\t\t\t╭ ⺌ % ╮                           ╭ ```╮  \n");
	printf("\t\t\t\t\t(@^o^@) 学生信息管理系统   学生端(⌒:⌒)\n");
	printf("\t\t\t\t\t(~):(~)                          (~)v(~) \n");
	printf("\n\n\n");
}
void SetPos(int x, int y)				//光标调整
{
	COORD pos;
	HANDLE handle;
	pos.X = x;
	pos.Y = y;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, pos);

}
void Login()
{
	fflush(stdin); //清除或刷新输入缓冲区
	printf("\n");
	printf("\t\t\t\t\t╭ ⺌ % ╮                   ╭ ```╮  \n");
	printf("\t\t\t\t\t(@^o^@) 学生信息管理系统 (⌒:⌒)\n");
	printf("\t\t\t\t\t(~):(~)                  (~)v(~) \n");
	printf("\n\n\n");
	printf("\t\t\t\t\t   ┅┅┅       LOGIN      ┅┅┅       \n");
	printf("\n\n\n");
	char xing[] = { "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * " };
	for (int i = 0;i < strlen(xing);i++)
	{
		printf("%c", xing[i]);
		Sleep(10);
	}

	printf("\n\n\t\t\t\t\t\t请选择您的登录身份:\n\n\n\n\t\t\t\t\t\t\t1.管理员\n\n\n\n\t\t\t\t\t\t\t2.学生");
	char num;
	fflush(stdin);
	num = getch();
	while (1)
	{
		system("cls");
		if (num != '1' && num != '2')
		{
			printf("\n");
			printf("\t\t\t\t\t╭ ⺌ % ╮                   ╭ ```╮  \n");
			printf("\t\t\t\t\t(@^o^@) 学生信息管理系统 (⌒:⌒)\n");
			printf("\t\t\t\t\t(~):(~)                  (~)v(~) \n");
			printf("\n\n\n");
			printf("\t\t\t\t\t   ┅┅┅       LOGIN      ┅┅┅       \n");
			printf("\n\n\n");
			printf("%s", xing);
			printf("\n\n\t\t\t\t\t请重新选择您的登录身份:\n\n\n\n\t\t\t\t\t\t\t1.管理员\n\n\n\n\t\t\t\t\t\t\t2.学生");
			fflush(stdin);
			num = getch();

		}
		if (num == '1')
		{
			judgeadmin = 1;
			system("cls");
			printf("\n");
			printf("\t\t\t\t\t╭ ⺌ % ╮                           ╭ ```╮  \n");
			printf("\t\t\t\t\t(@^o^@) 学生信息管理系统   管理端(⌒:⌒)\n");
			printf("\t\t\t\t\t(~):(~)                          (~)v(~) \n");
			printf("\n\n\n");
			printf("\t\t\t\t\t       ┅┅┅       LOGIN      ┅┅┅       \n");
			printf("\n\n\n");
			char xing[] = { "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * " };
			for (int i = 0;i < strlen(xing);i++)
			{
				printf("%c", xing[i]);
				Sleep(10);
			}
			printf("\n\n\n\n\n\n\t\t\t\t您将以管理员身份登录，按回车键继续，按空格键返回上一页");
			char cho;
			cho = getch();
			if (cho == 0x0d)
			{
				system("cls");
				Head();
				printf("\t\t\t\t\t       ┅┅┅       LOGIN      ┅┅┅       \n");
				printf("\n\n\n");
				char xing[] = { "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * " };
				for (int i = 0;i < strlen(xing);i++)
				{
					printf("%c", xing[i]);
					Sleep(10);
				}
				char username[50] = { 0 };
				char password[50] = { 0 };
				printf("\n\n\n\t\t\t\t\t\t请输入用户名及密码\n\n");
				printf("\t\t\t\t\t用户名：");
				int x, y;
				SetPos(50, 15);
				printf("┏┈┈┈┈┈┈┈┈┈┈┈┈┈┓");
				SetPos(50, 16);
				printf("☆　　　　 　 ☆");
				SetPos(50, 17);
				printf("┗┈┈┈┈┈┈┈┈┈┈┈┈┈┛");
				SetPos(52, 16);
				scanf("%s", username);
				printf("\n\n");
				SetPos(30, 21);
				printf("\t\t密码： ");
				SetPos(50, 20);
				printf("┏┈┈┈┈┈┈┈┈┈┈┈┈┈┓");
				SetPos(50, 21);
				printf("☆　　　　　　☆");
				SetPos(50, 22);
				printf("┗┈┈┈┈┈┈┈┈┈┈┈┈┈┛");
				SetPos(52, 21);

				int i = 0, n = 5;
				char ch;
				while ((ch = getch()) != '\r')
				{
					fflush(stdin);
					if (ch == '\b')
					{
						if (i > 0)
						{
							i--;
							printf("\b \b");
							password[i] = 0;
							continue;
						}
						else
						{
							printf("\a");     //没有内容的时候
							continue;
						}
					}
					else
					{
						password[i] = ch;
						printf("*");
					}

					i++;
				}

				if (strcmp(username, ADUSER_NAME) == 0 && strcmp(password, ADPASSWORD) == 0)
				{
					system("cls");
					int x, y;
					x = 28;y = 17;
					SetPos(x, y);
					printf("○");
					Sleep(100);
					x += 6;
					SetPos(x, y);
					printf("●");
					Sleep(100);
					x += 6;
					SetPos(x, y);
					printf("○");
					Sleep(100);
					x += 6;
					SetPos(x, y);
					printf("●");
					Sleep(100);
					x += 6;
					SetPos(x, y);
					printf("○");
					Sleep(100);
					x += 6;
					SetPos(x, y);
					printf("●");
					Sleep(100);
					x += 6;
					SetPos(x, y);
					printf("○");
					Sleep(100);
					x += 6;
					SetPos(x, y);
					printf("●");
					Sleep(100);
					x += 6;
					SetPos(x, y);
					printf("○");
					printf("\n\n\t\t\t\t\t\t\t\t欢迎您，管理员！");
					system("pause");
					return;
				}
				else
				{
					SetPos(70, 21);
					system("cls");
					printf("\n\n\n");
					printf("\t\t\t\t\t   用户名或密码错误，您还有一次机会\n");
					//	system("pause");
					printf("\n\n\t\t\t\t\t       ┅┅┅       LOGIN      ┅┅┅       \n");
					printf("\n\n\n");
					for (int i = 0;i < strlen(xing);i++)
					{
						printf("%c", xing[i]);
						Sleep(10);
					}
					printf("\n\n\t\t\t\t要重新登录请按任意键\t\t要退出程序请按Esc键\n");
					char cho;
					cho = getch();
					if (cho == 0x1b)
						exit(0);
					system("cls");

					Head();
					printf("\t\t\t\t\t       ┅┅┅       LOGIN      ┅┅┅       \n");
					printf("\n\n\n");

					for (int i = 0;i < strlen(xing);i++)
					{
						printf("%c", xing[i]);
						Sleep(10);
					}
					char username[50] = { 0 };
					char password[50] = { 0 };
					printf("\n\n\n\t\t\t\t\t\t请输入用户名及密码\n\n");
					printf("\t\t\t\t\t用户名：");
					int x, y;
					SetPos(50, 15);
					printf("┏┈┈┈┈┈┈┈┈┈┈┈┈┈┓");
					SetPos(50, 16);
					printf("☆　　　　 　 ☆");
					SetPos(50, 17);
					printf("┗┈┈┈┈┈┈┈┈┈┈┈┈┈┛");
					SetPos(52, 16);
					scanf("%s", username);
					printf("\n\n");
					SetPos(30, 21);
					printf("\t\t密码： ");
					SetPos(50, 20);
					printf("┏┈┈┈┈┈┈┈┈┈┈┈┈┈┓");
					SetPos(50, 21);
					printf("☆　　　　　　☆");
					SetPos(50, 22);
					printf("┗┈┈┈┈┈┈┈┈┈┈┈┈┈┛");
					SetPos(52, 21);
					i = 0, n = 5;
					char ch;
					while ((ch = getch()) != '\r')
					{
						fflush(stdin);
						if (ch == '\b')
						{
							if (i > 0)
							{
								i--;
								printf("\b \b");
								password[i] = 0;
								continue;
							}
							else
							{
								printf("\a");     //没有内容的时候
								continue;
							}
						}
						else
						{
							password[i] = ch;
							printf("*");
						}

						i++;
					}
					if (strcmp(username, ADUSER_NAME) == 0 && strcmp(password, ADPASSWORD) == 0)
					{

						system("cls");
						int x, y;
						x = 28;y = 17;
						SetPos(x, y);
						printf("●");
						Sleep(100);
						x += 6;
						SetPos(x, y);
						printf("○");
						Sleep(100);
						x += 6;
						SetPos(x, y);
						printf("●");
						Sleep(100);
						x += 6;
						SetPos(x, y);
						printf("○");
						Sleep(100);
						x += 6;
						SetPos(x, y);
						printf("●");//
						Sleep(100);
						x += 6;
						SetPos(x, y);
						printf("○");
						Sleep(100);
						x += 6;
						SetPos(x, y);
						printf("●");
						Sleep(100);
						x += 6;
						SetPos(x, y);
						printf("○");
						Sleep(100);
						x += 6;
						SetPos(x, y);
						printf("●");
						printf("\n\n\t\t\t\t\t\t\t\t欢迎您，管理员！");
						system("pause");
						return;
					}
					else
					{
						for (i = 3; i != 0; i--)
						{
							system("cls");
							printf("\n\n登录异常，本系统将在%d秒后自动关闭...\n", i);
							Sleep(1000);
						}
						exit(0);
					}
				}
			}
		}
		//学生端
		if (num == '2')
		{
			system("cls");
			printf("\n");
			printf("\t\t\t\t\t╭ ⺌ % ╮                           ╭ ```╮  \n");
			printf("\t\t\t\t\t(@^o^@) 学生信息管理系统   学生端(⌒:⌒)\n");
			printf("\t\t\t\t\t(~):(~)                          (~)v(~) \n");
			printf("\n\n\n");
			printf("\t\t\t\t\t       ┅┅┅       LOGIN      ┅┅┅       \n");
			printf("\n\n\n");
			char xing[] = { "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * " };
			for (int i = 0;i < strlen(xing);i++)
			{
				printf("%c", xing[i]);
				Sleep(10);
			}
			printf("\n\n\n\n\n\n\t\t\t\t您将以学生的身份登录，按回车键继续，按空格键返回上一页");
			char cho;
			cho = getch();
			if (cho == 0x0d)
			{
				//学生端登录
				system("cls");
				STHead();
				printf("\t\t\t\t\t       ┅┅┅       LOGIN      ┅┅┅       \n");
				printf("\n\n\n");
				for (int i = 0;i < strlen(xing);i++)
				{
					printf("%c", xing[i]);
					Sleep(10);
				}
				char password[50] = { 0 };
				printf("\n\n\n\t\t\t\t\t\t请输入用户名及密码\n\n");
				printf("\t\t\t\t\t用户名：");
				int x, y;
				SetPos(50, 15);
				printf("┏┈┈┈┈┈┈┈┈┈┈┈┈┈┓");
				SetPos(50, 16);
				printf("☆　　　　 　 ☆");
				SetPos(50, 17);
				printf("┗┈┈┈┈┈┈┈┈┈┈┈┈┈┛");
				SetPos(52, 16);
				scanf("%s", STusername);
				printf("\n\n");
				SetPos(30, 21);
				printf("\t\t密码： ");
				SetPos(50, 20);
				printf("┏┈┈┈┈┈┈┈┈┈┈┈┈┈┓");
				SetPos(50, 21);
				printf("☆　　　　　　☆");
				SetPos(50, 22);
				printf("┗┈┈┈┈┈┈┈┈┈┈┈┈┈┛");
				SetPos(52, 21);

				int	i = 0, n = 5;
				char ch;
				while ((ch = getch()) != '\r')
				{
					fflush(stdin);
					if (ch == '\b')
					{
						if (i > 0)
						{
							i--;
							printf("\b \b");
							password[i] = 0;
							continue;
						}
						else
						{
							printf("\a");     //没有内容的时候
							continue;
						}
					}
					else
					{
						password[i] = ch;
						printf("*");
					}

					i++;
				}
				if (strcmp(password, STPASSWORD) == 0)
				{
					printf("\n\n登录中");
					for (int i = 0; i < 3; i++)
					{
						printf(".");
						Sleep(100);
					}
					judgeadmin = 0;
					return;
				}
				else
				{
					SetPos(70, 21);
					system("cls");
					printf("\n\n\n");
					printf("\t\t\t\t\t   用户名或密码错误，您还有一次机会\n");
					//	system("pause");
					printf("\n\n\t\t\t\t\t       ┅┅┅       LOGIN      ┅┅┅       \n");
					printf("\n\n\n");
					for (int i = 0;i < strlen(xing);i++)
					{
						printf("%c", xing[i]);
						Sleep(10);
					}
					printf("\n\n\t\t\t\t要重新登录请按任意键\t\t要退出程序请按Esc键\n");
					char cho;
					cho = getch();
					if (cho == 0x1b)
						exit(0);
					system("cls");

					STHead();
					printf("\t\t\t\t\t       ┅┅┅       LOGIN      ┅┅┅       \n");
					printf("\n\n\n");
					for (int i = 0;i < strlen(xing);i++)
					{
						printf("%c", xing[i]);
						Sleep(10);
					}
					char password[50] = { 0 };
					printf("\n\n\n\t\t\t\t\t\t请输入用户名及密码\n\n");
					printf("\t\t\t\t\t用户名：");
					int x, y;
					SetPos(50, 15);
					printf("┏┈┈┈┈┈┈┈┈┈┈┈┈┈┓");
					SetPos(50, 16);
					printf("☆　　　　 　 ☆");
					SetPos(50, 17);
					printf("┗┈┈┈┈┈┈┈┈┈┈┈┈┈┛");
					SetPos(52, 16);
					scanf("%s", STusername);
					printf("\n\n");
					SetPos(30, 21);
					printf("\t\t密码： ");
					SetPos(50, 20);
					printf("┏┈┈┈┈┈┈┈┈┈┈┈┈┈┓");
					SetPos(50, 21);
					printf("☆　　　　　　☆");
					SetPos(50, 22);
					printf("┗┈┈┈┈┈┈┈┈┈┈┈┈┈┛");
					SetPos(52, 21);
					i = 0, n = 5;
					char ch;
					while ((ch = getch()) != '\r')
					{
						fflush(stdin);
						if (ch == '\b')
						{
							if (i > 0)
							{
								i--;
								printf("\b \b");
								password[i] = 0;
								continue;
							}
							else
							{
								printf("\a");     //没有内容的时候
								continue;
							}
						}
						else
						{
							password[i] = ch;
							printf("*");
						}

						i++;
					}
					if (strcmp(password, STPASSWORD) == 0)
					{
						printf("\n\n登录中");
						for (int i = 0; i < 3; i++)
						{
							printf(".");
							Sleep(100);
						}
						judgeadmin = 0;
						return;
					}
					else
					{
						for (i = 3; i != 0; i--)
						{
							system("cls");
							printf("\n\n登录异常，本系统将在%d秒后自动关闭...\n", i);
							Sleep(1000);
						}
						exit(0);
					}

				}

			}

		}

		num = getch();
	}
}
int Menu_select()                              //菜单选择系统函数
{
	char c;
	system("cls");
	printf("\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t   ╭═════════════════════════════════○●○●═══╮\n");
	printf("\t\t\t\t   │              学生信息管理系统              │\n");
	printf("\t\t\t\t   ╰═══○●○●═════════════════════════════════╯\n");
	printf("\t\t\t\t   ┌───────────────────────────────────────────-┐\n");
	printf("\t\t\t\t   │                                            │\n");
	printf("\t\t\t\t   │ 1. 添加记录                    2. 显示记录 │\n");
	printf("\t\t\t\t   │                                            │\n");
	printf("\t\t\t\t   │ 3. 信息增加                    4. 数据排行 │\n");
	printf("\t\t\t\t   │                                            │\n");
	printf("\t\t\t\t   │ 5. 修改记录                    6. 删除记录 │\n");
	printf("\t\t\t\t   │                                            │\n");
	printf("\t\t\t\t   │ 7. 查询信息                    0. 退出程序 │\n");
	printf("\t\t\t\t   │                                            │\n");
	printf("\t\t\t\t   └────────────────────────────────────────────┘\n");
	printf("\t\t\t\t\t\t  请您选择(0-7):");
	c = getche();

	while (c < '0' || c > '7')
	{
		system("cls");
		printf("\n\n\n\n\n\n\n\n");
		printf("\t\t\t\t   ╭═════════════════════════════════○●○●═══╮\n");
		printf("\t\t\t\t   │              学生信息管理系统              │\n");
		printf("\t\t\t\t   ╰═══○●○●═════════════════════════════════╯\n");
		printf("\t\t\t\t   ┌───────────────────────────────────────────-┐\n");
		printf("\t\t\t\t   │                                            │\n");
		printf("\t\t\t\t   │ 1. 添加记录                    2. 显示记录 │\n");
		printf("\t\t\t\t   │                                            │\n");
		printf("\t\t\t\t   │ 3. 信息查询                    4. 数据排行 │\n");
		printf("\t\t\t\t   │                                            │\n");
		printf("\t\t\t\t   │ 5. 修改记录                    6. 删除记录 │\n");
		printf("\t\t\t\t   │                                            │\n");
		printf("\t\t\t\t   │ 7. 查询信息                    0. 退出程序 │\n");
		printf("\t\t\t\t   │                                            │\n");
		printf("\t\t\t\t   └────────────────────────────────────────────┘\n");
		printf("\t\t\t\t\t\t  请您选择(0-7):");
		c = getche();
		system("CLS");
	}
	return c - '0';

}
STU* Creat()//创建并输入链表函数
{
	for (int in = 1; in <= 3; in++)
	{
		Sleep(200);
		printf(".");
	}
	system("CLS");
	Head();
	printf("\t\t\t\t本操作项将建立新的名单，您是否想要继续？\n\t\t\t\t继续请按1\t退出请按任意键。\n\n\t\t\t\t");
	char cho;
	cho = getche();
	if (cho == '1')
	{
		for (int in = 1; in <= 3; in++)
		{
			Sleep(200);
			printf(".");
		}
		system("CLS");
		Head();	puts("");
		printf("\t\t\t\t*************创建名单************\n");
		//	STU*pHead = NULL;
		STU* pNew; //定义新节点，原结点（新节点前面那个，此处定义只是命名）
		icount = 0;
		pNew = (STU*)malloc(sizeof(STU));//此时所谓新结点和原结点都在同一空间
		//录入
		printf("\t\t\t\t请输入学生的信息：\n");
		printf("\t\t\t\t学号为0时停止录入(此次录入信息不包含在内)\n");

		printf("\t\t\t\t学号：\n\t\t\t\t");
		scanf("%s", pNew->iNumber);
		for (int i = 0;pNew->iNumber[i];i++) {
			if (48 > pNew->iNumber[i] || pNew->iNumber[i] > 57) {
				printf("\n\t●请重新输入学号:");
				fflush(stdin);
				scanf("%s", pNew->iNumber);
				i = -1;
			}
		}
		printf("\t\t\t\t姓名：\n\t\t\t\t");
		scanf("%s", pNew->cName);
		printf("\t\t\t\t成绩：\n\t\t\t\t");

		scanf("%d", &pNew->Score);
		while (pNew->Score > 100 || pNew->Score < 0)
		{
			printf("\n\t●请重新输入正确成绩:");
			fflush(stdin);
			scanf("%d", &pNew->Score);
		}
		printf("\n\n");
		/*说明，关于以上取址符的问题
				指针应该指向地址（空间）所以应该加上取址符；
				%s不加的原因是所指向字符数组名name本身就是地址；*/
		char null[10] = { "0" };
		while (1)//设置录入终止条件
		{
			//循环内处理录入的变量
			icount++;
			if (icount == 1)//分为第一个结点和其他结点两种情况
			{
				pNew->next = phead;

				pEnd = pNew;//此时新即头即尾
				phead = pNew;
			}
			else
			{
				pNew->next = NULL;
				pEnd->next = pNew;
				pEnd = pNew;
				/*原来的尾结点指向新结点，新结点位于链表末尾作尾结点*/
				/*现在再次分配内存空间为了下次录入*/
			}
			pNew = (STU*)malloc(sizeof(STU));
			printf("\t\t\t\t学号：\n\t\t\t\t");
			scanf("%s", pNew->iNumber);
			for (int i = 0;pNew->iNumber[i];i++) {
				if (48 > pNew->iNumber[i] || pNew->iNumber[i] > 57) {
					printf("\n\t●请重新输入学号:");
					fflush(stdin);
					scanf("%s", pNew->iNumber);
					i = -1;
				}
			}
			if (strcmp(pNew->iNumber, null) == 0)
			{
				break;
			}
			printf("\t\t\t\t姓名：\n\t\t\t\t");
			scanf("%s", pNew->cName);
			printf("\t\t\t\t成绩：\n\t\t\t\t");
			scanf("%d", &pNew->Score);
			while (pNew->Score > 100 || pNew->Score < 0)
			{
				printf("\n\t●请重新输入正确成绩:");
				fflush(stdin);
				scanf("%d", &pNew->Score);
			}
			printf("\n\n");
			//如此循环直到不符合录入条件

		}
		printf("\t\t\t\t");
		for (int in = 1; in <= 3; in++)
		{
			Sleep(200);
			printf(".");
		}
		printf("\n\t\t\t\t创建并录入成功！");
		free(pNew);
		//		Savestu();
		getch();
		Caozuowei();
		fflush(stdin);
		return phead;
	}

	else
	{
		return 0;
	}
}
void Print(STU* phead)						//输出函数
{
	for (int in = 1; in <= 3; in++)
	{
		Sleep(200);
		printf(".");
	}
	system("CLS");
	//	phead = Dataread_inf()	;
	Head();	puts("");
	STU* ptemp;
	int index = 1;
	printf("\t\t\t\t*************本名单共有%d名学生************\n", icount);
	ptemp = phead;
	if (icount == 0)
	{
		printf("\n\n\t\t\t\t名单为空");
		getch();
		return;
	}
	while (ptemp != NULL)
	{
		printf("\t\t\t\t第%d名学生是：\n", index);
		printf("\t\t\t\t");
		puts(ptemp->cName);
		printf("\t\t\t\t学号：%s\n\t\t\t\t姓名： %s\n\t\t\t\t成绩： %d\n\n", ptemp->iNumber, ptemp->cName, ptemp->Score);
		ptemp = ptemp->next;
		index++;
	}
	Chachong(phead);
	getch();
	Caozuowei();
	fflush(stdin);
}
void ADDstu(char* iNumber, char* cName, int Score) //插入函数
{
	STU* p = phead;
	int i;
	//逻辑
	//创建结点
	STU* ptemp;
	ptemp = (STU*)malloc(sizeof(STU));
	strcpy(ptemp->iNumber, iNumber);
	strcpy(ptemp->cName, cName);
	ptemp->Score = Score;
	ptemp->next = NULL;
	if (phead == NULL || pEnd == NULL)
	{
		phead = ptemp;
		pEnd = ptemp;
	}
	else
	{
		pEnd->next = ptemp;
		pEnd = ptemp;
	}
	ptemp = pEnd;
	icount++;


}

void sort(STU* phead) //修改函数
{
	int temp;char ci[10];char cn[20];
	STU* p = phead, * q, * s;
	printf("\t\t\t\t请选择您想用哪种方式排序。\n\t\t\t\t1)按成绩由高到低排序 \t2)按学号由小到大排序\n\t\t\t\t");
	char ccho;
	fflush(stdin);
	ccho = getche();
	if (ccho != '2' && ccho != '1')
	{
		printf("\t\t\t\t无效输入");
		return;
	}
	else if (ccho == '1')
	{
		if (p == NULL)
		{
			printf("\n\t\t\t\t该名单为空\n");
		}
		else
		{
			while (p->next != NULL)
			{
				q = p;//q初始化
				s = p->next;
				while (s != NULL)
				{
					if (q->Score < s->Score)
						q = s;//q记录最小节点位置
					s = s->next;//遍历
				}
				if (q != p)//若q值改变，交换
				{
					temp = q->Score; strcpy(ci, q->iNumber); strcpy(cn, q->cName);
					q->Score = p->Score; strcpy(q->iNumber, p->iNumber); strcpy(q->cName, p->cName);
					p->Score = temp;strcpy(p->iNumber, ci); strcpy(p->cName, cn);
				}
				p = p->next;//下一轮回交换位置
			}
			printf("\n\t\t\t\t");
			for (int in = 1; in <= 3; in++)
			{
				Sleep(200);
				printf(".");
			}
			printf("\n\t\t\t\t排序成功！");
		}
	}
	else if (ccho == '2')
	{
		if (p == NULL)
		{
			printf("\n该名单为空\n");
		}
		else
		{
			while (p->next != NULL)
			{
				q = p;//q初始化
				s = p->next;
				while (s != NULL)
				{
					if (strcmp(q->iNumber, s->iNumber) == 1)
						q = s;//q记录最小节点位置
					s = s->next;//遍历
				}
				if (q != p)//若q值改变，交换
				{
					temp = q->Score; strcpy(ci, q->iNumber); strcpy(cn, q->cName);
					q->Score = p->Score; strcpy(q->iNumber, p->iNumber); strcpy(q->cName, p->cName);
					p->Score = temp;strcpy(p->iNumber, ci); strcpy(p->cName, cn);
				}
				p = p->next;//下一轮回交换位置
			}
			printf("\n\t\t\t\t");
			for (int in = 1; in <= 3; in++)
			{
				Sleep(200);
				printf(".");
			}
			printf("\n\t\t\t\t排序成功！");
		}
	}
}
void Delete(STU* phead, int index) //删除函数（根据序号）
{
	//	printf("请选择删除方式。\n1)删除输入的序号对应的学生。\t2)删除全部学生\n");
	int i;

	printf("\t\t\t\t正在删除第%d名学生\t\t\t\t", index);
	if (index > icount)
	{
		for (int in = 1; in <= 3; in++)
		{
			Sleep(200);
			printf(".");
		}
		printf("\\n\t\t\t\t没有找到对应学生的信息，删除失败！");
		return;
	}
	STU* pTemp;
	pTemp = phead;
	STU* pPre;
	pPre = pTemp;
	for (i = 1; i < index; i++)
	{
		pPre = pTemp;
		pTemp = pTemp->next;

	}
	pPre->next = pTemp->next;
	free(pTemp);
	icount--;
	printf("\n\t\t\t\t");
	for (int in = 1; in <= 3; in++)
	{
		Sleep(200);
		printf(".");
	}
	printf("\n\t\t\t\t删除成功！");
}
STU* delHead(STU* phead)//删除函数（根据姓名）
{
	STU* p = phead;
	phead = p->next;
	free(p);
	icount--;
	printf("\n\t\t\t\t");
	for (int in = 1; in <= 3; in++)
	{
		Sleep(200);
		printf(".");
	}
	printf("\n\t\t\t\t删除成功！");
	return 	phead;
}
STU* FreeAll_LINK(STU* phead)//清空链表
{
	STU* p = phead;
	while (phead != NULL)
	{
		//记录结点
		p = phead;
		//向后移动
		phead = p->next;

		free(p);
		icount = 0;
	}
	return(phead);

}
void Search_stu(STU* phead)//查找学生
{
	for (int in = 1; in <= 3; in++)
	{
		Sleep(200);
		printf(".");
	}
	system("CLS");
	Head();	puts("");
	char ccho;
	printf("\t\t\t\t请选择您想要的查询方式\n\t\t\t\t1)按学号查询 \t2)按姓名查询\n\t\t\t\t");
	ccho = getche();
	for (int in = 1; in <= 3; in++)
	{
		Sleep(200);
		printf(".");
	}
	while (ccho != '1' && ccho != '2')
	{

		ccho = getch();
	}
	if (ccho == '1')
	{
		char siNumber[50];
		int p = 0;
		printf("\n\t\t\t\t请输入要查询的学生学号\n\t\t\t\t");
		scanf("%s", siNumber);
		STU* pTemp = phead;
		while (pTemp != NULL)
		{
			if (strcmp(pTemp->iNumber, siNumber) == 0)
			{
				p++;
				printf("\t\t\t\t学生信息如下：\n\t\t\t\t姓名： %s\n\t\t\t\t学号： %s\n\t\t\t\t成绩：%d\n", pTemp->cName, pTemp->iNumber, pTemp->Score);
				/*if(strcmp( pTemp -> lesson ,0) == 0 )
					printf("\t\t\t\t学生信息如下：\n\t\t\t\t姓名： %s\n\t\t\t\t学号： %s\n\t\t\t\t成绩： %d\n\t\t\t\t课程： 暂无选课",pTemp->cName,pTemp->iNumber,pTemp->Score,pTemp->lesson);
				else
					printf("\t\t\t\t学生信息如下：\n\t\t\t\t姓名： %s\n\t\t\t\t学号： %s\n\t\t\t\t成绩： %d\n\t\t\t\t课程： %s",pTemp->cName,pTemp->iNumber,pTemp->Score,pTemp->lesson);
				break;*/
			}
			pTemp = pTemp->next;
		}
		if (p == 0)
			printf("\t\t\t\t没有找到对应的学生信息。");
	}
	else if (ccho == '2')
	{
		char scName[50];
		int p = 0;
		printf("\n\t\t\t\t请输入要查询的学生姓名\n\t\t\t\t");
		scanf("%s", scName);
		STU* pTemp = phead;
		while (pTemp != NULL)
		{
			if (strcmp(pTemp->cName, scName) == 0)
			{
				p++;
				printf("\t\t\t\t该学生信息如下：\n\t\t\t\t姓名： %s\n\t\t\t\t学号： %s\n\t\t\t\t成绩：%d\n\n\n", pTemp->cName, pTemp->iNumber, pTemp->Score);
			}
			pTemp = pTemp->next;
		}
		if (p == 0)
			printf("\t\t\t\t没有找到对应的学生信息。");
	}
	getch();
	Caozuowei();
	fflush(stdin);

}
void Revise_stu(STU* phead)//修改学生信息
{
	for (int in = 1; in <= 3; in++)
	{
		Sleep(200);
		printf(".");
	}

	system("CLS");
	Head();	puts("");
	char ccho;
	printf("\t\t\t\t请选择您想要的修改方式：\n\t\t\t\t1) 修改指定学号的学生\t2) 修改指定姓名的学生\n\t\t\t\t");
	ccho = getche();
	for (int in = 1; in <= 3; in++)
	{
		Sleep(200);
		printf(".");
	}
	while (ccho != '1' && ccho != '2')
	{
		printf("\t\t\t\t无效输入！");
		printf("\n\t\t\t\t");
		ccho = getche();
	}
	if (ccho == '1')
	{
		char siNumber[50] = { 0 };
		int p = 0;
		printf("请输入要修改的学生学号\n\t\t\t\t");
		scanf("%s", siNumber);
		STU* pTemp = phead;
		while (pTemp != NULL)
		{
			if (strcmp(pTemp->iNumber, siNumber) == 0)
			{
				p++;
				printf("\t\t\t\t该学学号：生原信息如下：\n\t\t\t\t姓名： %s\n\t\t\t\t学号： %s\n\t\t\t\t成绩：%d\n\n\t\t\t\t将修改为\n\t\t\t\t", pTemp->cName, pTemp->iNumber, pTemp->Score);
				printf("\n");
				printf("\t\t\t\t姓名：\n\t\t\t\t");
				scanf("%s", pTemp->cName);
				printf("\t\t\t\t学号：\n\t\t\t\t");
				scanf("%s", pTemp->iNumber);
				for (int i = 0;pTemp->iNumber[i];i++)
				{
					if (48 > pTemp->iNumber[i] || pTemp->iNumber[i] > 57)
					{
						printf("\n\t■请重新输入学号:");
						fflush(stdin);
						scanf("%s", pTemp->iNumber);
						i = -1;
					}
				}
				printf("\t\t\t\t成绩：\n\t\t\t\t");
				scanf("%d", &pTemp->Score);
				while (pTemp->Score > 100 || pTemp->Score < 0)
				{
					printf("\n\t■请重新输入正确成绩:");
					fflush(stdin);
					scanf("%d", &pTemp->Score);
				}
				printf("\n");
				for (int in = 1; in <= 3; in++)
				{
					Sleep(200);
					printf(".");
				}
				printf("\n\t\t\t\t修改成功！");
				break;
			}
			pTemp = pTemp->next;
		}
		if (p == 0)
			printf("\t\t\t\t没有找到对应的学生信息。");
	}
	else
	{
		char scName[50];
		int p = 0;
		printf("\n\t\t\t\t请输入要修改的学生姓名\n\t\t\t\t");
		scanf("%s", scName);
		STU* pTemp = phead;
		while (pTemp != NULL)
		{
			if (strcmp(pTemp->cName, scName) == 0)
			{
				p++;
				printf("\n\t\t\t\t该学生原信息如下：\n\t\t\t\t姓名： %s\n\t\t\t\t学号： %s\n\t\t\t\t成绩：%d\n\n\t\t\t\t将修改为：", pTemp->cName, pTemp->iNumber, pTemp->Score);
				printf("\n");
				printf("\t\t\t\t姓名：\n\t\t\t\t");
				scanf("%s", pTemp->cName);
				printf("\t\t\t\t学号：\n\t\t\t\t");

				scanf("%s", pTemp->iNumber);
				for (int i = 0;pTemp->iNumber[i];i++)
				{
					if (48 > pTemp->iNumber[i] || pTemp->iNumber[i] > 57)
					{
						printf("\n\t■请重新输入学号:");
						fflush(stdin);
						scanf("%s", pTemp->iNumber);
						i = -1;
					}
				}
				printf("\t\t\t\t成绩：\n\t\t\t\t");
				scanf("%d", &pTemp->Score);
				while (pTemp->Score > 100 || pTemp->Score < 0)
				{
					printf("\n\t■请重新输入正确成绩:");
					fflush(stdin);
					scanf("%d", &pTemp->Score);
				}
				printf("\n");
				for (int in = 1; in <= 3; in++)
				{
					Sleep(200);
					printf(".");
				}
				printf("\n\t\t\t\t修改成功！\n");
			}
			pTemp = pTemp->next;
		}
		if (p == 0)
			printf("\t\t\t\t没有找到对应的学生信息。");
		getch();
		Caozuowei();
		fflush(stdin);
	}
}
void Caozuowei()
{
	int i;
	printf("\n\n\n\t ");
	for (i = 0; i < 50; i++)
	{
		printf("* ");
		Sleep(3);
	}
	printf("\n\t\t\t   ");
	printf("要返回主菜单请按任意键\t\t要退出程序请按Esc键\n");
	char cho;
	cho = getch();
	if (cho == 0x1b)
		exit(0);
}
void backlogin_caozuowei()
{
	int i;
	printf("\n\n\n\t ");
	for (i = 0; i < 50; i++)
	{
		printf("* ");
		Sleep(10);
	}
	printf("\n\t\t\t   ");
	printf("\t按Esc键结束程序\t\t\t按任意键返回登录界面\n");
	char cho;
	cho = getch();
	if (cho == 0x1b)
	{
		exit(0);
	}
	FreeAll_LINK(phead);
	Backlogin();
}

void Chachong(STU* phead) //查重
{
	int i, j;
	STU* p, * s;
	p = phead;
	s = phead;
	for (i = 1; i < icount; i++)
	{
		for (j = icount - i; j > 0; j--)
		{
			s = s->next;
			if (strcmp(s->iNumber, p->iNumber) == 0)
			{
				printf("发现重复学生信息：");
				printf("\n\t\t\t\t学号： %s\n", s->iNumber);
			}

		}
		p = p->next;
		s = p;
	}

}
void Savestu()//文件操作
				//将链表信息保存到文件中
{
	FILE* fp = NULL;
	//判断链表是否为空
	if (NULL == phead)
	{
		printf("没有学生");
		return;
	}
	STU* ptemp = phead;
	//打开文件
	fp = fopen("e:\\wj\\test.txt", "wb+");
	if (NULL == fp)
	{
		printf("打开失败");
		return;
	}
	//操作文件指针
	char strBuf[110] = { 0 };char strScore[10] = { 0 };
	while (ptemp)
	{
		//学号
		strcpy(strBuf, ptemp->iNumber);
		strcat(strBuf, ".");
		//姓名：
		strcat(strBuf, ptemp->cName);
		strcat(strBuf, ".");
		//成绩
	//	itoa(ptemp->Score,strScore,10);
		sprintf(strScore, "%d", ptemp->Score);
		strcat(strBuf, strScore);
		fwrite(strBuf, 1, strlen(strBuf), fp);
		fwrite("\r\n", 1, strlen("\r\n"), fp);
		ptemp = ptemp->next;
	}
	//关闭文件
	fclose(fp);
}
void Readstu()//读取文件中的内容到单链表
{
	FILE* fp = fopen("e:\\wj\\test.txt", "rb+");
	if (NULL == fp)
	{
		printf("打开失败");
		return;
	}
	char strBuf[110] = { 0 };
	while (NULL != fgets(strBuf, 110, fp))
	{

		int i = 0, ncount = 0, j = 0, k;
		char strNum[50] = { "0" };
		char strName[50] = { "0" };
		char strScore[10] = { "0" };
		i = 0;ncount = 0;
		for (i = 0, j = 0, k = 0, ncount = 0; strBuf[i] != '\r';i++)
		{
			if (0 == ncount)
			{
				strNum[i] = strBuf[i];
				if (strNum[i] == '.')
				{
					strNum[i] = '\0';
					ncount++;
					continue;
				}
			}
			if (ncount == 1)
			{
				strName[j] = strBuf[i];
				if (strName[j] == '.')
				{
					strName[j] = '\0';
					ncount++;
					continue;
				}
				j++;
			}
			if (ncount == 2)
			{
				strScore[k] = strBuf[i];
				k++;
				continue;
			}

		}
		ADDstu(strNum, strName, atoi(strScore));
	}
	fclose(fp);
}
void Backlogin()
{
	Readstu();
	system("cls");
	char cName[50] = { 0 };
	char iNumber[50] = { 0 };
	int  Score;
	Login();
	getchar();
	system("cls");
	int iN;
	if (judgeadmin == 0)
	{
		system("cls");
		STHead();
		printf("\n\t\t\t\t\t*************学生端信息查询************\n");
		int p = 0;
		STU* pTemp = phead;
		while (pTemp != NULL)
		{
			if (strcmp(pTemp->iNumber, STusername) == 0)
			{
				p++;
				while (!judgeadmin)
				{
					iN = Stmenu_select();
					switch (iN)
					{
					case 0:
						system("cls");
						printf("\n\n\n\t ");
						for (int i = 0; i < 50; i++)
						{
							printf("* ");
							Sleep(50);
						}
						printf("\n\t\t\t   ");
						printf("要返回登录界面按任意键\t\t要退出程序请按Esc键\n");
						char cho;
						fflush(stdin);
						cho = getch();
						if (cho == 0x1b)
						{
							FreeAll_LINK(phead);
							exit(0);
						}

						else
						{
							fflush(stdin);
							Savestu();
							system("cls");
							Backlogin();
						}
						break;
					case 1:
						system("cls");
						print_lessons();
						break;
					case 2:
						system("cls");
						printf("\t\t\t\t学生信息如下：\n\t\t\t\t姓名： %s\n\t\t\t\t学号： %s\n\t\t\t\t成绩： %d\n\t\t\t\t课程： %s", pTemp->cName, pTemp->iNumber, pTemp->Score, pTemp->lesson);
						Caozuowei();
						break;
					case 3:
						system("cls");
						save_lesson(choose_lesson());
						strcpy(pTemp->lesson, choose_lesson());
						Caozuowei();
						break;
					}

				}
			}
			break;
		}
		pTemp = pTemp->next;


		if (p == 0)
		{
			printf("\n\n\n\t\t\t\t\t\t管理员还没有添加你的信息哦。");
		}
		free(phead);
		backlogin_caozuowei();
	}
	else
	{
		system("cls");
		Head();
		while (judgeadmin)
		{

			iN = Menu_select();
			switch (iN)
			{
			case 0:
				system("cls");
				printf("\n\n\n\t ");
				for (int i = 0; i < 50; i++)
				{
					printf("* ");
					Sleep(50);
				}
				printf("\n\t\t\t   ");
				printf("要返回登录界面按任意键\t\t要退出程序请按Esc键\n");
				char cho;
				fflush(stdin);
				cho = getch();
				if (cho == 0x1b)
				{
					FreeAll_LINK(phead);
					exit(0);
				}

				else
				{
					fflush(stdin);
					Savestu();
					system("cls");
					Backlogin();
				}

				break;
			case 1:
				//		               创建
				phead = Creat();
				Savestu();
				break;
			case 2:
				//	打印
				Print(phead);
				break;
			case 3:
				for (int in = 1; in <= 3; in++)
				{
					Sleep(200);
					printf(".");
				}
				system("CLS");
				Head();	printf("\n");							//追加
				printf("\t\t\t\t学号：\n\t\t\t\t");
				scanf("%s", iNumber);
				for (int i = 0;iNumber[i];i++)
				{
					if (48 > iNumber[i] || iNumber[i] > 57)
					{
						printf("\n\t●请重新输入学号:");
						fflush(stdin);
						scanf("%s", iNumber);
						i = -1;
					}
				}
				printf("\t\t\t\t姓名：\n\t\t\t\t");
				scanf("%s", cName);
				printf("\t\t\t\t成绩：\n\t\t\t\t");
				scanf("%d", &Score);
				while (Score > 100 || Score < 0)
				{
					printf("\n\t●请重新输入正确成绩:");
					fflush(stdin);
					scanf("%d", &Score);
				}
				ADDstu(iNumber, cName, Score);
				printf("\t\t\t\t");
				printf("\t\t\t\t\n");
				for (int in = 1; in <= 3; in++)
				{
					Sleep(200);
					printf(".");
				}
				printf("\n\t\t\t\t添加成功！");
				getch();
				Caozuowei();
				Savestu();
				break;
			case 4:

				for (int in = 1; in <= 3; in++)
				{
					Sleep(200);
					printf(".");
				}
				system("CLS");
				Head();	puts("");								//排序
				printf("\t\t\t\t\t*************数据排序************\n");
				sort(phead);
				getch();
				Caozuowei();
				fflush(stdin);
				Savestu();
				break;
			case 5:
				Revise_stu(phead);
				Savestu();
				break;
			case 6:
				for (int in = 1; in <= 3; in++)
				{
					Sleep(200);
					printf(".");
				}
				system("CLS");
				Head();	puts("");							//删除
				printf("\t\t\t\t\t*************删除学生信息************\n\t\t\t\t请选择删除方式。\n\t\t\t\t1)删除输入的序号对应的学生。\t2)删除全部学生\n\t\t\t\t");
				char ccho;
				ccho = getche();
				while (ccho != '1' && ccho != '2')
				{
					ccho = getch();
				}
				if (ccho == '1')
				{
					int index;//要删除的学生序号
					printf("\n\t\t\t\t请输入要删除的学生序号：\n\t\t\t\t");
					scanf("%d", &index);
					getchar();
					if (index != 1)
						Delete(phead, index);
					else
					{
						phead = delHead(phead);
					}
					Savestu();
				}
				if (ccho == '2')
				{
					phead = FreeAll_LINK(phead);
					for (int in = 1; in <= 3; in++)
					{
						Sleep(200);
						printf(".");
					}
					phead = NULL;
					printf("\n\t\t\t\t已清空！");
					Savestu();
				}
				getch();
				Caozuowei();
				break;
			case 7:
				Search_stu(phead);
				break;
			}
			system("CLS");

		}
	}
}
void print_lessons()
{
	printf("\n\n\n");
	printf("\t\t\t╔════════════╦════════════╦════════════╦════════════╦════════════╗\n");
	printf("\t\t\t║  高等数学  ║  大学英语  ║  高等数学  ║  大学英语  ║  高等数学  ║\n");
	printf("\t\t\t╚════════════╝════════════╝════════════╝════════════╝════════════╝\n");
	printf("\t\t\t║  离散数学  ║  大学物理  ║  离散数学  ║  大学物理  ║  离散数学  ║\n");
	printf("\t\t\t╚════════════╝════════════╝════════════╝════════════╝════════════╝\n");
	printf("\t\t\t║            ║            ║            ║            ║            ║\n");
	printf("\t\t\t╚════════════╝════════════╝════════════╝════════════╝════════════╝\n");
	printf("\t\t\t║  程序设计  ║  大学体育  ║  程序设计  ║            ║  程序设计  ║\n");
	printf("\t\t\t╚════════════╝════════════╝════════════╝════════════╝════════════╝\n");
	printf("\t\t\t║            ║            ║            ║            ║            ║\n");
	printf("\t\t\t╚════════════╝════════════╝════════════╝════════════╝════════════╝\n");
	Caozuowei();
}
int Stmenu_select()
{
	char c;
	system("cls");
	printf("\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t   ╭═════════════════════════════════○●○●═══╮\n");
	printf("\t\t\t\t   │         学生信息管理系统     学生端        │\n");
	printf("\t\t\t\t   ╰═══○●○●═════════════════════════════════╯\n");
	printf("\t\t\t\t   ┌───────────────────────────────────────────-┐\n");
	printf("\t\t\t\t   │                                            │\n");
	printf("\t\t\t\t   │ 1. 查询课表                    2. 查询成绩 │\n");
	printf("\t\t\t\t   │                                            │\n");
	printf("\t\t\t\t   │ 3. 课程选修                    0. 退出程序 │\n");
	printf("\t\t\t\t   │                                            │\n");
	printf("\t\t\t\t   └────────────────────────────────────────────┘\n");
	printf("\t\t\t\t\t\t  请您选择(0-3):");
	c = getche();

	while (c < '0' || c > '3')
	{
		system("cls");
		printf("\n\n\n\n\n\n\n\n");
		printf("\t\t\t\t   ╭═════════════════════════════════○●○●═══╮\n");
		printf("\t\t\t\t   │         学生信息管理系统     学生端        │\n");
		printf("\t\t\t\t   ╰═══○●○●═════════════════════════════════╯\n");
		printf("\t\t\t\t   ┌───────────────────────────────────────────-┐\n");
		printf("\t\t\t\t   │                                            │\n");
		printf("\t\t\t\t   │ 1. 查询课表                    2. 查询成绩 │\n");
		printf("\t\t\t\t   │                                            │\n");
		printf("\t\t\t\t   │ 3. 课程选修                    0. 退出程序 │\n");
		printf("\t\t\t\t   │                                            │\n");
		printf("\t\t\t\t   └────────────────────────────────────────────┘\n");
		printf("\t\t\t\t\t  请您重新选择选择(0-3):");
		c = getche();
		system("CLS");
	}
	return c - '0';

}
char* choose_lesson()
{
	char l[20] = { 0 };
	char c;
	char* p;

	system("cls");
	while (1)
	{
		printf("\n\n\n\n\n\n\n\n");
		printf("\t\t\t\t   ╭══════════════════════════════○●○●═══╮\n");
		printf("\t\t\t\t   │            学生课程选修界面             │\n");
		printf("\t\t\t\t   ╰═══○●○●══════════════════════════════╯\n");
		printf("\t\t\t\t   ┌─────────────────────────────────────────┐\n");
		printf("\t\t\t\t   │                                         │\n");
		printf("\t\t\t\t   │ 1. 英语测试                 2. 英语写作 │\n");
		printf("\t\t\t\t   │                                         │\n");
		printf("\t\t\t\t   │ 3. 英语听力                 4. 英文鉴赏 │\n");
		printf("\t\t\t\t   │                                         │\n");
		printf("\t\t\t\t   └─────────────────────────────────────────┘\n");
		printf("\t\t\t\t\t\t  请您选择(1-4):");
		c = getche();
		while (c < '1' || c > '4')
		{
			system("cls");
			printf("\n\n\n\n\n\n\n\n");
			printf("\t\t\t\t   ╭══════════════════════════════○●○●═══╮\n");
			printf("\t\t\t\t   │            学生课程选修界面             │\n");
			printf("\t\t\t\t   ╰═══○●○●══════════════════════════════╯\n");
			printf("\t\t\t\t   ┌─────────────────────────────────────────┐\n");
			printf("\t\t\t\t   │                                         │\n");
			printf("\t\t\t\t   │ 1. 英语测试                 2. 英语写作 │\n");
			printf("\t\t\t\t   │                                         │\n");
			printf("\t\t\t\t   │ 3. 英语听力                 4. 英文鉴赏 │\n");
			printf("\t\t\t\t   │                                         │\n");
			printf("\t\t\t\t   └─────────────────────────────────────────┘\n");
			printf("\t\t\t\t\t      请您重新选择选择(1-4):");
			fflush(stdin);
			c = getche();
		}
		if (c == '1')
		{
			strcpy(l, "英语测试");
			printf("选择成功！");
			break;
		}
		if (c == '2')
		{
			strcpy(l, "英语写作");
			printf("选择成功！");
			break;
		}
		if (c == '3')
		{
			strcpy(l, "英语听力");
			printf("选择成功！");
			break;
		}
		if (c == '4')
		{
			strcpy(l, "英语鉴赏");
			printf("选择成功！");
			break;
		}
	}
	p = l;
	return p;
}
void save_lesson(char* l)
{
	FILE* f = NULL;
	//打开文件
	f = fopen("e:\\wj\\test1.txt", "wt");
	if (f == NULL)
	{
		printf("发生问题");
		return;
	}
	fputs(l, f);
	fclose(f);
}
void read_lesson()
{
	int i = 0;
	FILE* fp = fopen("e:\\wj\\test1.txt", "rt");
	if (fp == NULL)
	{
		printf("发生问题");
		return;
	}
	STU* pTemp = phead;
	while (pTemp != NULL)
	{
		if (strcmp(pTemp->iNumber, STusername) == 0)
		{
			printf("%s", pTemp->lesson);
			break;
		}
		pTemp = pTemp->next;
	}
	fclose(fp);
	getch();
	Caozuowei();
}
