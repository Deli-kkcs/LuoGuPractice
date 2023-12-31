#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>

using namespace std;

int i, m, n, j, k, q, p, w;
int a[1100][1100];//保存位置颜色
int f[4] = { 0,0,1,-1 }, ff[4] = { 1,-1,0,0 };//四个搜索方向，分别表示横纵坐标变化值 
int minn = 0x7fffffff;//花费最小值 
int d[1100][1100];//剪枝1：保存每个位置的花费最小值 
bool bl[1100][1100];//剪枝2：保存每个位置是否走过 

void search(int x, int y, int c, int color)
//x，y为当前位置坐标 ，c为当前所花金币，color为当前位置颜色 
{
    if ((x == n) && (y == n))//已搜到右下角，即（n,n) 
    {
        minn = min(c, minn);//用min保存到(n,n)的最小花费 
        return;
    }

    for (int i = 0; i < 4; i++)//向四个方向搜索 
    {
        int p = x + f[i], q = y + ff[i];//移动后到达的位置 
        if ((p <= n) && (p > 0) && (q <= n) && (q > 0))//判断搜索位置合法，未超出边界 
            if (bl[p][q])//判断搜索位置未走过
                if (a[x][y] || a[p][q])//判断搜索位置和当前位置至少其中一个有颜色 
                {
                    if (a[p][q] == 0)//如果搜索位置没有颜色，变色为当前颜色
                    {
                        if (c + 2 < d[p][q])//剪枝：花费2金币和原本到此的最小花费 
                        {
                            bl[p][q] = 0;//将此位置设为已走 
                            d[p][q] = c + 2, search(p, q, c + 2, color);//更新搜索位置的最小花费，递归 
                            bl[p][q] = 1;//回溯 
                        }
                    }
                    else//搜索位置有颜色 
                    {
                        if ((color == a[p][q]) && (c < d[p][q]))//搜索位置与原位置颜色相同，且花费减少
                        {
                            bl[p][q] = 0;//将此位置设为已走 
                            d[p][q] = c, search(p, q, c, color);//更新搜索位置的最小花费，递归
                            bl[p][q] = 1;//回溯 
                        }
                        else if ((c + 1 < minn) && (c + 1 < d[p][q])) //搜索位置与原位置颜色不同        
                        {
                            bl[p][q] = 0;//将此位置设为已走 
                            d[p][q] = c + 1, search(p, q, c + 1, a[p][q]);//更新搜索位置的最小花费，递归
                            bl[p][q] = 1;//回溯
                        }
                    }
                }
    }
}


int main()
{
    scanf("%d%d", &n, &m);

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++) d[i][j] = 0x7fffffff, a[i][j] = 0, bl[i][j] = 1;

    for (i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &q, &p, &w);
        a[q][p] = w + 1; //把有颜色分别存为1，2 。无色存为0 
    }

    bl[1][1] = 0;//开始位置设为走过 

    search(1, 1, 0, a[1][1]);

    if (minn == 0x7fffffff) printf("-1");//没有找到输出-1 
    else printf("%d", minn);

    return 0;
}