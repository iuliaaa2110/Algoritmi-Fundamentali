#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream f("admitere-fmi-2016.in");
ofstream g("admitere-fmi-2016.out");

int n, m, k;

vector<int> pr;   //friends
vector< vector<int> > w;
bool b[100001]; // 1 = eliminat

queue<int> q;

void kind_of_bfs()
{
    while (!q.empty())
    {
        int x = q.front();
        for(int i = 0; i < w[x].size(); ++i)
        {
            if(!b[w[x][i]]) //iau prietenii care mai sunt valabili
            {
                pr[w[x][i]]--;  //si rup legatura ei

                if(pr[w[x][i]] < k) // daca  acum prietenul i  nu se mai incadreaza nici el
                {
                    b[w[x][i]] = true;  //il elimin
                    q.push(w[x][i]);    //si rup si legaturile lui
                }
            }
        }
        q.pop();
    }
}

int main()
{
    int x, y;

    f >> n >> m >> k;

    pr.resize(n+1);
    w.resize(n+1);


    for(int i = 0; i < m; ++i)
    {
        f >> x >> y;

        w[x].push_back(y);
        w[y].push_back(x);

        pr[x]++;
        pr[y]++;
    }

    //a)
    for (int i = 1; i <= n; ++i)
    {
        g<<pr[i]<<" ";

        if (pr[i] < k)
        {
            q.push(i);  //ii pun in coada ca sa rup toate legaturile pe care le aveau
            b[i] = true;    //n au destui prieteni :c csf :)))
        }
    }

    g<<'\n';

    //b)
    kind_of_bfs();

    bool ok = 0;

    for (int i = 1; i <= n; ++i)
        if (b[i] == 0)  //daca au mai ramas noduri neeliminate le afisez
        {
            g << i << " ";
            ok = 1;
        }

    if (!ok)
    {
        g << "NU";
    }

    f.close();
    g.close();

    return 0;
}
