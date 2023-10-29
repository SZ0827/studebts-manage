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
//��������ĸ��д�Ժͱ�������
typedef struct Student
{
	char cName[50];
	char iNumber[50];
	int  Score;
	char lesson[50];
	struct Student* next;
}STU;
//��Ϊ������ͬ���Եݹ鶨��
STU* phead = NULL;
STU* pEnd = NULL;
int icount;//ȫ�ֶ���������
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
	printf("��ӭʹ�ñ�ϵͳ��\n");
	int i;
	printf("\n\n\n\n\n\n\n\n\t\t\t\t\t");
	char heihei[] = { "��������ѧ������ϵͳ..." };
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
		printf("\n\t\t\t\t\t*************ѧ������Ϣ��ѯ************\n");
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
						printf("Ҫ���ص�¼���水�����\t\tҪ�˳������밴Esc��\n");
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
						printf("\t\t\t\tѧ����Ϣ���£�\n\t\t\t\t������ %s\n\t\t\t\tѧ�ţ� %s\n\t\t\t\t�ɼ��� %d\n\t\t\t\t�γ̣� %s", pTemp->cName, pTemp->iNumber, pTemp->Score, pTemp->lesson);
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
			printf("\n\n\n\t\t\t\t\t\t����Ա��û����������ϢŶ��");
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
				printf("Ҫ���ص�¼���水�����\t\tҪ�˳������밴Esc��\n");
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
				//		               ����
				phead = Creat();
				Savestu();
				break;
			case 2:
				//	��ӡ
				Print(phead);
				break;
			case 3:
				for (int in = 1; in <= 3; in++)
				{
					Sleep(200);
					printf(".");
				}
				system("CLS");
				Head();	printf("\n");							//׷��
				printf("\t\t\t\tѧ�ţ�\n\t\t\t\t");
				scanf("%s", iNumber);
				for (int i = 0;iNumber[i];i++)
				{
					if (48 > iNumber[i] || iNumber[i] > 57)
					{
						printf("\n\t������������ѧ��:");
						fflush(stdin);
						scanf("%s", iNumber);
						i = -1;
					}
				}
				printf("\t\t\t\t������\n\t\t\t\t");
				scanf("%s", cName);
				printf("\t\t\t\t�ɼ���\n\t\t\t\t");
				scanf("%d", &Score);
				while (Score > 100 || Score < 0)
				{
					printf("\n\t��������������ȷ�ɼ�:");
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
				printf("\n\t\t\t\t��ӳɹ���");
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
				Head();	puts("");								//����
				printf("\t\t\t\t\t*************��������************\n");
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
				Head();	puts("");							//ɾ��
				printf("\t\t\t\t\t*************ɾ��ѧ����Ϣ************\n\t\t\t\t��ѡ��ɾ����ʽ��\n\t\t\t\t1)ɾ���������Ŷ�Ӧ��ѧ����\t2)ɾ��ȫ��ѧ��\n\t\t\t\t");
				char ccho;
				ccho = getche();
				while (ccho != '1' && ccho != '2')
				{
					ccho = getch();
				}
				if (ccho == '1')
				{
					int index;//Ҫɾ����ѧ�����
					printf("\n\t\t\t\t������Ҫɾ����ѧ����ţ�\n\t\t\t\t");
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
					printf("\n\t\t\t\t����գ�");
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
	printf("\t\t\t\t\t�q �] % �r                           �q ```�r  \n");
	printf("\t\t\t\t\t(@^o^@) ѧ����Ϣ����ϵͳ   �����(��:��)\n");
	printf("\t\t\t\t\t(~):(~)                          (~)v(~) \n");
	printf("\n\n\n");
}
void STHead()
{
	printf("\n");
	printf("\t\t\t\t\t�q �] % �r                           �q ```�r  \n");
	printf("\t\t\t\t\t(@^o^@) ѧ����Ϣ����ϵͳ   ѧ����(��:��)\n");
	printf("\t\t\t\t\t(~):(~)                          (~)v(~) \n");
	printf("\n\n\n");
}
void SetPos(int x, int y)				//������
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
	fflush(stdin); //�����ˢ�����뻺����
	printf("\n");
	printf("\t\t\t\t\t�q �] % �r                   �q ```�r  \n");
	printf("\t\t\t\t\t(@^o^@) ѧ����Ϣ����ϵͳ (��:��)\n");
	printf("\t\t\t\t\t(~):(~)                  (~)v(~) \n");
	printf("\n\n\n");
	printf("\t\t\t\t\t   ������       LOGIN      ������       \n");
	printf("\n\n\n");
	char xing[] = { "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * " };
	for (int i = 0;i < strlen(xing);i++)
	{
		printf("%c", xing[i]);
		Sleep(10);
	}

	printf("\n\n\t\t\t\t\t\t��ѡ�����ĵ�¼���:\n\n\n\n\t\t\t\t\t\t\t1.����Ա\n\n\n\n\t\t\t\t\t\t\t2.ѧ��");
	char num;
	fflush(stdin);
	num = getch();
	while (1)
	{
		system("cls");
		if (num != '1' && num != '2')
		{
			printf("\n");
			printf("\t\t\t\t\t�q �] % �r                   �q ```�r  \n");
			printf("\t\t\t\t\t(@^o^@) ѧ����Ϣ����ϵͳ (��:��)\n");
			printf("\t\t\t\t\t(~):(~)                  (~)v(~) \n");
			printf("\n\n\n");
			printf("\t\t\t\t\t   ������       LOGIN      ������       \n");
			printf("\n\n\n");
			printf("%s", xing);
			printf("\n\n\t\t\t\t\t������ѡ�����ĵ�¼���:\n\n\n\n\t\t\t\t\t\t\t1.����Ա\n\n\n\n\t\t\t\t\t\t\t2.ѧ��");
			fflush(stdin);
			num = getch();

		}
		if (num == '1')
		{
			judgeadmin = 1;
			system("cls");
			printf("\n");
			printf("\t\t\t\t\t�q �] % �r                           �q ```�r  \n");
			printf("\t\t\t\t\t(@^o^@) ѧ����Ϣ����ϵͳ   �����(��:��)\n");
			printf("\t\t\t\t\t(~):(~)                          (~)v(~) \n");
			printf("\n\n\n");
			printf("\t\t\t\t\t       ������       LOGIN      ������       \n");
			printf("\n\n\n");
			char xing[] = { "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * " };
			for (int i = 0;i < strlen(xing);i++)
			{
				printf("%c", xing[i]);
				Sleep(10);
			}
			printf("\n\n\n\n\n\n\t\t\t\t�����Թ���Ա��ݵ�¼�����س������������ո��������һҳ");
			char cho;
			cho = getch();
			if (cho == 0x0d)
			{
				system("cls");
				Head();
				printf("\t\t\t\t\t       ������       LOGIN      ������       \n");
				printf("\n\n\n");
				char xing[] = { "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * " };
				for (int i = 0;i < strlen(xing);i++)
				{
					printf("%c", xing[i]);
					Sleep(10);
				}
				char username[50] = { 0 };
				char password[50] = { 0 };
				printf("\n\n\n\t\t\t\t\t\t�������û���������\n\n");
				printf("\t\t\t\t\t�û�����");
				int x, y;
				SetPos(50, 15);
				printf("������������������������������");
				SetPos(50, 16);
				printf("������� �� ��");
				SetPos(50, 17);
				printf("������������������������������");
				SetPos(52, 16);
				scanf("%s", username);
				printf("\n\n");
				SetPos(30, 21);
				printf("\t\t���룺 ");
				SetPos(50, 20);
				printf("������������������������������");
				SetPos(50, 21);
				printf("�������������");
				SetPos(50, 22);
				printf("������������������������������");
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
							printf("\a");     //û�����ݵ�ʱ��
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
					printf("��");
					Sleep(100);
					x += 6;
					SetPos(x, y);
					printf("��");
					Sleep(100);
					x += 6;
					SetPos(x, y);
					printf("��");
					Sleep(100);
					x += 6;
					SetPos(x, y);
					printf("��");
					Sleep(100);
					x += 6;
					SetPos(x, y);
					printf("��");
					Sleep(100);
					x += 6;
					SetPos(x, y);
					printf("��");
					Sleep(100);
					x += 6;
					SetPos(x, y);
					printf("��");
					Sleep(100);
					x += 6;
					SetPos(x, y);
					printf("��");
					Sleep(100);
					x += 6;
					SetPos(x, y);
					printf("��");
					printf("\n\n\t\t\t\t\t\t\t\t��ӭ��������Ա��");
					system("pause");
					return;
				}
				else
				{
					SetPos(70, 21);
					system("cls");
					printf("\n\n\n");
					printf("\t\t\t\t\t   �û������������������һ�λ���\n");
					//	system("pause");
					printf("\n\n\t\t\t\t\t       ������       LOGIN      ������       \n");
					printf("\n\n\n");
					for (int i = 0;i < strlen(xing);i++)
					{
						printf("%c", xing[i]);
						Sleep(10);
					}
					printf("\n\n\t\t\t\tҪ���µ�¼�밴�����\t\tҪ�˳������밴Esc��\n");
					char cho;
					cho = getch();
					if (cho == 0x1b)
						exit(0);
					system("cls");

					Head();
					printf("\t\t\t\t\t       ������       LOGIN      ������       \n");
					printf("\n\n\n");

					for (int i = 0;i < strlen(xing);i++)
					{
						printf("%c", xing[i]);
						Sleep(10);
					}
					char username[50] = { 0 };
					char password[50] = { 0 };
					printf("\n\n\n\t\t\t\t\t\t�������û���������\n\n");
					printf("\t\t\t\t\t�û�����");
					int x, y;
					SetPos(50, 15);
					printf("������������������������������");
					SetPos(50, 16);
					printf("������� �� ��");
					SetPos(50, 17);
					printf("������������������������������");
					SetPos(52, 16);
					scanf("%s", username);
					printf("\n\n");
					SetPos(30, 21);
					printf("\t\t���룺 ");
					SetPos(50, 20);
					printf("������������������������������");
					SetPos(50, 21);
					printf("�������������");
					SetPos(50, 22);
					printf("������������������������������");
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
								printf("\a");     //û�����ݵ�ʱ��
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
						printf("��");
						Sleep(100);
						x += 6;
						SetPos(x, y);
						printf("��");
						Sleep(100);
						x += 6;
						SetPos(x, y);
						printf("��");
						Sleep(100);
						x += 6;
						SetPos(x, y);
						printf("��");
						Sleep(100);
						x += 6;
						SetPos(x, y);
						printf("��");//
						Sleep(100);
						x += 6;
						SetPos(x, y);
						printf("��");
						Sleep(100);
						x += 6;
						SetPos(x, y);
						printf("��");
						Sleep(100);
						x += 6;
						SetPos(x, y);
						printf("��");
						Sleep(100);
						x += 6;
						SetPos(x, y);
						printf("��");
						printf("\n\n\t\t\t\t\t\t\t\t��ӭ��������Ա��");
						system("pause");
						return;
					}
					else
					{
						for (i = 3; i != 0; i--)
						{
							system("cls");
							printf("\n\n��¼�쳣����ϵͳ����%d����Զ��ر�...\n", i);
							Sleep(1000);
						}
						exit(0);
					}
				}
			}
		}
		//ѧ����
		if (num == '2')
		{
			system("cls");
			printf("\n");
			printf("\t\t\t\t\t�q �] % �r                           �q ```�r  \n");
			printf("\t\t\t\t\t(@^o^@) ѧ����Ϣ����ϵͳ   ѧ����(��:��)\n");
			printf("\t\t\t\t\t(~):(~)                          (~)v(~) \n");
			printf("\n\n\n");
			printf("\t\t\t\t\t       ������       LOGIN      ������       \n");
			printf("\n\n\n");
			char xing[] = { "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * " };
			for (int i = 0;i < strlen(xing);i++)
			{
				printf("%c", xing[i]);
				Sleep(10);
			}
			printf("\n\n\n\n\n\n\t\t\t\t������ѧ������ݵ�¼�����س������������ո��������һҳ");
			char cho;
			cho = getch();
			if (cho == 0x0d)
			{
				//ѧ���˵�¼
				system("cls");
				STHead();
				printf("\t\t\t\t\t       ������       LOGIN      ������       \n");
				printf("\n\n\n");
				for (int i = 0;i < strlen(xing);i++)
				{
					printf("%c", xing[i]);
					Sleep(10);
				}
				char password[50] = { 0 };
				printf("\n\n\n\t\t\t\t\t\t�������û���������\n\n");
				printf("\t\t\t\t\t�û�����");
				int x, y;
				SetPos(50, 15);
				printf("������������������������������");
				SetPos(50, 16);
				printf("������� �� ��");
				SetPos(50, 17);
				printf("������������������������������");
				SetPos(52, 16);
				scanf("%s", STusername);
				printf("\n\n");
				SetPos(30, 21);
				printf("\t\t���룺 ");
				SetPos(50, 20);
				printf("������������������������������");
				SetPos(50, 21);
				printf("�������������");
				SetPos(50, 22);
				printf("������������������������������");
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
							printf("\a");     //û�����ݵ�ʱ��
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
					printf("\n\n��¼��");
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
					printf("\t\t\t\t\t   �û������������������һ�λ���\n");
					//	system("pause");
					printf("\n\n\t\t\t\t\t       ������       LOGIN      ������       \n");
					printf("\n\n\n");
					for (int i = 0;i < strlen(xing);i++)
					{
						printf("%c", xing[i]);
						Sleep(10);
					}
					printf("\n\n\t\t\t\tҪ���µ�¼�밴�����\t\tҪ�˳������밴Esc��\n");
					char cho;
					cho = getch();
					if (cho == 0x1b)
						exit(0);
					system("cls");

					STHead();
					printf("\t\t\t\t\t       ������       LOGIN      ������       \n");
					printf("\n\n\n");
					for (int i = 0;i < strlen(xing);i++)
					{
						printf("%c", xing[i]);
						Sleep(10);
					}
					char password[50] = { 0 };
					printf("\n\n\n\t\t\t\t\t\t�������û���������\n\n");
					printf("\t\t\t\t\t�û�����");
					int x, y;
					SetPos(50, 15);
					printf("������������������������������");
					SetPos(50, 16);
					printf("������� �� ��");
					SetPos(50, 17);
					printf("������������������������������");
					SetPos(52, 16);
					scanf("%s", STusername);
					printf("\n\n");
					SetPos(30, 21);
					printf("\t\t���룺 ");
					SetPos(50, 20);
					printf("������������������������������");
					SetPos(50, 21);
					printf("�������������");
					SetPos(50, 22);
					printf("������������������������������");
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
								printf("\a");     //û�����ݵ�ʱ��
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
						printf("\n\n��¼��");
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
							printf("\n\n��¼�쳣����ϵͳ����%d����Զ��ر�...\n", i);
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
int Menu_select()                              //�˵�ѡ��ϵͳ����
{
	char c;
	system("cls");
	printf("\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t   �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�����T�T�T�r\n");
	printf("\t\t\t\t   ��              ѧ����Ϣ����ϵͳ              ��\n");
	printf("\t\t\t\t   �t�T�T�T�����T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s\n");
	printf("\t\t\t\t   ����������������������������������������������������������������������������������������-��\n");
	printf("\t\t\t\t   ��                                            ��\n");
	printf("\t\t\t\t   �� 1. ��Ӽ�¼                    2. ��ʾ��¼ ��\n");
	printf("\t\t\t\t   ��                                            ��\n");
	printf("\t\t\t\t   �� 3. ��Ϣ����                    4. �������� ��\n");
	printf("\t\t\t\t   ��                                            ��\n");
	printf("\t\t\t\t   �� 5. �޸ļ�¼                    6. ɾ����¼ ��\n");
	printf("\t\t\t\t   ��                                            ��\n");
	printf("\t\t\t\t   �� 7. ��ѯ��Ϣ                    0. �˳����� ��\n");
	printf("\t\t\t\t   ��                                            ��\n");
	printf("\t\t\t\t   ��������������������������������������������������������������������������������������������\n");
	printf("\t\t\t\t\t\t  ����ѡ��(0-7):");
	c = getche();

	while (c < '0' || c > '7')
	{
		system("cls");
		printf("\n\n\n\n\n\n\n\n");
		printf("\t\t\t\t   �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�����T�T�T�r\n");
		printf("\t\t\t\t   ��              ѧ����Ϣ����ϵͳ              ��\n");
		printf("\t\t\t\t   �t�T�T�T�����T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s\n");
		printf("\t\t\t\t   ����������������������������������������������������������������������������������������-��\n");
		printf("\t\t\t\t   ��                                            ��\n");
		printf("\t\t\t\t   �� 1. ��Ӽ�¼                    2. ��ʾ��¼ ��\n");
		printf("\t\t\t\t   ��                                            ��\n");
		printf("\t\t\t\t   �� 3. ��Ϣ��ѯ                    4. �������� ��\n");
		printf("\t\t\t\t   ��                                            ��\n");
		printf("\t\t\t\t   �� 5. �޸ļ�¼                    6. ɾ����¼ ��\n");
		printf("\t\t\t\t   ��                                            ��\n");
		printf("\t\t\t\t   �� 7. ��ѯ��Ϣ                    0. �˳����� ��\n");
		printf("\t\t\t\t   ��                                            ��\n");
		printf("\t\t\t\t   ��������������������������������������������������������������������������������������������\n");
		printf("\t\t\t\t\t\t  ����ѡ��(0-7):");
		c = getche();
		system("CLS");
	}
	return c - '0';

}
STU* Creat()//����������������
{
	for (int in = 1; in <= 3; in++)
	{
		Sleep(200);
		printf(".");
	}
	system("CLS");
	Head();
	printf("\t\t\t\t������������µ����������Ƿ���Ҫ������\n\t\t\t\t�����밴1\t�˳��밴�������\n\n\t\t\t\t");
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
		printf("\t\t\t\t*************��������************\n");
		//	STU*pHead = NULL;
		STU* pNew; //�����½ڵ㣬ԭ��㣨�½ڵ�ǰ���Ǹ����˴�����ֻ��������
		icount = 0;
		pNew = (STU*)malloc(sizeof(STU));//��ʱ��ν�½���ԭ��㶼��ͬһ�ռ�
		//¼��
		printf("\t\t\t\t������ѧ������Ϣ��\n");
		printf("\t\t\t\tѧ��Ϊ0ʱֹͣ¼��(�˴�¼����Ϣ����������)\n");

		printf("\t\t\t\tѧ�ţ�\n\t\t\t\t");
		scanf("%s", pNew->iNumber);
		for (int i = 0;pNew->iNumber[i];i++) {
			if (48 > pNew->iNumber[i] || pNew->iNumber[i] > 57) {
				printf("\n\t������������ѧ��:");
				fflush(stdin);
				scanf("%s", pNew->iNumber);
				i = -1;
			}
		}
		printf("\t\t\t\t������\n\t\t\t\t");
		scanf("%s", pNew->cName);
		printf("\t\t\t\t�ɼ���\n\t\t\t\t");

		scanf("%d", &pNew->Score);
		while (pNew->Score > 100 || pNew->Score < 0)
		{
			printf("\n\t��������������ȷ�ɼ�:");
			fflush(stdin);
			scanf("%d", &pNew->Score);
		}
		printf("\n\n");
		/*˵������������ȡַ��������
				ָ��Ӧ��ָ���ַ���ռ䣩����Ӧ�ü���ȡַ����
				%s���ӵ�ԭ������ָ���ַ�������name������ǵ�ַ��*/
		char null[10] = { "0" };
		while (1)//����¼����ֹ����
		{
			//ѭ���ڴ���¼��ı���
			icount++;
			if (icount == 1)//��Ϊ��һ��������������������
			{
				pNew->next = phead;

				pEnd = pNew;//��ʱ�¼�ͷ��β
				phead = pNew;
			}
			else
			{
				pNew->next = NULL;
				pEnd->next = pNew;
				pEnd = pNew;
				/*ԭ����β���ָ���½�㣬�½��λ������ĩβ��β���*/
				/*�����ٴη����ڴ�ռ�Ϊ���´�¼��*/
			}
			pNew = (STU*)malloc(sizeof(STU));
			printf("\t\t\t\tѧ�ţ�\n\t\t\t\t");
			scanf("%s", pNew->iNumber);
			for (int i = 0;pNew->iNumber[i];i++) {
				if (48 > pNew->iNumber[i] || pNew->iNumber[i] > 57) {
					printf("\n\t������������ѧ��:");
					fflush(stdin);
					scanf("%s", pNew->iNumber);
					i = -1;
				}
			}
			if (strcmp(pNew->iNumber, null) == 0)
			{
				break;
			}
			printf("\t\t\t\t������\n\t\t\t\t");
			scanf("%s", pNew->cName);
			printf("\t\t\t\t�ɼ���\n\t\t\t\t");
			scanf("%d", &pNew->Score);
			while (pNew->Score > 100 || pNew->Score < 0)
			{
				printf("\n\t��������������ȷ�ɼ�:");
				fflush(stdin);
				scanf("%d", &pNew->Score);
			}
			printf("\n\n");
			//���ѭ��ֱ��������¼������

		}
		printf("\t\t\t\t");
		for (int in = 1; in <= 3; in++)
		{
			Sleep(200);
			printf(".");
		}
		printf("\n\t\t\t\t������¼��ɹ���");
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
void Print(STU* phead)						//�������
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
	printf("\t\t\t\t*************����������%d��ѧ��************\n", icount);
	ptemp = phead;
	if (icount == 0)
	{
		printf("\n\n\t\t\t\t����Ϊ��");
		getch();
		return;
	}
	while (ptemp != NULL)
	{
		printf("\t\t\t\t��%d��ѧ���ǣ�\n", index);
		printf("\t\t\t\t");
		puts(ptemp->cName);
		printf("\t\t\t\tѧ�ţ�%s\n\t\t\t\t������ %s\n\t\t\t\t�ɼ��� %d\n\n", ptemp->iNumber, ptemp->cName, ptemp->Score);
		ptemp = ptemp->next;
		index++;
	}
	Chachong(phead);
	getch();
	Caozuowei();
	fflush(stdin);
}
void ADDstu(char* iNumber, char* cName, int Score) //���뺯��
{
	STU* p = phead;
	int i;
	//�߼�
	//�������
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

void sort(STU* phead) //�޸ĺ���
{
	int temp;char ci[10];char cn[20];
	STU* p = phead, * q, * s;
	printf("\t\t\t\t��ѡ�����������ַ�ʽ����\n\t\t\t\t1)���ɼ��ɸߵ������� \t2)��ѧ����С��������\n\t\t\t\t");
	char ccho;
	fflush(stdin);
	ccho = getche();
	if (ccho != '2' && ccho != '1')
	{
		printf("\t\t\t\t��Ч����");
		return;
	}
	else if (ccho == '1')
	{
		if (p == NULL)
		{
			printf("\n\t\t\t\t������Ϊ��\n");
		}
		else
		{
			while (p->next != NULL)
			{
				q = p;//q��ʼ��
				s = p->next;
				while (s != NULL)
				{
					if (q->Score < s->Score)
						q = s;//q��¼��С�ڵ�λ��
					s = s->next;//����
				}
				if (q != p)//��qֵ�ı䣬����
				{
					temp = q->Score; strcpy(ci, q->iNumber); strcpy(cn, q->cName);
					q->Score = p->Score; strcpy(q->iNumber, p->iNumber); strcpy(q->cName, p->cName);
					p->Score = temp;strcpy(p->iNumber, ci); strcpy(p->cName, cn);
				}
				p = p->next;//��һ�ֻؽ���λ��
			}
			printf("\n\t\t\t\t");
			for (int in = 1; in <= 3; in++)
			{
				Sleep(200);
				printf(".");
			}
			printf("\n\t\t\t\t����ɹ���");
		}
	}
	else if (ccho == '2')
	{
		if (p == NULL)
		{
			printf("\n������Ϊ��\n");
		}
		else
		{
			while (p->next != NULL)
			{
				q = p;//q��ʼ��
				s = p->next;
				while (s != NULL)
				{
					if (strcmp(q->iNumber, s->iNumber) == 1)
						q = s;//q��¼��С�ڵ�λ��
					s = s->next;//����
				}
				if (q != p)//��qֵ�ı䣬����
				{
					temp = q->Score; strcpy(ci, q->iNumber); strcpy(cn, q->cName);
					q->Score = p->Score; strcpy(q->iNumber, p->iNumber); strcpy(q->cName, p->cName);
					p->Score = temp;strcpy(p->iNumber, ci); strcpy(p->cName, cn);
				}
				p = p->next;//��һ�ֻؽ���λ��
			}
			printf("\n\t\t\t\t");
			for (int in = 1; in <= 3; in++)
			{
				Sleep(200);
				printf(".");
			}
			printf("\n\t\t\t\t����ɹ���");
		}
	}
}
void Delete(STU* phead, int index) //ɾ��������������ţ�
{
	//	printf("��ѡ��ɾ����ʽ��\n1)ɾ���������Ŷ�Ӧ��ѧ����\t2)ɾ��ȫ��ѧ��\n");
	int i;

	printf("\t\t\t\t����ɾ����%d��ѧ��\t\t\t\t", index);
	if (index > icount)
	{
		for (int in = 1; in <= 3; in++)
		{
			Sleep(200);
			printf(".");
		}
		printf("\\n\t\t\t\tû���ҵ���Ӧѧ������Ϣ��ɾ��ʧ�ܣ�");
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
	printf("\n\t\t\t\tɾ���ɹ���");
}
STU* delHead(STU* phead)//ɾ������������������
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
	printf("\n\t\t\t\tɾ���ɹ���");
	return 	phead;
}
STU* FreeAll_LINK(STU* phead)//�������
{
	STU* p = phead;
	while (phead != NULL)
	{
		//��¼���
		p = phead;
		//����ƶ�
		phead = p->next;

		free(p);
		icount = 0;
	}
	return(phead);

}
void Search_stu(STU* phead)//����ѧ��
{
	for (int in = 1; in <= 3; in++)
	{
		Sleep(200);
		printf(".");
	}
	system("CLS");
	Head();	puts("");
	char ccho;
	printf("\t\t\t\t��ѡ������Ҫ�Ĳ�ѯ��ʽ\n\t\t\t\t1)��ѧ�Ų�ѯ \t2)��������ѯ\n\t\t\t\t");
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
		printf("\n\t\t\t\t������Ҫ��ѯ��ѧ��ѧ��\n\t\t\t\t");
		scanf("%s", siNumber);
		STU* pTemp = phead;
		while (pTemp != NULL)
		{
			if (strcmp(pTemp->iNumber, siNumber) == 0)
			{
				p++;
				printf("\t\t\t\tѧ����Ϣ���£�\n\t\t\t\t������ %s\n\t\t\t\tѧ�ţ� %s\n\t\t\t\t�ɼ���%d\n", pTemp->cName, pTemp->iNumber, pTemp->Score);
				/*if(strcmp( pTemp -> lesson ,0) == 0 )
					printf("\t\t\t\tѧ����Ϣ���£�\n\t\t\t\t������ %s\n\t\t\t\tѧ�ţ� %s\n\t\t\t\t�ɼ��� %d\n\t\t\t\t�γ̣� ����ѡ��",pTemp->cName,pTemp->iNumber,pTemp->Score,pTemp->lesson);
				else
					printf("\t\t\t\tѧ����Ϣ���£�\n\t\t\t\t������ %s\n\t\t\t\tѧ�ţ� %s\n\t\t\t\t�ɼ��� %d\n\t\t\t\t�γ̣� %s",pTemp->cName,pTemp->iNumber,pTemp->Score,pTemp->lesson);
				break;*/
			}
			pTemp = pTemp->next;
		}
		if (p == 0)
			printf("\t\t\t\tû���ҵ���Ӧ��ѧ����Ϣ��");
	}
	else if (ccho == '2')
	{
		char scName[50];
		int p = 0;
		printf("\n\t\t\t\t������Ҫ��ѯ��ѧ������\n\t\t\t\t");
		scanf("%s", scName);
		STU* pTemp = phead;
		while (pTemp != NULL)
		{
			if (strcmp(pTemp->cName, scName) == 0)
			{
				p++;
				printf("\t\t\t\t��ѧ����Ϣ���£�\n\t\t\t\t������ %s\n\t\t\t\tѧ�ţ� %s\n\t\t\t\t�ɼ���%d\n\n\n", pTemp->cName, pTemp->iNumber, pTemp->Score);
			}
			pTemp = pTemp->next;
		}
		if (p == 0)
			printf("\t\t\t\tû���ҵ���Ӧ��ѧ����Ϣ��");
	}
	getch();
	Caozuowei();
	fflush(stdin);

}
void Revise_stu(STU* phead)//�޸�ѧ����Ϣ
{
	for (int in = 1; in <= 3; in++)
	{
		Sleep(200);
		printf(".");
	}

	system("CLS");
	Head();	puts("");
	char ccho;
	printf("\t\t\t\t��ѡ������Ҫ���޸ķ�ʽ��\n\t\t\t\t1) �޸�ָ��ѧ�ŵ�ѧ��\t2) �޸�ָ��������ѧ��\n\t\t\t\t");
	ccho = getche();
	for (int in = 1; in <= 3; in++)
	{
		Sleep(200);
		printf(".");
	}
	while (ccho != '1' && ccho != '2')
	{
		printf("\t\t\t\t��Ч���룡");
		printf("\n\t\t\t\t");
		ccho = getche();
	}
	if (ccho == '1')
	{
		char siNumber[50] = { 0 };
		int p = 0;
		printf("������Ҫ�޸ĵ�ѧ��ѧ��\n\t\t\t\t");
		scanf("%s", siNumber);
		STU* pTemp = phead;
		while (pTemp != NULL)
		{
			if (strcmp(pTemp->iNumber, siNumber) == 0)
			{
				p++;
				printf("\t\t\t\t��ѧѧ�ţ���ԭ��Ϣ���£�\n\t\t\t\t������ %s\n\t\t\t\tѧ�ţ� %s\n\t\t\t\t�ɼ���%d\n\n\t\t\t\t���޸�Ϊ\n\t\t\t\t", pTemp->cName, pTemp->iNumber, pTemp->Score);
				printf("\n");
				printf("\t\t\t\t������\n\t\t\t\t");
				scanf("%s", pTemp->cName);
				printf("\t\t\t\tѧ�ţ�\n\t\t\t\t");
				scanf("%s", pTemp->iNumber);
				for (int i = 0;pTemp->iNumber[i];i++)
				{
					if (48 > pTemp->iNumber[i] || pTemp->iNumber[i] > 57)
					{
						printf("\n\t������������ѧ��:");
						fflush(stdin);
						scanf("%s", pTemp->iNumber);
						i = -1;
					}
				}
				printf("\t\t\t\t�ɼ���\n\t\t\t\t");
				scanf("%d", &pTemp->Score);
				while (pTemp->Score > 100 || pTemp->Score < 0)
				{
					printf("\n\t��������������ȷ�ɼ�:");
					fflush(stdin);
					scanf("%d", &pTemp->Score);
				}
				printf("\n");
				for (int in = 1; in <= 3; in++)
				{
					Sleep(200);
					printf(".");
				}
				printf("\n\t\t\t\t�޸ĳɹ���");
				break;
			}
			pTemp = pTemp->next;
		}
		if (p == 0)
			printf("\t\t\t\tû���ҵ���Ӧ��ѧ����Ϣ��");
	}
	else
	{
		char scName[50];
		int p = 0;
		printf("\n\t\t\t\t������Ҫ�޸ĵ�ѧ������\n\t\t\t\t");
		scanf("%s", scName);
		STU* pTemp = phead;
		while (pTemp != NULL)
		{
			if (strcmp(pTemp->cName, scName) == 0)
			{
				p++;
				printf("\n\t\t\t\t��ѧ��ԭ��Ϣ���£�\n\t\t\t\t������ %s\n\t\t\t\tѧ�ţ� %s\n\t\t\t\t�ɼ���%d\n\n\t\t\t\t���޸�Ϊ��", pTemp->cName, pTemp->iNumber, pTemp->Score);
				printf("\n");
				printf("\t\t\t\t������\n\t\t\t\t");
				scanf("%s", pTemp->cName);
				printf("\t\t\t\tѧ�ţ�\n\t\t\t\t");

				scanf("%s", pTemp->iNumber);
				for (int i = 0;pTemp->iNumber[i];i++)
				{
					if (48 > pTemp->iNumber[i] || pTemp->iNumber[i] > 57)
					{
						printf("\n\t������������ѧ��:");
						fflush(stdin);
						scanf("%s", pTemp->iNumber);
						i = -1;
					}
				}
				printf("\t\t\t\t�ɼ���\n\t\t\t\t");
				scanf("%d", &pTemp->Score);
				while (pTemp->Score > 100 || pTemp->Score < 0)
				{
					printf("\n\t��������������ȷ�ɼ�:");
					fflush(stdin);
					scanf("%d", &pTemp->Score);
				}
				printf("\n");
				for (int in = 1; in <= 3; in++)
				{
					Sleep(200);
					printf(".");
				}
				printf("\n\t\t\t\t�޸ĳɹ���\n");
			}
			pTemp = pTemp->next;
		}
		if (p == 0)
			printf("\t\t\t\tû���ҵ���Ӧ��ѧ����Ϣ��");
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
	printf("Ҫ�������˵��밴�����\t\tҪ�˳������밴Esc��\n");
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
	printf("\t��Esc����������\t\t\t����������ص�¼����\n");
	char cho;
	cho = getch();
	if (cho == 0x1b)
	{
		exit(0);
	}
	FreeAll_LINK(phead);
	Backlogin();
}

void Chachong(STU* phead) //����
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
				printf("�����ظ�ѧ����Ϣ��");
				printf("\n\t\t\t\tѧ�ţ� %s\n", s->iNumber);
			}

		}
		p = p->next;
		s = p;
	}

}
void Savestu()//�ļ�����
				//��������Ϣ���浽�ļ���
{
	FILE* fp = NULL;
	//�ж������Ƿ�Ϊ��
	if (NULL == phead)
	{
		printf("û��ѧ��");
		return;
	}
	STU* ptemp = phead;
	//���ļ�
	fp = fopen("e:\\wj\\test.txt", "wb+");
	if (NULL == fp)
	{
		printf("��ʧ��");
		return;
	}
	//�����ļ�ָ��
	char strBuf[110] = { 0 };char strScore[10] = { 0 };
	while (ptemp)
	{
		//ѧ��
		strcpy(strBuf, ptemp->iNumber);
		strcat(strBuf, ".");
		//������
		strcat(strBuf, ptemp->cName);
		strcat(strBuf, ".");
		//�ɼ�
	//	itoa(ptemp->Score,strScore,10);
		sprintf(strScore, "%d", ptemp->Score);
		strcat(strBuf, strScore);
		fwrite(strBuf, 1, strlen(strBuf), fp);
		fwrite("\r\n", 1, strlen("\r\n"), fp);
		ptemp = ptemp->next;
	}
	//�ر��ļ�
	fclose(fp);
}
void Readstu()//��ȡ�ļ��е����ݵ�������
{
	FILE* fp = fopen("e:\\wj\\test.txt", "rb+");
	if (NULL == fp)
	{
		printf("��ʧ��");
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
		printf("\n\t\t\t\t\t*************ѧ������Ϣ��ѯ************\n");
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
						printf("Ҫ���ص�¼���水�����\t\tҪ�˳������밴Esc��\n");
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
						printf("\t\t\t\tѧ����Ϣ���£�\n\t\t\t\t������ %s\n\t\t\t\tѧ�ţ� %s\n\t\t\t\t�ɼ��� %d\n\t\t\t\t�γ̣� %s", pTemp->cName, pTemp->iNumber, pTemp->Score, pTemp->lesson);
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
			printf("\n\n\n\t\t\t\t\t\t����Ա��û����������ϢŶ��");
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
				printf("Ҫ���ص�¼���水�����\t\tҪ�˳������밴Esc��\n");
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
				//		               ����
				phead = Creat();
				Savestu();
				break;
			case 2:
				//	��ӡ
				Print(phead);
				break;
			case 3:
				for (int in = 1; in <= 3; in++)
				{
					Sleep(200);
					printf(".");
				}
				system("CLS");
				Head();	printf("\n");							//׷��
				printf("\t\t\t\tѧ�ţ�\n\t\t\t\t");
				scanf("%s", iNumber);
				for (int i = 0;iNumber[i];i++)
				{
					if (48 > iNumber[i] || iNumber[i] > 57)
					{
						printf("\n\t������������ѧ��:");
						fflush(stdin);
						scanf("%s", iNumber);
						i = -1;
					}
				}
				printf("\t\t\t\t������\n\t\t\t\t");
				scanf("%s", cName);
				printf("\t\t\t\t�ɼ���\n\t\t\t\t");
				scanf("%d", &Score);
				while (Score > 100 || Score < 0)
				{
					printf("\n\t��������������ȷ�ɼ�:");
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
				printf("\n\t\t\t\t��ӳɹ���");
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
				Head();	puts("");								//����
				printf("\t\t\t\t\t*************��������************\n");
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
				Head();	puts("");							//ɾ��
				printf("\t\t\t\t\t*************ɾ��ѧ����Ϣ************\n\t\t\t\t��ѡ��ɾ����ʽ��\n\t\t\t\t1)ɾ���������Ŷ�Ӧ��ѧ����\t2)ɾ��ȫ��ѧ��\n\t\t\t\t");
				char ccho;
				ccho = getche();
				while (ccho != '1' && ccho != '2')
				{
					ccho = getch();
				}
				if (ccho == '1')
				{
					int index;//Ҫɾ����ѧ�����
					printf("\n\t\t\t\t������Ҫɾ����ѧ����ţ�\n\t\t\t\t");
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
					printf("\n\t\t\t\t����գ�");
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
	printf("\t\t\t�X�T�T�T�T�T�T�T�T�T�T�T�T�j�T�T�T�T�T�T�T�T�T�T�T�T�j�T�T�T�T�T�T�T�T�T�T�T�T�j�T�T�T�T�T�T�T�T�T�T�T�T�j�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("\t\t\t�U  �ߵ���ѧ  �U  ��ѧӢ��  �U  �ߵ���ѧ  �U  ��ѧӢ��  �U  �ߵ���ѧ  �U\n");
	printf("\t\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�a�T�T�T�T�T�T�T�T�T�T�T�T�a�T�T�T�T�T�T�T�T�T�T�T�T�a�T�T�T�T�T�T�T�T�T�T�T�T�a�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	printf("\t\t\t�U  ��ɢ��ѧ  �U  ��ѧ����  �U  ��ɢ��ѧ  �U  ��ѧ����  �U  ��ɢ��ѧ  �U\n");
	printf("\t\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�a�T�T�T�T�T�T�T�T�T�T�T�T�a�T�T�T�T�T�T�T�T�T�T�T�T�a�T�T�T�T�T�T�T�T�T�T�T�T�a�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	printf("\t\t\t�U            �U            �U            �U            �U            �U\n");
	printf("\t\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�a�T�T�T�T�T�T�T�T�T�T�T�T�a�T�T�T�T�T�T�T�T�T�T�T�T�a�T�T�T�T�T�T�T�T�T�T�T�T�a�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	printf("\t\t\t�U  �������  �U  ��ѧ����  �U  �������  �U            �U  �������  �U\n");
	printf("\t\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�a�T�T�T�T�T�T�T�T�T�T�T�T�a�T�T�T�T�T�T�T�T�T�T�T�T�a�T�T�T�T�T�T�T�T�T�T�T�T�a�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	printf("\t\t\t�U            �U            �U            �U            �U            �U\n");
	printf("\t\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�a�T�T�T�T�T�T�T�T�T�T�T�T�a�T�T�T�T�T�T�T�T�T�T�T�T�a�T�T�T�T�T�T�T�T�T�T�T�T�a�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	Caozuowei();
}
int Stmenu_select()
{
	char c;
	system("cls");
	printf("\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t   �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�����T�T�T�r\n");
	printf("\t\t\t\t   ��         ѧ����Ϣ����ϵͳ     ѧ����        ��\n");
	printf("\t\t\t\t   �t�T�T�T�����T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s\n");
	printf("\t\t\t\t   ����������������������������������������������������������������������������������������-��\n");
	printf("\t\t\t\t   ��                                            ��\n");
	printf("\t\t\t\t   �� 1. ��ѯ�α�                    2. ��ѯ�ɼ� ��\n");
	printf("\t\t\t\t   ��                                            ��\n");
	printf("\t\t\t\t   �� 3. �γ�ѡ��                    0. �˳����� ��\n");
	printf("\t\t\t\t   ��                                            ��\n");
	printf("\t\t\t\t   ��������������������������������������������������������������������������������������������\n");
	printf("\t\t\t\t\t\t  ����ѡ��(0-3):");
	c = getche();

	while (c < '0' || c > '3')
	{
		system("cls");
		printf("\n\n\n\n\n\n\n\n");
		printf("\t\t\t\t   �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�����T�T�T�r\n");
		printf("\t\t\t\t   ��         ѧ����Ϣ����ϵͳ     ѧ����        ��\n");
		printf("\t\t\t\t   �t�T�T�T�����T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s\n");
		printf("\t\t\t\t   ����������������������������������������������������������������������������������������-��\n");
		printf("\t\t\t\t   ��                                            ��\n");
		printf("\t\t\t\t   �� 1. ��ѯ�α�                    2. ��ѯ�ɼ� ��\n");
		printf("\t\t\t\t   ��                                            ��\n");
		printf("\t\t\t\t   �� 3. �γ�ѡ��                    0. �˳����� ��\n");
		printf("\t\t\t\t   ��                                            ��\n");
		printf("\t\t\t\t   ��������������������������������������������������������������������������������������������\n");
		printf("\t\t\t\t\t  ��������ѡ��ѡ��(0-3):");
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
		printf("\t\t\t\t   �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�����T�T�T�r\n");
		printf("\t\t\t\t   ��            ѧ���γ�ѡ�޽���             ��\n");
		printf("\t\t\t\t   �t�T�T�T�����T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s\n");
		printf("\t\t\t\t   ��������������������������������������������������������������������������������������\n");
		printf("\t\t\t\t   ��                                         ��\n");
		printf("\t\t\t\t   �� 1. Ӣ�����                 2. Ӣ��д�� ��\n");
		printf("\t\t\t\t   ��                                         ��\n");
		printf("\t\t\t\t   �� 3. Ӣ������                 4. Ӣ�ļ��� ��\n");
		printf("\t\t\t\t   ��                                         ��\n");
		printf("\t\t\t\t   ��������������������������������������������������������������������������������������\n");
		printf("\t\t\t\t\t\t  ����ѡ��(1-4):");
		c = getche();
		while (c < '1' || c > '4')
		{
			system("cls");
			printf("\n\n\n\n\n\n\n\n");
			printf("\t\t\t\t   �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�����T�T�T�r\n");
			printf("\t\t\t\t   ��            ѧ���γ�ѡ�޽���             ��\n");
			printf("\t\t\t\t   �t�T�T�T�����T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s\n");
			printf("\t\t\t\t   ��������������������������������������������������������������������������������������\n");
			printf("\t\t\t\t   ��                                         ��\n");
			printf("\t\t\t\t   �� 1. Ӣ�����                 2. Ӣ��д�� ��\n");
			printf("\t\t\t\t   ��                                         ��\n");
			printf("\t\t\t\t   �� 3. Ӣ������                 4. Ӣ�ļ��� ��\n");
			printf("\t\t\t\t   ��                                         ��\n");
			printf("\t\t\t\t   ��������������������������������������������������������������������������������������\n");
			printf("\t\t\t\t\t      ��������ѡ��ѡ��(1-4):");
			fflush(stdin);
			c = getche();
		}
		if (c == '1')
		{
			strcpy(l, "Ӣ�����");
			printf("ѡ��ɹ���");
			break;
		}
		if (c == '2')
		{
			strcpy(l, "Ӣ��д��");
			printf("ѡ��ɹ���");
			break;
		}
		if (c == '3')
		{
			strcpy(l, "Ӣ������");
			printf("ѡ��ɹ���");
			break;
		}
		if (c == '4')
		{
			strcpy(l, "Ӣ�����");
			printf("ѡ��ɹ���");
			break;
		}
	}
	p = l;
	return p;
}
void save_lesson(char* l)
{
	FILE* f = NULL;
	//���ļ�
	f = fopen("e:\\wj\\test1.txt", "wt");
	if (f == NULL)
	{
		printf("��������");
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
		printf("��������");
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
