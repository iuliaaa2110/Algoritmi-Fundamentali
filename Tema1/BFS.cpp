#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream f("BFS.in");
ofstream g("bfs.out");

int N, M, S;

vector < vector <int> > w;   //retin intr un vector de vectori. Nodul i are vecinii  v[i][0], v[i][1] ...
int c[100001];
queue <int> q;

void BFS(int x)
{
    q.push(x);

    while(!q.empty())
    {
        int x = q.front();
        q.pop();

        for(int i = 0; i < w[x].size(); i ++)
        {
            if(c[ w[x][i] ] == 0 && w[x][i] != S)
            {
                c[ w[x][i] ] = c[x] + 1;
                q.push(w[x][i]);
            }
        }
    }

}

int main()
{
    int x, y, i, j;

    f >> N >> M >> S;

    w.resize(N + 1);

    for (int i = 0; i < M; i++)
    {
        f >> x >> y;
        if(x != y)
            w[x].push_back(y);
    }

    BFS(S);

    for (int i = 1; i <= N; i++)
    {

        if (c[i] == 0 && i != S)
            g << -1 << " ";
        else
            g << c[i] << " ";
    }

    return 0;
}
