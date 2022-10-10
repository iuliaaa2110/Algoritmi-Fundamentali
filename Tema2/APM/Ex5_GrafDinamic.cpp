#include<iostream>
#include<fstream>
#include<vector>
#include<queue>

using namespace std;

ifstream f("apm.in");
ofstream g("apm.out");

vector< vector< pair<int, int> > >w;   //first = vecinul, second = valoarea muchiei
vector< vector< pair<int, int> > >apm;
priority_queue< pair<int, pair<int,int> >, vector< pair<int, pair<int,int> > >, greater< pair<int, pair<int,int> > > >h; //first valoarea, second.first =x, second.second = y


int s,i,ya,xa,ca,mx,my;

bool b[200001], b2[200001] ; //marchez cand plec din nod

void prim (int x)
{
    for(i = 0; i < w[x].size(); i++)
        if(!b[w[x][i].first])
            h.push(make_pair(w[x][i].second, make_pair(x, w[x][i].first)));

    b[x] = 1;

    while ( !h.empty() && b[h.top().second.second])
        h.pop();

    if(!h.empty())
    {
        int val = h.top().first, xn = h.top().second.first, yn = h.top().second.second;
        h.pop();

        apm[xn].push_back(make_pair(yn, val));
        s += val;

        prim(yn);
    }

}

//
int cmciclu(int x, int cmax)    //dfs
{
    b2[x] = 1;
    cout<<x<<" ";
    for(i = 0; i < apm[x].size(); i++)
    {

        if( !b2[apm[x][i].first] )
        {
            if(apm[x][i].second > cmax)
            {
                cmax = apm[x][i].second;
                mx = x;
                my = apm[x][i].first;
            }

            if( apm[x][i].first == ya )
                return cmax;

            return cmciclu(apm[x][i].first,cmax);
        }
    }
}


int main()
{
    //Prim:

    int n, m, x, y, cost;

    f >> n >> m;

    w.resize(n+1);
    apm.resize(n+1);

    for(i = 0; i < m; i++)
    {
        f>>x>>y>>cost;

        w[x].push_back(make_pair(y,cost));
        w[y].push_back(make_pair(x,cost));
    }

    prim(1);

    g<<"Muchiile apcm-ului in G:"<<'\n'<<apm.size()<<'\n';

    for( i = 1; i <= n ;i++)
        for(int j = 0; j < apm[i].size(); j++)
            g<<i<<" "<<apm[i][j].first<< '\n';

    g<<"Costul apcm-ului:"<<'\n'<<s<<'\n';

    //GrafDinamic:

    f>>xa>>ya>>ca;

    int cm = cmciclu(xa,0);

    g<<'\n'<<"a) Muchia de cost maxim din ciclul inchis de "<<xa<<" "<<ya<<" este muchia "<<mx<<" "<<my<<" si are valoarea "<<cm<<'\n';

    //b) O(1)

    g<<"b) Dupa adaugarea muchiei apcm are costul "<<s - cm + ca;


    return 0;
}
