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


int s,ya,xa,ca,mx,my,cm;

bool b[201], b2[201] ; //marchez cand plec din nod

void prim (int x)
{
    for(int i = 0; i < w[x].size(); i++)
        if(!b[w[x][i].first])
            h.push(make_pair(w[x][i].second, make_pair(x, w[x][i].first)));

    b[x] = 1;

    while ( !h.empty() && b[h.top().second.second]) //se poate sa mi fi ramas niste muchii care acum nu mai sunt disponibile
        h.pop();    //nu mai am voie sa ma duc intr un element din care la un moment dat am plecat.
                    //asa ca elemin muchiile cu directie catre elementele marcate in b, ramase urcate in priority queue de dinainte sa fi intrat in prim cu elementul respectiv

    if(!h.empty())
    {
        int val = h.top().first, xn = h.top().second.first, yn = h.top().second.second;
        h.pop();

        apm[xn].push_back(make_pair(yn, val));
        apm[yn].push_back(make_pair(xn, val));

        s += val;

        prim(yn);
    }

}

//
void cmciclu(int x, int cmax)    //aproape dfs
{
    b2[x] = 1;

    for(int i = 0; i < apm[x].size(); i++)
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
                cm = cmax;
            else
                cmciclu(apm[x][i].first,cmax);
        }
    }
}


int main()
{
    //Prim:

    int n, m, x, y, cost, n2;

    f >> n >> m;

    w.resize(n+1);
    apm.resize(n+1);

    for(int i = 0; i < m; i++)
    {
        f>>x>>y>>cost;

        w[x].push_back(make_pair(y,cost));
        w[y].push_back(make_pair(x,cost));
    }

    prim(1);

    g<<s<<'\n';

    f>> n2;

    for(int i = 1; i <= n2; i++)
    {
        f>>xa>>ya>>ca;

        cm = 0;
        cmciclu(xa,0); //gasirea muchiei maxime din ciclu: O(n+n-1) = O(2n-1)
                                // eliminand constantele ~= O(n)
        if( s - cm + ca < s)
        {
            s = s - cm + ca;

            for( auto elem =apm[mx].begin(); elem != apm[mx].end(); elem++)
                if((*elem).first == my)
                {
                    apm[mx].erase(elem);
                    break;
                }

            for( auto elem =apm[my].begin(); elem != apm[my].end(); elem++)
                if((*elem).first == mx)
                {
                    apm[my].erase(elem);
                    break;
                }

            apm[xa].push_back(make_pair(ya, ca));
            apm[ya].push_back(make_pair(xa, ca));
        }

         g<<s<<'\n';

         for(int j = 1; j <= n ;j++)
            b2[j] = 0;

    }

    return 0;
}
