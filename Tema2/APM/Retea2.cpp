#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <queue>
#include <limits.h>
#include <float.h>
#include <iomanip>

using namespace std;


ifstream f("retea2.in");
ofstream g("retea2.out");

int n, m;

double s;

vector< pair<int, int> > noduri;
vector<bool> b;
vector<double> d;
priority_queue< pair<double, int>, vector< pair<double, int> >, greater < pair<double,int> > > h;

double dist_eur(int x, int y)
{
    return sqrt((noduri[x].first - noduri[y].first) * (noduri[x].first - noduri[y].first) + (noduri[x].second - noduri[y].second) * (noduri[x].second - noduri[y].second));
}

void rez()
{
    int x = h.top().second;
    d[x] = h.top().first;
    h.pop();

    if (!b[x])
    {
        b[x] = 1;
        s += d[x];

        for (int i = n + 1; i <= n + m; i++)
        {
            if (dist_eur(x, i) < d[i])
                h.push(make_pair(dist_eur(x,i), i));
        }
    }

    if(!h.empty())
        rez();
}

int main()
{

    f >> n >> m;
    noduri.resize(n + m + 1);
    b.resize(n + m + 1);
    d.resize(n + m + 1);

    for (int i = 1; i <= n + m; i++)
    {
        int x, y;

        f >> x >> y;
        noduri[i]= make_pair(x,y);
    }

    for (int i = 1; i <= n; i++)    //centralele
        h.push(make_pair(d[i], i));

    for(int i = n + 1; i <= n + m; i++) //blocurile
        d[i] = DBL_MAX;

    rez();

    g << fixed << setprecision(6) << s;
    return 0;
}
