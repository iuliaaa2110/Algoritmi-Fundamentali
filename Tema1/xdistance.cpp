#include <iostream>
#include <vector>
#include <algorithm>
#include<fstream>

using namespace std;

ifstream f("dfs.in");
ofstream g("dfs.out");

const int lmax = 1e5+5;

vector<pair<int, int>> w[lmax];

long long distanta(int n, int cost) {

    long long rez = 0;

    vector<bool> b(n+1, 0);

    for(int i = 1; i <= n; i++) {

        vector<int> q;

        q.push_back(i);
        b[i] = true;

        int nr = 1;

        while(q.size())
        {
            int nod = q.back();
            q.pop_back();

            for(i = 0; i < w[nod].size() ; i++)
            {
                if(w[nod][i].second <= cost)
                {
                   int x = w[nod][i].first;

                   if(!b[x])
                   {
                       q.push_back(x);
                       b[x] = true;
                       nr++;
                   }
                }

            }
        }

        rez += 1LL * nr*(nr-1)/2;
    }

    return rez;
}


int main()
{
    int n, m, x, a, b, c;

    f >> n >> m >> x;

    for(int i = 0; i < m; i++)
    {
        f >> a >> b >> c;
        w[a].push_back({b, c});
        w[b].push_back({a, c});
    }

    g << distanta(n, x) - distanta(n, x-1);
    return 0;
}
