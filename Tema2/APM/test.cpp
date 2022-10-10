#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <climits>
#include <iomanip>
#include <queue>
#define DOUBLE_MAX  2e9 + 5;

using namespace std;
int vizitat[500000], n, m;
double  d[500000], cost;
vector<pair<double,double>> coord;
priority_queue<pair<double, int>> q;
ifstream f("retea2.in");
ofstream g("retea2.out");

double distanta(int x, int y)
{
    if(x == 0 || y == 0)
        return 0;
    double a = sqrt((coord[x].first - coord[y].first) * (coord[x].first - coord[y].first) + (coord[x].second - coord[y].second) * (coord[x].second - coord[y].second));
    return a;
}
void initializare()
{
    for(int i = 0; i <= n + m; i++)
    {
        d[i] = DOUBLE_MAX;
        vizitat[i] = 1;         //1 = nevizitat, 0 = vizitat
    }
}

int main() {
    f >> n >> m; //centrale, blocuri
    coord.emplace_back(0, 0); //ca sa inceapa indexarea de la 1 in vector
    for (int i = 0; i < n + m; i++)
    {
        int x, y;
        f >> x >> y;
        coord.emplace_back(x, y); //coord pastreaza coordonatele cladirilor
        //cout<<coord[i].first<<" "<<coord[i].second<<endl;
    }
    initializare();

    //d[0] = 0;

    for (int i = 1;i <= n; i++)     //punctele de plecare sunt centralele, cu distanta 0 pana la cea mai apropiata centr
        if (d[i] > 0)
        {
            q.push(make_pair(0, i));
            d[i] = 0;
        }






        //for(int i = 0; i <= n + m; i++)

           // cout<<vizitat[i]<<" ";
    while (!q.empty())
    {
//cout<<q.top().first<<endl;
        pair<double, int> t = q.top();
        int u = t.second;
        q.pop();
       // cout<<u<<" ";

        if (vizitat[u] == 1) {
            vizitat[u] = 0; //vizitam nodul
            cost += d[u];    //il adaugam la costul total

            for (int x = n + 1; x <= n + m; x++)
            {
                //cout<<u<<" "<<x<<" "<<distanta(u, x)<<endl;
                if (distanta(u, x) < d[x])  //daca noua distanta e mai mica, updatez si pun in coada
                {
                    d[x] = distanta(u, x);
                    cout<<u<<" "<<x<<" "<<d[x]<<" "<<endl;
                    q.push(make_pair(-d[x], x));
                }
            }
        }
    }

    g << fixed << setprecision(6) << cost;
    return 0;
}
