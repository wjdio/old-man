#include<iostream>
using namespace std;
#include<string>
#define MaxValue 65535
typedef struct 
{
	int vertnum;
	int Edgenum;
	string Vert[30];
	int edge[30][30];
	char kind;
}Mygraph;

int locate(Mygraph* g, string c) 
{
	for (int i = 0; i < g->vertnum; i++)
	{
		if (g->Vert[i] == c) 
	    {
			return i;
		}
	}
	cout << "输入的点不存在请从新输入";
	return -1;
}

void Init(Mygraph* G)
{
	cout << "请输入图的顶点数:";
	cin >> G->vertnum;
	for (int i = 0; i < G->vertnum; i++) 
	{
		cout << "请输入第" << i + 1 << "个顶点：";
		cin >> G->Vert[i];
	}
	cout << "请输入图的边数: ";
	cin >> G->Edgenum; 
	while (G->Edgenum > (G->vertnum * (G->vertnum - 1)) / 2 || G->Edgenum < G->vertnum - 1) 
	{
		cout << "边数与顶点数不匹配请重新输入";
		cin >> G->Edgenum;
	}
	for (int i = 0; i < G->vertnum; i++)
	{
		for (int j = 0; j < G->vertnum; j++)
		{
			if (i == j)
			{
				G->edge[i][j] = 0;
			}
			else
			{
				G->edge[i][j] = MaxValue;
			}
		}
	}
	for (int k = 0; k < G->Edgenum; k++)
	{
		cout << "请输入第"<<k+1<<"条边的两个顶点以及权值：";
		string v1, v2;
		int weight;
		cin >> v1 >> v2 >> weight;
		int i = locate(G, v1);
		int j = locate(G, v2);
		while (i == -1 || j == -1) 
		{
			cout << "输入的顶点有误，请重新输入";
			cin >> v1 >> v2 >> weight;
			int i = locate(G, v1);
			int j = locate(G, v2);
		}
		G->edge[i][j] = weight;
		if (G->kind == '0')
		{
			G->edge[j][i] = G->edge[i][j];
		}
	}
}

void OutGraph(Mygraph* GM)
{
	int i, j;
	for (j = 0; j < GM->vertnum; j++)
	{
		cout << "\t" << GM->Vert[j];
	}
	cout << "\n";

	for (i = 0; i < GM->vertnum; i++)
	{
		cout << GM->Vert[i];
		for (j = 0; j < GM->vertnum; j++)
		{
			if (GM->edge[i][j] == 65535)
			{
				printf("\tM");  //以M表示无穷大
			}
			else
			{
				printf("\t%d", GM->edge[i][j]);  //输出边的权值
			}
		}
		cout << "\n";
	}
}

void Prim(Mygraph *g) 
{
	int min,sum;
	int weights[100];//权值数组
	string temp[100];//暂存顶点数组
	int i,j,k;
	sum = 0;
	for (i = 1; i < g->vertnum; i++) 
	{
		weights[i] = g->edge[0][i];
		if (weights[i] == MaxValue) 
		{
			temp[i] = -1;
		}
		else 
		{
			temp[i] = g->Vert[0];
		}
	}//存储一行中所有邻接点边的权值
	temp[0] = "0";//将该点即为已访问
	weights[0] = MaxValue;//初始化第一个权值
	for (i = 1; i < g->vertnum; i++) 
	{
		min = weights[0];
		k = 0;
		for (int j = 1; j < g->vertnum; j++) 
		{
			if (weights[j] < min && temp[j] !="0")
			{
				min = weights[j];
				k = j;
			}
		}//找到权值最小的那一条边
		sum += min;//将该权值累加
		cout << "(" << temp[k] << "," << g->Vert[k] << ")" << " ";//打印该条路径
		temp[k] = "0";//记为已访问
		weights[k] = MaxValue;

		for (j = 0; j < g->vertnum; j++) 
		{
			if (g->edge[k][j] < weights[j] && temp[j] != "0")
			{
				weights[j] = g->edge[k][j];
				temp[j] = g->Vert[k];
			}
		}//以新顶点为开始，继续查找
	}
	printf("\n最小生成树的总权值为:%d\n", sum);//打印最后的权值累加和
}
void menu() 
{
	cout << "                       ******************************************************" << endl;
	cout << "                       ******************************************************" << endl;
	cout << "                       **                找出最省经济的方案                **" << endl;
	cout << "                       ******************************************************" << endl;
	cout << "                       ******************************************************" << endl;
}
int main() 
{
	menu();
	Mygraph G;
	cout << "找出最省经济的方案"<<endl;
	cout << "请输入图的类型0或1: " << endl;
	cin >> G.kind;
	while (G.kind !='0' && G.kind != '1')
	{
		cout << "输入的图的类型有误请重新输入";
		cin >> G.kind;
	}
	Init(&G);
	cout << "以下是该城市网的模拟邻接矩阵" << endl;
	OutGraph(&G);
	cout << "经济效益最好的方案是：";
	Prim(&G);
	return 0;
}
}

