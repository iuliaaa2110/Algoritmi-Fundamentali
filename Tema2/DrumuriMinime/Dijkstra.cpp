#include<iostream>
#include<fstream>
#include<vector>
#include<queue>

using namespace std;

ifstream f("grafpond.in");
ofstream g("grafpond.out");

int n,m,s;

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
        int x,y,c;

        f>>x>>y>>c;
        w[x].push_back(make_pair(y,c));
        w[y].push_back(make_pair(x,c));
    }

    int k,varf;
    cout<<"k= ";
    cin>>k;

    puncte.resize(k + 1);

    cout<<"puncte:";
    for(int i = 0; i < k; i++)
    {
        int x;

        cin>>x;
        puncte[x] = 1;
    }

    cout<<"varf=";
    cin>>varf;

    dist[varf] = 0;
    t[varf] = -1;

    //cout<<h.top().first<<" "<<h.top().second<<endl;

    for(int i = 1; i <= n; i++)
    {
        if(i!=varf)
            dist[i] = INT_MAX;

        h.push(make_pair(dist[i],i));

        cout<<h.top().first<<" "<<h.top().second<<endl;

    }

    dijkstra();

    int dmin = INT_MAX, pc;

    for(int i = 1; i <= n; i++)
        if(puncte[i] &&  dist[i] < dmin)
        {
            dmin = dist[i];
            pc = i;
        }

    g<<"Cel mai apropiat punct de control este "<<pc<<'\n';
    g<<"Un lant minim este: ";

    lant_minim(pc);

    return 0;
}
