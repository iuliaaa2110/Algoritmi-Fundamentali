#include<iostream>
#include<fstream>
#include<vector>
#include<queue>

using namespace std;

ifstream f("activitati.in");
ofstream g("activitati.out");

int n,m;

struct activitate{

    int durata;
    int intrare;
    int iesire;
    int intrare_la_intoarcere = INT_MAX;
    int iesire_la_intoarcere;
};

vector <activitate> activitati;

vector < vector<int> > cpm;
vector < vector<int> > cpm_invers;
vector < pair <int,int> >solutie_b;

vector <bool> b;    //marchez daca am trecut prin nod

queue <int> q;

void parcurgere()   //bfs kind of
{
    int x = q.front();
    q.pop();

    b[x] = 1;
    activitati[x].iesire = activitati[x].intrare + activitati[x].durata;

    for(int i = 0; i < cpm[x].size(); i++)
    {
        int next = cpm[x][i];

        if(activitati[x].iesire > activitati[next].intrare) //il luam pe cel mai mare
        {
            activitati[next].intrare = activitati[x].iesire;
            q.push(next);
        }
    }

    if(!q.empty())
        parcurgere();
}

void intoarcere()   //bfs kind of
{
    int x = q.front();
    q.pop();

    activitati[x].iesire_la_intoarcere = activitati[x].intrare_la_intoarcere - activitati[x].durata;

    for(int i = 0; i < cpm_invers[x].size(); i++)
    {
        int next = cpm_invers[x][i];

        if(activitati[x].iesire_la_intoarcere <= activitati[next].intrare_la_intoarcere) //de data asta il luam pe cel mai mic
        {
           // cout<<x<<" "<<activitati[x].iesire_la_intoarcere <<" <<"<< next<<" "<<activitati[next].intrare_la_intoarcere<<endl;
            activitati[next].intrare_la_intoarcere = activitati[x].iesire_la_intoarcere;
            solutie_b[next] = make_pair(solutie_b[x].second, solutie_b[x].second + activitati[next].durata);
            q.push(next);
        }
    }

    if(!q.empty())
        intoarcere();
}

void solutie_a(int x)
{

    for(int i = 0; i < cpm_invers[x].size(); i++)
    {

        int next = cpm_invers[x][i];

        if(activitati[next].iesire == activitati[next].intrare_la_intoarcere)
        {
            g<<next<<" ";
            solutie_a(next);
        }
    }
}

int main()
{
    int x, y, timp_minim, fr;

    f>>n;

    cpm.resize(n+1);
    cpm_invers.resize(n+1);
    solutie_b.resize(n+1);
    b.resize(n+1);
    activitati.resize(n+1);

    for(int i = 1; i <= n; i++)
    {
        activitate a;

        f>>a.durata;
        a.intrare = 0;
        activitati[i] = a;
    }

    f>>m;

    for(int i = 0; i < m ; i++)
    {
        f>>x>>y;
        cpm[y].push_back(x);
        cpm_invers[x].push_back(y);
    }

    for(int i = 1; i <= n; i++)
        if(!b[i])
        {
            q.push(i);
            parcurgere();
        }

    for(int i = 1; i <= n ;i++)
        if(cpm[i].size() == 0)  //plec din frunzele grafului spre radacina
        {

            if(activitati[i].iesire > timp_minim)   //timp minim = max( timpi iesire frunze)    //pt a).1
            {
                timp_minim = activitati[i].iesire;
                fr = i;
            }

            activitati[i].intrare_la_intoarcere = activitati[i].iesire;//pt a).2

            solutie_b[i] = make_pair(0,activitati[i].durata); //pentru b)

            q.push(i);
            intoarcere();
        }

    //a)
    g<< "Timp minim:"<< timp_minim <<'\n';
    g<<"Activitati critice:"<< fr <<" ";
    solutie_a(fr);
    g<<'\n';

    //b)
    //in cazul in care doua noduri x1 x2 au aceeasi valoare in iesire_la_intoarcere si ele se duc intr un nod y
    //eu vreau sa ma asigur ca o sa il ia pe x ul din lantul critic.
    //si atunci mai apelez odata din frunza lantului critic, si am pus conditia " <= " in if in functie ca sa se poata suprascrie
    q.push(fr);
    intoarcere();
    //

    for(int i = 1; i <= n ; i++)
        g<<i<<": "<< solutie_b[i].first<<" "<<solutie_b[i].second<<'\n';

    return 0;
}
