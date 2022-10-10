#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<limits.h>

using namespace std;

ifstream f("catun.in");
ofstream g("catun.out");

int n,m,s,k;

vector< vector< pair<int,int> > >w; //first = vecinul, second = val muchiei
vector<bool>puncte; //true => i este punct de control <=> fortareata
vector<int>dist;
vector<int>ft; //pt fiecare nod, cea mai apropiata fortareata

priority_queue< pair<int,int>, vector< pair<int,int> >, greater< pair<int,int> > >h; //first = distanta minima pana in acest punct, second = nodul

void dijkstra()
{
    int x = h.top().second;
    h.pop();

    for(int i = 0; i < w[x].size(); i++)
    {
        int y = w[x][i].first, val_muchie = w[x][i].second;

        if(dist[x] + val_muchie < dist[y])
        {
            ft[y] = ft[x];
            dist[y] = dist[x] + val_muchie;
            h.push(make_pair(dist[y],y));
        }
        else
            if( dist[x] + val_muchie == dist[y])
                if(ft[x] < ft[y])
                    ft[y] = ft[x];
    }

    if(!h.empty())
        dijkstra();

}

int main ()
{

    f>>n>>m>>k;

    w.resize(n + 1);
    dist.resize(n + 1);
    ft.resize(n + 1);
    puncte.resize(n + 1);

    for(int i = 0; i < k ; i++)
    {
        int x;

        f>>x;
        ft[x] = x;
        puncte[x] = 1;
        dist[x] = 0;
        h.push(make_pair(dist[x],x));
    }

    for(int i = 0; i < m; i++)
    {
        int x,y,c;

        f>>x>>y>>c;
        w[x].push_back(make_pair(y,c));
        w[y].push_back(make_pair(x,c));
    }

    for(int i = 1; i <= n; i++)
        if(!puncte[i])
        {
            dist[i] = INT_MAX;
            h.push(make_pair(dist[i],i));
        }

    dijkstra();

    for(int i = 1; i <= n; i++)
        if(puncte[i])
            g<<0<<" ";
        else
            g<<ft[i]<<" ";

    return 0;
}
