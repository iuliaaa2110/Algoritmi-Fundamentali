//complexitate O(mlogn)
#include<iostream>
#include<fstream>
#include<vector>
#include<queue>

using namespace std;

ifstream f("apm.in");
ofstream g("apm.out");

vector< vector< pair<int, int> > > w;   //first = vecinul, second = valoarea muchiei
vector< pair<int,int> >apm;
priority_queue< pair<int, pair<int,int> >, vector< pair<int, pair<int,int> > >, greater< pair<int, pair<int,int> > > >h; //first valoarea muchiei, si apoi muchia x y: second.first =x, second.second = y

int s,i;

bool b[200001]; //marchez cand plec din nod

void prim (int x)
{
    for(i = 0; i < w[x].size(); i++)    //ii parcurg toti vecinii
        if(!b[w[x][i].first])   //daca nu am mai plecat din vecinula asta pana acum, il urc in heap ca sa revin cu el in prim()
            h.push(make_pair(w[x][i].second, make_pair(x, w[x][i].first)));

    b[x] = 1;

    while ( !h.empty() && b[h.top().second.second]) //se poate sa mi fi ramas niste muchii care acum nu mai sunt disponibile
        h.pop();    //nu mai am voie sa ma duc intr un element din care la un moment dat am plecat.
                    //asa ca elemin muchiile cu directie catre elementele marcate in b, ramase urcate in priority queue de dinainte sa fi intrat in prim cu elementul respectiv

    if(!h.empty())
    {
        int val = h.top().first, xn = h.top().second.first, yn = h.top().second.second;
        h.pop();

        apm.push_back(make_pair(xn,yn));
        s += val;

        prim(yn);
    }

}

int main()
{
    int n, m, x, y, cost;

    f >> n >> m;

    w.resize(n+1);

    for(i = 0; i < m; i++)
    {
        f>>x>>y>>cost;

        w[x].push_back(make_pair(y,cost));
        w[y].push_back(make_pair(x,cost));
    }

    prim(1);

    g<<s<<'\n'<< apm.size()<< '\n';

    for( auto elem =apm.begin(); elem != apm.end(); elem++)
        g<<(*elem).first<<" " << (*elem).second<< '\n';

    return 0;
}
