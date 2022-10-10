#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

vector< vector<int> > w;//v[i] are vecinii v[i][0], v[i][1] ..
bool b[100001];    //1 = vizitat, 0 = nevizitat

void DFS(int x,int c)
{
    b[x] = 1;

    for(int i = 0; i < w[x].size(); i ++)
        if(!b[ w[x][i] ])
            DFS(w[x][i], c);
}
int main()
{
    ifstream f("dfs.in");
    ofstream g("dfs.out");

    int n, m, i, c = 0;

    f >> n >> m;

    w.resize(100001);

    for(i = 1; i <= m; i++)
    {
        int x, y;

        f >> x >> y;

        w[x].push_back(y);
        w[y].push_back(x);
    }

    for(i = 1; i <= n; i++)
    {
        if(b[i] == 0)
        {
            c++;
            DFS(i, c);
        }
    }

    g<<c;

}
