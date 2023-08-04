#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>

using namespace std;

int i, m, n, j, k, q, p, w;
int a[1100][1100];//����λ����ɫ
int f[4] = { 0,0,1,-1 }, ff[4] = { 1,-1,0,0 };//�ĸ��������򣬷ֱ��ʾ��������仯ֵ 
int minn = 0x7fffffff;//������Сֵ 
int d[1100][1100];//��֦1������ÿ��λ�õĻ�����Сֵ 
bool bl[1100][1100];//��֦2������ÿ��λ���Ƿ��߹� 

void search(int x, int y, int c, int color)
//x��yΪ��ǰλ������ ��cΪ��ǰ������ң�colorΪ��ǰλ����ɫ 
{
    if ((x == n) && (y == n))//���ѵ����½ǣ�����n,n) 
    {
        minn = min(c, minn);//��min���浽(n,n)����С���� 
        return;
    }

    for (int i = 0; i < 4; i++)//���ĸ��������� 
    {
        int p = x + f[i], q = y + ff[i];//�ƶ��󵽴��λ�� 
        if ((p <= n) && (p > 0) && (q <= n) && (q > 0))//�ж�����λ�úϷ���δ�����߽� 
            if (bl[p][q])//�ж�����λ��δ�߹�
                if (a[x][y] || a[p][q])//�ж�����λ�ú͵�ǰλ����������һ������ɫ 
                {
                    if (a[p][q] == 0)//�������λ��û����ɫ����ɫΪ��ǰ��ɫ
                    {
                        if (c + 2 < d[p][q])//��֦������2��Һ�ԭ�����˵���С���� 
                        {
                            bl[p][q] = 0;//����λ����Ϊ���� 
                            d[p][q] = c + 2, search(p, q, c + 2, color);//��������λ�õ���С���ѣ��ݹ� 
                            bl[p][q] = 1;//���� 
                        }
                    }
                    else//����λ������ɫ 
                    {
                        if ((color == a[p][q]) && (c < d[p][q]))//����λ����ԭλ����ɫ��ͬ���һ��Ѽ���
                        {
                            bl[p][q] = 0;//����λ����Ϊ���� 
                            d[p][q] = c, search(p, q, c, color);//��������λ�õ���С���ѣ��ݹ�
                            bl[p][q] = 1;//���� 
                        }
                        else if ((c + 1 < minn) && (c + 1 < d[p][q])) //����λ����ԭλ����ɫ��ͬ        
                        {
                            bl[p][q] = 0;//����λ����Ϊ���� 
                            d[p][q] = c + 1, search(p, q, c + 1, a[p][q]);//��������λ�õ���С���ѣ��ݹ�
                            bl[p][q] = 1;//����
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
        a[q][p] = w + 1; //������ɫ�ֱ��Ϊ1��2 ����ɫ��Ϊ0 
    }

    bl[1][1] = 0;//��ʼλ����Ϊ�߹� 

    search(1, 1, 0, a[1][1]);

    if (minn == 0x7fffffff) printf("-1");//û���ҵ����-1 
    else printf("%d", minn);

    return 0;
}