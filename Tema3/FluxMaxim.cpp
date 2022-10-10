#include<iostream>
#include<fstream>
#include<queue>
#include<limits>

#include<vector>

using namespace std;

ifstream f("retea.in");
ofstream g("retea.out");


struct arc{
    int  flux, capacitate;
    bool original; //1 = face parte din graful initial, 0 = muchie artificiala de intoarcere
};


vector < vector < pair <int, arc> > > w; // first = vecinul, second.flux, second.capacitate
vector < vector < pair <int, int> > > r; //first = vecinul, second = valoarea
queue <int> q;

vector <bool> visited; // 1 == vizitat in bfs

vector<int> parent;

vector <vector <int> > poz; //poz[x][y] = pozitia lui y in lista de vecini ai lui x

vector<pair<int,int>> taietura_min;

int n, s, t, m, i, j;

bool  isFlux()
{
    bool b = 1;
    int suma;

    for(i = 2; i <= n - 1; i++) //fara ultimul si fara primul neaparat pt conservare! Iar pt marginire, e de ajuns ca am verificat pt toti vecinii lor.
    {
        int suma = 0;

        for(j = 0; j < w[i].size(); j++)
        {
            if(w[i][j].second.flux > w[i][j].second.capacitate) //marginirea
            {
                b = 0;
                break;
            }

            suma+= w[i][j].second.flux;    //suma tuturor valorilor care ies din nod == suma tuturor care intra in nod
        }

        if(suma!=0 || !b)    //trebuie sa dea 0 ca sa respecte conservarea
        {
            b = 0;
            break;
        }
    }

    if(b)
        return true;
    else
        return false;
}


void Retea_Reziduala() //initializare
{

    for(i = 1; i <= n; i++)
    {
        r[i].resize(w[i].size());

        for(j = 0; j < w[i].size(); j++)
        {
            r[i][j].first = w[i][j].first; //vecinii
            r[i][j].second = w[i][j].second.capacitate - w[i][j].second.flux;//cantitatile de pe fiecare muchie
        }
    }

}


bool bfs()
{
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty())
    {
        int x = q.front();
        q.pop();

        for (int j=0; j < r[x].size(); j++)
        {
            int y = r[x][j].first; // y == vecinul lui x
            int val = r[x][j].second; // val == fluxul de la x la y

            if (!visited[y] && val > 0)
            {
                q.push(y);
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

int Ford_Fulkerson(int fluxMaxim)   //cu EdmondsKarp
{

    while(bfs())    //cat timp gasesc un flux pozitiv <=> un drum minim de la s la t folosind bfs
    {
        int x, y, j, i, j2;
        int flux_ = INT_MAX;
        int m = INT_MAX,xm,ym;

        for (y = t; y != s; y = parent[y])  //muchia minima din drum
        {
            x = parent[y];
            j = poz[x][y];

            flux_ = min(flux_, r[x][j].second);
        }

        for (y = t; y != s; y = parent[y])  //updatez reteaua reziduala
        {
            x = parent[y];
            j = poz[x][y];
            j2 = poz[y][x];

            r[x][j].second -= flux_;
            r[y][j2].second += flux_;

            w[x][j].second.flux += flux_;    //updatez si w doar pt ca imi cere sa-l afisez la final
            w[y][j2].second.flux -= flux_;


            //muchia (minima epuizata) din fiecare drum minim => taietura minima:

            if(w[x][j].second.flux ==  w[x][j].second.capacitate && w[x][j].second.flux < m && w[x][j].second.original)
            {
                m = w[x][j].second.flux;
                xm = x;
                ym = w[x][j].first;
            }


            if(w[y][j2].second.flux ==  w[y][j2].second.capacitate && w[y][j2].second.flux < m && w[y][j2].second.original)
            {
                m = w[y][j2].second.flux;
                xm = y;
                ym = w[y][j2].first;
            }
        }

        taietura_min.push_back( make_pair(xm,ym));

        fluxMaxim += flux_; //adun muchia minima la fluxul final

        for(i = 1; i <= n ; i++)    //resetez visited
            visited[i] = 0;

        //g<<flux_<<'\n';
    }

    return fluxMaxim;
}

int main()
{
    int fluxMaxim = 0;

    f>>n>>s>>t;

    w.resize(n+1);
    r.resize(n+1);
    visited.resize(n+1);
    parent.resize(n+1);
    poz.resize(n+1);

    f>>m;

    for(i = 1; i <= n; i++)
        poz[i].resize(n+1);

    for(i = 0; i < m; i++)
    {
        int x,y;
        arc a;
        f>>x>>y>>a.capacitate>>a.flux;

        a.original = 1;

        if(y == t)
            fluxMaxim += a.flux;

        w[x].push_back(make_pair(y,a));

        a.flux *= (-1);
        a.capacitate = 0;
        a.original = 0;

        w[y].push_back(make_pair(x,a));

        poz[x][y] = w[x].size() - 1;
        poz[y][x] = w[y].size() - 1;
    }

    //a)
    if(isFlux())
        g<<"DA"<<'\n';
    else
        g<<"NU"<<'\n';


    //b)
    Retea_Reziduala(); //initializare


    fluxMaxim = Ford_Fulkerson(fluxMaxim);

    g<<fluxMaxim;

     for(i = 1; i <= n; i++)
    {
        for(j = 0; j <w[i].size(); j++)
            if(w[i][j].second.original)
                g<<'\n'<<i<<" "<<w[i][j].first<<" "<<w[i][j].second.flux;
    }

    g<<'\n'<<fluxMaxim<<'\n';

    for(i = 0; i < taietura_min.size(); i++)
        g<<taietura_min[i].first<<" "<<taietura_min[i].second<<'\n';

    f.close();
    g.close();

    return 0;
}
