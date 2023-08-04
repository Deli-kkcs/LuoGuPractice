#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<cstring>
#include<math.h>
using namespace std;

const int max_length = 1 * 1e2 + 10;
const int max_count_colored = 1 * 1e3 + 10;
int length, count_colored;
int color[max_length][max_length];
int direct1[4] = { 0,0,1,-1 }, direct2[4] = { 1,-1,0,0 };
int my_min = 0x7fffffff;
int minAtGrid[max_length][max_length];
bool notVisited[max_length][max_length];
void Search(int x, int y, int expense, int temp_color)
{
    if ((x == length) && (y == length))
    {
        my_min = min(expense, my_min);
        return;
    }
    for (int i = 0; i < 4; i++) 
    {
        int p = x + direct1[i], q = y + direct2[i];
        if (!  (  (p <= length) && (p > 0) && (q <= length) && (q > 0)  )  ) //�����߽� 
        {
            continue;
        }
        if (!notVisited[p][q])//�߹�
        {
            continue;
        }
        if ((color[x][y] == 0 && color[p][q] == 0))//��������ɫ
        {
            continue;
        }
        if (color[p][q] == 0)
        {
            if (expense + 2 < minAtGrid[p][q])//Ŀ�����ɫ�һ��Ѹ���
            {
                notVisited[p][q] = 0;
                minAtGrid[p][q] = expense + 2;
                Search(p, q, expense + 2, temp_color);
                notVisited[p][q] = 1;
                continue;
            }
            continue;
        }
            
        //Ŀ�����ɫ
        if ((temp_color == color[p][q]) && (expense < minAtGrid[p][q]))//ͬɫ�һ��Ѹ���
        {
            notVisited[p][q] = 0;
            minAtGrid[p][q] = expense;
            Search(p, q, expense, temp_color);
            notVisited[p][q] = 1;
        }
        else if ((expense + 1 < my_min) && (expense + 1 < minAtGrid[p][q])) //��ͬɫ�һ��Ѹ���      
        {
            notVisited[p][q] = 0;
            minAtGrid[p][q] = expense + 1;
            Search(p, q, expense + 1, color[p][q]);
            notVisited[p][q] = 1;
        }
    }
}
void Init()
{
    for (int i = 1; i <= length; i++)
    {
        for (int j = 1; j <= length; j++)
        {
            minAtGrid[i][j] = 0x7fffffff;
            color[i][j] = 0;
            notVisited[i][j] = 1;//1:δ��
        }
    }
}
void SetColor()
{
    for (int i = 1; i <= count_colored; i++)
    {
        int x, y, temp_color;
        scanf("%d%d%d", &x, &y, &temp_color);
        color[x][y] = temp_color + 1; //��ɫ:1��2... ��ɫ:0 
    }
}

int main()
{
    cin >> length >> count_colored;
    Init();
    SetColor();
    notVisited[1][1] = 0;
    Search(1, 1, 0, color[1][1]);
    if (my_min == 0x7fffffff)
    {
        printf("-1");
        return 0;
    }
    printf("%d", my_min);
    return 0;
}


