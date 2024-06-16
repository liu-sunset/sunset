#define  _CRT_SECURE_NO_WARNINGS
#include "home.h"
int row;
int col;
int rows;
int cols;
int bomb;
extern  char musics[50][50];
extern char stopmusics[50][50];
extern int musicn;
void menu()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
	printf("\t\t    *******   1:开始  ********\n");
	printf("\t\t    *******   0:退出  ********\n");
	printf("\t\t    *******  -1:清屏  ********\n");
	printf("\t\t    ***********青铜***********\n");
	printf("\t\t    ***********黄金***********\n");
	printf("\t\t    ***********星耀***********\n");
	printf("\t\t    ***********王者***********\n");
	printf("******1:暮色回响**2:天若有情**3:如果可以**4:向阳生长**5:(一首钢琴曲)**6:记忆博物馆******\n");
}
void initialize(char arr[40][40], int h, int l, char mod)
{
	int i, j;
	for(i=0;i<h;i++)
		for (j = 0; j < l; j++)
		{
			arr[i][j] = mod;
		}
}
void display(char arr[40][40], int h, int l)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
	printf("------------------------display------------------------\n");
	int i, j;
	printf("   ");
	for (i = 1; i <= l; i++)
	{
		printf("%d", i);
		if (i < 10)
			printf("  ");
		else
			printf(" ");
	}
	printf("\n\n");
	for (i = 1; i <= h; i++)
	{
		printf("%d", i);
		if (i < 10)
			printf("  ");
		else
			printf(" ");
		for (j = 1; j <= l; j++)
		{
			printf("%c  ", arr[i][j]);
		}
		printf("\n");
	}	
	printf("------------------------display------------------------\n");
}
void Layout(char arr[40][40])
{
	int count = bomb;
	while(count)
	{
	int x = rand() % row + 1;
	int y = rand() % col + 1;
	
		if (arr[x][y] == '0')
		{
			arr[x][y] = '1';
			count--;
		}
	}
}
char num(char arr[40][40], int x, int y)
{
	int n = 48;
	int i, j;
	for (i = -1; i <= 1; i++)
	{
		for (j = -1; j <= 1; j++)
		{
			if (arr[x + i][y + j] == '1')
				n++;
		}
			
	}
	return n;
	
}

int outcome(char arr[40][40])
{
	int n = 0;
	int i, j;
	for (i = 1; i <= row; i++)
		for (j = 1; j <= col; j++)
		{
			if (arr[i][j] =='*'||arr[i][j]=='&')
				n++;
		}
	return n;
}
void mark(char mail[40][40],int a,int b)
{
	mail[a][b] = '&';
}

void clear_input_buffer() 
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void coordinate(char mine[40][40], char mail[40][40])
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int end;//判断是要找炸弹还是标记炸弹
	int come = 0;
	int a, b;//拆雷坐标
	int c, d;//标记坐标
	int flagbomb = 0;
	int flagwin = 0;
	while (1)
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
		come = 0;
		printf("1：拆雷  0：标记雷 ——功能选择->");
		scanf("%d", &end);
		clear_input_buffer();
		if (end == 1)
		{
			while (1)
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
				printf("请输入坐标->");
				scanf("%d%d", &a, &b);
				clear_input_buffer();
				printf("\n\n");
				if (a > row || a <= 0 || b > col || b <= 0)
				{
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
					printf("\t\t\t  坐标不合法！\n\a");
				}
				else
				{
					if (mail[a][b] != '*'&&mail[a][b]!='&')
					{
						SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
						printf("\n\n\t\t\t该坐标已经排查过了！请重新选择！\a\n\n");
					}
					else
					{
						if (mine[a][b] == '1')
						{
							mail[a][b] = '@';
							SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
							printf("\n\t\t\tgame over!踩雷了！\n");
							flagbomb = 1;
							display(mail, row, col);
							printf("\n\n");
							display(mine, row, col);
							break;
						}
						else
						{
							char time = num(mine, a, b);
							mail[a][b] = time;
							display(mail, row, col);
							come = outcome(mail);
							if (come == bomb)
							{
								display(mine, row, col);
								float x, y, a;
								mciSendStringA(stopmusics[musicn - 1], 0, 0, 0);
								mciSendStringA("play vectory.mp3 wait", 0, 0, 0);
								for (y = 1.5f; y > -1; y -= 0.1f)
								{
									for (x = -1.5f; x < 1.5f; x += 0.05f)
									{
										a = x * x + y * y - 1;
										if (a * a * a - x * x * y * y * y < 0.0f)
										{
											SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
											printf("*");
										}

										else
											printf(" ");
									}
									Sleep(100);
									printf("\n");
								}

								printf("\t\t\t  恭喜胜利！\n\n\n");
								flagwin = 1;
								break;
							}
							break;
						}
						
					}
				}
			}
		}
		else if (end == 0)
		{
			printf("请输入要标记的坐标->");
			scanf("%d%d", &c, &d);
			clear_input_buffer();
			mark(mail, c, d);
			display(mail, row, col);
		}
		else
		{

			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			printf("\n\n\t\t\t  输入错误! \a\n");
		}
		if (flagbomb == 1)
			break;
		
		if (flagwin == 1)
			break;
	}
}
void rules()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	printf("\t\t\t          \t\t    游戏规则\n\t\t\t\t本游戏不存在区域爆炸，踩雷即死（@是雷的标志 &是你标记的雷）");
	printf("\n\t\t\t游戏结束最后的表格中0为非雷，1是布置的雷(其他的懒得称述自己看吧）\n\t\t\t\t\t\t你有6秒的时间阅读\n");
}
void level()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	while (1)
	{
		char liu[10] = { '\0' };
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
		printf("请选择难易程度->");
		scanf("%s", liu);
		if (strcmp(liu, "黄金") == 0)
		{
			row = 9; col = 9;
			rows = row + 2; cols = col + 2;
			bomb = 24;
			break;
		}
		else if (strcmp(liu, "星耀") == 0)
		{
			row = 16; col = 16;
			rows = row + 2; cols = col + 2;
			bomb = 45;
			break;
		}
		else if (strcmp(liu, "王者") == 0)
		{
			row = 16; col = 30;
			rows = row + 2; cols = col + 2;
			bomb = 120;
			break;
		}
		else if (strcmp(liu, "青铜") == 0)
		{
			row = 5; col = 5;
			rows = row + 2; cols = col + 2;
			bomb = 7;
			break;
		}
		else
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			printf("\t\t\t  难度选择错误!\n\n\a");
		}
	}
	
}


void game()
{
	mciSendStringA(musics[musicn-1], 0, 0, 0);
	rules();
	Sleep(6000);
	level();
	char mine[40][40] = { '0' };
	char mail[40][40] = { '*' };
	initialize(mine, rows, cols, '0');
	initialize(mail, rows, cols, '*');
	display(mail, row, col);
	Layout(mine);
	coordinate(mine,mail);
}