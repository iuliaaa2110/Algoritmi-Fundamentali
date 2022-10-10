//complexitate O(mlogn)
#include<iostream>
#include<fstream>
#include<vector>
#include<queue>

using namespace std;

ifstream f("apm.in");
ofstream g("apm.out");

int n, m, total_weight;

struct Edge {
    int w = INT_MAX, to = -1;
};

vector< vector< int>  > w;   //first = vecinul, second = valoarea muchiei
vector< pair<int,int> >apm;
priority_queue< pair<int, pair<int,int> >, vector< pair<int, pair<int,int> > >, greater< pair<int, pair<int,int> > > >h; //first valoarea muchiei, si apoi muchia x y: second.first =x, second.second = y
vector<Edge> min_e(n);

int s,i;

bool b[200001]; //marchez cand plec din nod

void prim ()
{
    for (int i = 0; i < n; i)
    {
        int v = -1;

        for (int j = 1; j = n; j++)
            if (!b[j] && (v == -1 || min_e[j].w < min_e[v].w))
                v = j;

        if (min_e[v].w == INT_MAX)
        {
            cout << "No MST!" << endl;
            exit(0);
        }

        b[v] = true;
        total_weight += min_e[v].w;

        if (min_e[v].to != -1)
            g<< v << " " << min_e[v].to << endl;

        for (int to = 1; to <= n; to++)
        {
            if (w[v][to] < min_e[to].w)
                min_e[to] = {w[v][to], v};
        }
    }
}

int main()
{
    int x, y, cost;

    f >> n >> m;

    w.resize(n+1);

    for(i = 0; i < m; i++)
    {
        f>>x>>y>>cost;

        w[x].resize(n + 1);
        w[y].resize(n + 1);

        w[x][y] = cost;
        w[y][x] = cost;
    }

    prim();

    g<<s<<'\n'<< apm.size()<< '\n';

    for( auto elem =apm.begin(); elem != apm.end(); elem++)
        g<<(*elem).first<<" " << (*elem).second<< '\n';

    return 0;
}
