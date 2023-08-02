#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include <queue>
#include<algorithm>
#include<cstring>
using namespace std; 

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
const int max_n = 1 * 1e4 + 10;
const int max_m = 5 * 1e5 + 10;
const int max_int = 0x7fffffff;
int ans[max_n];
bool visited[max_n];
int n, m, s;

typedef int KeyType;
typedef enum { DG, DN, UDG, UDN } GraphKind;
typedef struct {
	int key;
	char others[20];
} DotNode;                       //�������Ͷ���
typedef struct ArcNode {            //��
	int index_target_dot;                     //���ĸ�����ı��
	int distance;                   //���ö���ľ���
	struct ArcNode* nextarc;	    //��һ���߽��ָ��
} ArcNode;
typedef struct VNode {				//ͷ��㼰���������Ͷ���
	DotNode data;       	        //������Ϣ
	ArcNode* firstarc;      	    //ָ���һ����
} VNode, AdjList[max_n];
typedef  struct ALGraph 
{                   
	AdjList dots;     	            //ͷ�������
	int vexnum, arcnum;   	        //������������
	GraphKind  kind;                //ͼ������
} ALGraph, * ALGraphPointer;
ALGraph G ;
DotNode V[max_n];
KeyType VR[max_m][3];
int CreateGraph(ALGraph& m_G, DotNode m_V[], KeyType m_VR[][3])
{
    m_G.vexnum = 0;                                           //ͼ�ıߺͶ�������ֵΪ0
    m_G.arcnum = 0;
    for (int i = 1; m_V[i].key != -1; i++)
    {
        //for (int j = 0; j < i; j++)
        //{
        //    if (m_V[j].key == m_V[i].key) return ERROR;         //�ؼ����ظ�
        //}
        m_G.vexnum++;
        //if (m_G.vexnum > MAX_VERTEX_NUM)return ERROR;         //�����������ֵ
        m_G.dots[i].firstarc = NULL;
        m_G.dots[i].data.key = m_V[i].key;
        //strcpy(m_G.dots[i].data.others, m_V[i].others);
    }
    for (int i = 1; m_VR[i][0] != -1; i++)
    {
        int n1 = m_VR[i][0], n2 = m_VR[i][1];
        //for (; n1 < m_G.vexnum; n1++)
        //{
        //    if (m_G.dots[n1].data.key == m_VR[i][0])
        //    {
        //        break;                                      //�ҵ��˶���
        //    }
        //}
        ////if (n1 == m_G.vexnum) return ERROR;
        //for (; n2 < m_G.vexnum; n2++)
        //{
        //    if (m_G.dots[n2].data.key == m_VR[i][1])
        //    {
        //        break;                                      //�ҵ��˶���
        //    }
        //}
        //if (n2 == m_G.vexnum) return ERROR;

        m_G.arcnum++;
        //if (m_G.arcnum > 100)return ERROR;
        if (n1 == n2)continue;
        int judge = 1;
        
        if (judge == 0)continue;
        if (!m_G.dots[n1].firstarc)                       //û�б�����
        {
            m_G.dots[n1].firstarc = (ArcNode*)malloc(sizeof(ArcNode));
            m_G.dots[n1].firstarc->nextarc = NULL;
            m_G.dots[n1].firstarc->index_target_dot = n2;
            m_G.dots[n1].firstarc->distance = m_VR[i][2];
        }
        else                                                //�б�����
        {
            for (ArcNode* this_arc = m_G.dots[n1].firstarc; this_arc; this_arc = this_arc->nextarc)
            {
                if (this_arc->index_target_dot == n2)       //�ظ���
                {
                    if (this_arc->distance > m_VR[i][2])
                    {
                        this_arc->distance = m_VR[i][2];
                    }
                    judge = 0;
                    break;
                }
            }
            ArcNode* temp = m_G.dots[n1].firstarc;
            while (temp)
            {
                if (temp->index_target_dot == n2)
                {
                    judge = 0;
                    break;                                  //�������Գɻ�
                }
                temp = temp->nextarc;
            }
            if (judge == 1)
            {
                temp = (ArcNode*)malloc(sizeof(ArcNode));
                temp->nextarc = m_G.dots[n1].firstarc;
                temp->index_target_dot = n2;
                temp->distance = m_VR[i][2];
                m_G.dots[n1].firstarc = temp;
            }
        }
        //if (judge == 1)
        //{
        //    if (!m_G.dots[n2].firstarc)                       //û�б�����
        //    {
        //        m_G.dots[n2].firstarc = (ArcNode*)malloc(sizeof(ArcNode));
        //        m_G.dots[n2].firstarc->nextarc = NULL;
        //        m_G.dots[n2].firstarc->index_target_dot = n1;
        //        m_G.dots[n2].firstarc->distance = m_VR[i][2];
        //    }
        //    else                                                //�б�����
        //    {
        //        ArcNode* temp = m_G.dots[n2].firstarc;
        //        while (temp)
        //        {
        //            if (n1 == n2)
        //            {
        //                judge = 0;
        //                break;                                  //�������Գɻ�
        //            }
        //            temp = temp->nextarc;
        //        }
        //        if (judge == 1)
        //        {
        //            temp = (ArcNode*)malloc(sizeof(ArcNode));
        //            temp->nextarc = m_G.dots[n2].firstarc;
        //            temp->index_target_dot = n1;
        //            temp->distance = m_VR[i][2];
        //            m_G.dots[n2].firstarc = temp;
        //        }
        //    }
        //}
    }
    return 1;
}
int main() 
{
	//memset(ans, max_int, sizeof(ans));
	//memset(visited, false, sizeof(visited));
    cin >> n >> m >> s;
    for (int i = 1; i <= n; i++)
    {
        ans[i] = max_int;
        visited[i] = false;
    }
    for (int i = 1; i <= n; i++)
    {
        V[i].key = i;
    }
    V[n+1].key = -1 , strcpy(V[n+1].others ,"null");
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &VR[i][0] ,& VR[i][1], & VR[i][2]);
    }
    VR[m+1][0] = VR[m+1][1] = VR[m+1][2] = -1;
    CreateGraph(G, V, VR);
    ans[s] = 0;
    while (!visited[s])
    {
        visited[s] = true;
        for (ArcNode* this_arc = G.dots[s].firstarc; this_arc; this_arc = this_arc->nextarc)
        {
            ans[this_arc->index_target_dot] = min(ans[this_arc->index_target_dot], ans[s] + this_arc->distance);
        }
        int my_min = max_int;
        for (int i = 1; i <= n; i++)
        {
            if (!visited[i] && ans[i] < my_min)
            {
                my_min = ans[i];
                s = i;
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        cout << ans[i] << " ";
    }
	return 0;
}