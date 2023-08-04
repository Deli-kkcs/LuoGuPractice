#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<math.h>

#include<vector>
#include<stack>
#include<queue>
#include<map>
using namespace std;
const int max_n = 1 * 1e3 + 10;
int index_station[max_n], t[max_n];
int topo[max_n][max_n], level[max_n];// topo[i][j] == 1 �ȼ��� j ����� i 
bool station[max_n], cut[max_n]; //�жϱ�վ���޻�ͣ�����Ƿ��Ѿ�ɾ�������

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        memset(station, false, sizeof(station)); //ÿ����·��ʼ��
        int count_stopped_station;
        scanf("%d", &count_stopped_station);
        for (int j = 1; j <= count_stopped_station; j++)
        {
            scanf("%d", &index_station[j]);
            station[index_station[j]] = true;//��ȡͣ������
        }
        for (int j = index_station[1]; j <= index_station[count_stopped_station]; j++) //ö��ÿ��վ��
        {
            if (station[j])//�л�ͣ����վ��
            {
                continue;
            }
            //else û�л�ͣ����վ��
            for (int k = 1; k <= count_stopped_station; k++)
            {
                if (topo[j][index_station[k]] == 0)
                {
                    topo[j][index_station[k]] = 1;
                    level[index_station[k]]++;
                }
            }
        }
    }

    memset(cut, false, sizeof(cut));
    int ans = 0, count_top = 0;

    do
    {
        count_top = 0;
        for (int i = 1; i <= n; i++)
        {
            if (level[i] == 0 && !cut[i])
            {
                cut[i] = true;
                count_top++;
                t[count_top] = i;
            }
        }
        for (int i = 1; i <= count_top; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (topo[t[i]][j] == 1)
                {
                    topo[t[i]][j] = 0;
                    level[j]--;
                }
            }
        }
        ans++;
    } while (count_top != 0);

    cout << ans - 1 << endl; // ans ����һ��
    return 0;
}