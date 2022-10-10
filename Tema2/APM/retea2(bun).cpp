#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
#include <float.h>
#include <iomanip>

using namespace std;

ifstream f("apm.in");
ofstream g("apm.out");

int n, m, e;
double s;

vector < vector < pair<int, double> > > w; //first = vecinul, double = distanta
vector< pair<int, int> > noduri;
vector <bool> b;
vector< pair<int,int> >apm;
priority_queue< pair<double, pair<int,int> >, vector< pair<double, pair<int,int> > >, greater< pair<double, pair<int,int> > > >h;//first valoarea muchiei, si apoi muchia second.first =x, second.second = y

double distanta_euclidiana(pair<int, int> a, pair<int, int> b)
{
    return sqrt((b.first - a.first) * (b.first - a.first) + (b.second - a.second) * (b.second - a.second));
}

void prim ()
{
    int val = h.top().first, xn = h.top().second.first, yn = h.top().second.second;
    h.pop();

    if(xn!=yn)  //pt fiecare centrala am intordus o muchie de la ea la ea insasi. Nu treb sa le iau in considerare!
        apm.push_back(make_pair(xn,yn));

    s += val;

    int x = yn;

    for(int i = 0; i < w[x].size(); i++)
        if(!b[w[x][i].first])
            h.push(make_pair(w[x][i].second, make_pair(x, w[x][i].first)));

    b[x] = 1;

    while ( !h.empty() && b[h.top().second.second])
        h.pop();

    if(!h.empty())
        prim();

}



int main ()
{
    f>>n>>m>>e;

    noduri.resize(n + m + 1);
    b.resize(n + m + 1);
    w.resize(n + m + 1);

    for(int i = 1; i <= n + m; i++) //daca x <= n => x = centrala
    {
        int a,b;

        f>>a>>b;

        noduri[i] = make_pair (a,b);

    }


    for(int i = 1; i <= e; i++)
    {
        int x, y;

        f>>x>>y;

        w[x].push_back(make_pair(y,distanta_euclidiana(noduri[x],noduri[y])));
        w[y].push_back(make_pair(x,distanta_euclidiana(noduri[x],noduri[y])));

    }

    for(int i = 1; i <= n + m; i++)
    {
        for(int j = 0; j < w[i].size(); j++)
            cout<<i<<" "<<w[i][j].first<<" "<<w[i][j].second<<endl;
    }

    for(int i = 1; i <= n; i++)
        h.push(make_pair(0, make_pair(i,i)));   //pun toate centralele in coada

    prim();

    g<<fixed << setprecision(6)<< s<<endl;

    for( auto elem =apm.begin(); elem != apm.end(); elem++)
        g<<(*elem).first<<" " << (*elem).second<< '\n';

    return 0;
}
