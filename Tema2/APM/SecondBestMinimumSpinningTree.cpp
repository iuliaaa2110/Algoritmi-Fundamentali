#include<iostream>
#include<fstream>
#include<vector>
#include<queue>

using namespace std;

ifstream f("apm.in");
ofstream g("apm.out");

vector< vector< pair<int, bool> > >w;   //first = valoarea muchiei, second = daca este in apm sau nu
vector< vector< pair<int, int> > >apm;
priority_queue< pair<int, pair<int,int> >, vector< pair<int, pair<int,int> > >, greater< pair<int, pair<int,int> > > >h; //first valoarea, second.first =x, second.second = y
vector< vector< pair<int, pair< int, int> >  > >muchie_max; //aici pt fiecare pereche x y, costul maxim al unei muchii din lantul de la x la y

int s,ya,xa,ca,mx,my,n;

bool b[200001], b2[200001] ; //marchez cand plec din nod

void prim (int x)
{
    for(int i = 1; i <= n; i++)
        if(!b[i] && w[x][i].first)
            h.push(make_pair(w[x][i].first, make_pair(x, i)));

    b[x] = 1;

    while ( !h.empty() && b[h.top().second.second]) /
        h.pop();

    if(!h.empty())
    {
        int val = h.top().first, xn = h.top().second.first, yn = h.top().second.second;
        h.pop();

        apm[xn].push_back(make_pair(yn, val));  //pe asta l am facut cand aveam liste de adiacenta, apoi am adus w la n pe n
        apm[yn].push_back(make_pair(xn, val));

        w[xn][yn].second = w[yn][xn].second = 1;    //marchez ca fac paprte din apm1

        s += val;

        prim(yn);
    }

}

//
int dfs(int st, int x, int cmax,int pred)    //dfs pe apm1
{
    b2[x] = 1;
    muchie_max[st][x].first = cmax;
    muchie_max[st][x].second.first = pred;
    muchie_max[st][x].second.second = x;

    cout<<st<<" "<<x<<" "<<cmax<<endl;

    for(int i = 0; i < apm[x].size(); i++)
    {
        if( !b2[apm[x][i].first] )
        {
            if(apm[x][i].second > cmax)
            {
                dfs(st, apm[x][i].first, apm[x][i].second, x);
            }
            else
            {
                dfs(st, apm[x][i].first, cmax, x);
            }
        }
    }
}


int main()
{
    //Prim:

    int  m, x, y, cost;

    f >> n >> m;

    w.resize(n+1);
    apm.resize(n+1);
    muchie_max.resize(n+1);

    for(int i = 1; i <= n; i++)
    {
        muchie_max[i].resize(n+1);
        w[i].resize(n+1);
    }


    for(int i = 0; i < m; i++)
    {
        f>>x>>y>>cost;

        w[x][y].first = cost;
        w[y][x].first = cost;
    }

    prim(1);

    g<<"Primul"<<'\n';
    g<<"Cost"<<'\n'<<s<<'\n';
    g<<"Muchii"<<'\n';

    for(int i = 1; i <= n ;i++)
    {
        if(!b2[i])
        {
            for(int j = 0; j < apm[i].size(); j++)
            {
                g<<i<<" "<<apm[i][j].first<< '\n';
                b2[apm[i][j].first] = 1;
            }
        }
    }

    //APM2:
    int s2 = INT_MAX,iv, jv, in, jn;

    for(int i = 1; i <= n ;i++)
    {
        for( int j = 1; j <= n; j++)
            b2[j] = 0;

        dfs(i, i, 0, i);
    }

    for(int i = 1; i <= n; i++)
         for(int j = 1; j <= n; j++)
            if(!w[i][j].second && w[i][j].first) //aici iau muchiile care nu sunt in apm
                if(s - muchie_max[i][j].first + w[i][j].first < s2)
                {
                    //cout<<i<<" "<<j<<" "<< muchie_max[i][j]<<" "<<w[i][j].first<<endl<<s2<<endl;
                    s2 =s - muchie_max[i][j].first + w[i][j].first;

                    iv = muchie_max[i][j].second.first;
                    jv = muchie_max[i][j].second.second;

                    in = i;
                    jn = j;
                }

    cout<<iv<<" "<<jv<<" "<<in<<" "<<jn;
    g<<"Al doilea"<<'\n';
    g<<"Cost"<<'\n'<<s2<<'\n';
    g<<"Muchii"<<'\n';

    for( int j = 1; j <= n; j++)
            b2[j] = 0;

    for(int i = 1; i <= n ;i++)
    {
        if(!b2[i])
        {
            for(int j = 0; j < apm[i].size(); j++)
            {
                if((i == iv && apm[i][j].first == jv) || (i == jv && apm[i][j].first == iv))
                    g<<in<<" "<<jn<<'\n';
                else
                    g<<i<<" "<<apm[i][j].first<< '\n';

                b2[apm[i][j].first] = 1;
            }
        }
    }

    return 0;
}
