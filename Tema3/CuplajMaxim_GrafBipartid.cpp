#include<iostream>
#include<fstream>
#include<queue>
#include<limits>
#include<vector>

using namespace std;

ifstream f("graf.in");
ofstream g("graf.out");

vector  <bool> multime; // 0 = prima multime, 1 = a doua multime
queue < pair <int,bool> > q;
queue <int> q2;
vector <bool> visited; // 1 == vizitat in bfs
vector < vector < pair <int, int> > > r; //first = vecinul, second = valoarea
vector <vector <int> > poz; //poz[x][y] = pozitia lui y in lista de vecini ai lui x
vector<int> parent;

int n, m, i, j, s, t;

void bfs(int x)   //separ nodurile in cele doua multimi
{
    q.push(make_pair(x, 0));

    while(!q.empty())
    {
        int x = q.front().first;
        bool mx = q.front().second;

        visited[x] = 1;
        multime[x] = mx;

        q.pop();

        for(int i = 0; i < r[x].size(); i ++)
        {
            if(!visited[ r[x][i].first ])
                q.push(make_pair(r[x][i].first, !mx));
        }
    }
}


bool bfs2() //pt EdmondsCarp
{

    q2.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q2.empty())
    {
        int x = q2.front();
        q2.pop();

        for (int j=0; j < r[x].size(); j++)
        {
            int y = r[x][j].first; // y == vecinul lui x
            int val = r[x][j].second; // val == fluxul de la x la y
            if (!visited[y] && val > 0)
            {
                q2.push(y);
                parent[y] = x;
                visited[y] = true;
            }
        }
    }

    if (visited[t])

        return true;
    else
        return false;
}

void Ford_Fulkerson() //cu EdmondsKarp
{
    for(i = 1; i <= t ; i++)    //resetez visited
            visited[i] = 0;

    while(bfs2())    //cat timp gasesc un flux pozitiv <=> un drum minim de la s la t folosind bfs
    {

        int x, y, j, i, j2, flux_ = INT_MAX, xm, ym;

        for (y = t; y != s; y = parent[y])  //muchia minima din drum
        {
            x = parent[y];
            j = poz[x][y];

            //if( x != s && x != t && r[x][j].first != s && r[x][j].first != t)
            if(x != s && y != t)
            {
                flux_ = r[x][j].second;
                xm = x;
                ym = r[x][j].first;
            }
        }

        for (y = t; y != s; y = parent[y])  //updatez reteaua reziduala
        {
            x = parent[y];
            j = poz[x][y];
            j2 = poz[y][x];

            r[x][j].second -= flux_;
            r[y][j2].second += flux_;
        }

        g<<xm<<" "<<ym<<'\n'; //cuplajul maxim

        for(i = 1; i <= t ; i++)    //resetez visited
            visited[i] = 0;
    }

}


int main()
{
    f>>n>>m;

    s = n + 1;
    t = n + 2;

    r.resize(n + 3);
    visited.resize(n + 3);
    multime.resize(n + 1);
    parent.resize(n + 3);
    poz.resize(t + 1);

    for(i = 1; i <= t; i++)
        poz[i].resize(t + 1);


    for(i = 0; i < m; i++)
    {
        int x, y;

        f>>x>>y;

        r[x].push_back(make_pair(y,0)); //ma ocup de val dupa ce aflu cele doua seturi de noduri
        r[y].push_back(make_pair(x,0));

        poz[x][y] = r[x].size() - 1;
        poz[y][x] = r[y].size() - 1;
    }

    bfs(1); //pt incadrarea nodurilor in cele 2 seturi

    for(i = 1; i <= n; i++)
    {
        for(j = 0; j < r[i].size(); j++)
            if( multime[i] == 0 && multime[r[i][j].first] == 1)
                r[i][j].second = 1;
            else
                r[i][j].second = 0;//val drum de intoarcere in reteaua reziduala

        if(multime[i] == 0)
        {
            r[s].push_back(make_pair(i, 1));   // leg nodul s
            poz[s][i] = r[s].size() - 1;

            r[i].push_back(make_pair(s, 0));
            poz[i][s] = r[i].size() - 1;
        }
        else
        {

            r[i].push_back(make_pair(t, 1));   // si nodul t
            poz[i][t] = r[i].size() - 1;

            r[t].push_back(make_pair(i, 0));
            poz[t][i] = r[t].size() - 1;
        }
    }

    n = t;

    Ford_Fulkerson();

    return 0;

}
