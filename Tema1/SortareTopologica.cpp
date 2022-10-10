#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

ifstream f("sortaret.in");
ofstream g("sortaret.out");

vector< vector<int> > w;//v[i] are vecinii v[i][0], v[i][1] ..
bool b[100002];    //1 = vizitat, 0 = nevizitat

void DFS(int x)
{
    b[x] = 1;

    for(int i = 0; i < w[x].size(); i ++)
        if(!b[ w[x][i] ])
            DFS(w[x][i]);

    g<<x<<" ";

}
int main()
{

    int n, m, i, c = 0;

    f >> n >> m;

    w.resize(n + 2);

    for(i = 1; i <= m; i++)
    {
        int x, y;

        f >> x >> y;

        w[y].push_back(x);
    }

    for(i = 1; i <= n; i++)
        if(b[i] == 0)
            DFS(i);

    return 0;

}
