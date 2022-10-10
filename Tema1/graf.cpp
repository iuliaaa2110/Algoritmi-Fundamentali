#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream f("graf.in");
ofstream g("graf.out");

int N, M;

vector < vector <int> > w;   //retin intr un vector de vectori. Nodul i are vecinii  v[i][0], v[i][1] ...
int c[7502];
bool b[7502];  //1 = vizitat, 0 = nev
int vfx[7502], vfc[7502];
vector <int> v;

void BFS(int p)
{
    queue <int> q;
    q.push(p);


    while(!q.empty())
    {
        int x = q.front();
        q.pop();

        for(int i = 0; i < w[x].size(); i ++)
        {
            if(c[ w[x][i] ] == 0 && w[x][i] != p)
            {
                c[ w[x][i] ] = c[x] + 1;
                q.push(w[x][i]);
            }
        }
    }

}

void rez(int u) //parcurg acum in sens invers si numar frecventaa de aparitie pt fiecare
{
    vfc[ c[u] ] = 1;    //vector de frecventa pt contorizari
    vfx[u] = 1; //vector de frecventa pt noduri
    b[u] = 1;

    queue<int> q;
    q.push(u);

    while(!q.empty())
    {
        int x = q.front();
        q.pop();

        for(int i = 0; i < w[x].size(); i++)
        {

            if( c[x] == c[ w[x][i] ] + 1 )
            {
                vfc[c[x]-1]++;
                vfx[ w[x][i] ]++;

                if(!b[ w[x][i] ])
                {
                    b[ w[x][i] ] = 1;
                    q.push(w[x][i]);
                }
            }
        }
    }
}

int main()
{
    int x, y, a1, a2, s = 0;

    f >> N >> M >> a1 >> a2;

    w.resize(N + 2);

    for (int i = 0; i < M; i++)
    {
        f >> x >> y;
        w[x].push_back(y);
        w[y].push_back(x);
    }

    BFS(a1);
    //rez(a2);

    for(int i = 1; i <= N; i++)
        cout<<c[i]<<" ";
//        if(vfx[i] == vfc[c[i]] && b[i])   //=>este nod comun al tuturor lanturilor optime
  //      {
    //        cout<<vfx[i]<<" ";
      //      s++;
        //    v.push_back(i);
        //}

    g<<s<<'\n';
    for (int i = 0; i < s; i++)
        g<<v[i]<<" ";

    return 0;
}
