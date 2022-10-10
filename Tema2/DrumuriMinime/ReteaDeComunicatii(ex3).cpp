#include<iostream>
#include<fstream>
#include<vector>
#include<queue>

using namespace std;

ifstream f("grafpond.in");
ofstream g("grafpond.out");

int n,m,s,v1,v2;

vector< vector< pair<int,int> > >w; //first = vecinul, second = val muchiei
vector<bool>puncte; //true => i este punct de control
vector<int>dist;
vector<int>t; //tatal

priority_queue< pair<int,int>, vector< pair<int,int> >, greater< pair<int,int> > >h; //first = distanta minima pana in acest punct, second = nodul

void dijkstra()
{
    int x = h.top().second;
    h.pop();
    cout<<x<<endl;


    for(int i = 0; i < w[x].size(); i++)
    {
        int y = w[x][i].first, val_muchie = w[x][i].second;

        if(dist[x] + val_muchie < dist[y])
        {
            t[y] = x;
            dist[y] = dist[x] + val_muchie;
            h.push(make_pair(dist[y],y));
        }
    }

    if(!h.empty())
        dijkstra();

}

void lant_minim(int x)
{

    if(t[x]!= -1)
        lant_minim(t[x]);

    g<<x<<" ";
}

int main ()
{

    f>>n>>m;

    w.resize(n + 1);
    dist.resize(n + 1);
    t.resize(n+1);

    for(int i = 0; i < m; i++)
    {
        int x,y,p;

        f>>x>>y>>p;
        w[x].push_back(make_pair(y,p));
        w[y].push_back(make_pair(x,p));
    }

    cin>>v1>>v2;

    dist[v1] = 0;
    t[v1] = -1;

    for(int i = 1; i <= n; i++)
    {
        if(i != v1)
            dist[i] = INT_MAX;

        h.push(make_pair(dist[i],i));
    }

    dijkstra();

    lant_minim(v2);

    return 0;
}
