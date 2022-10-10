#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<limits.h>

using namespace std;

ifstream f("grafpond.in");
ofstream g("grafpond.out");

int n, m, d, y2;
int gf[10001][10001];
int a[10001][10001]; //first = vecinul, second = val muchiei

void  floyd_warshall()
{
    int i, j, k;

	for (k = 1; k <= n; k++)
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				if (a[i][k] && a[k][j] && (a[i][j] > a[i][k] + a[k][j] || !a[i][j]) && i != j)
                    a[i][j] = a[i][k] + a[k][j];
}

void lant_diametral(int x, int s, vector<int>v, bool b[10001])
{
    v.push_back(x);
    b[x] = 1;

    if(x==y2)
    {
        for(int i = 0; i < v.size(); i++)
            g<<v[i]<<" ";

    }
    else
    {
        for(int j = 1; j <= n; j++)
            if(gf[x][j] && s + gf[x][j] <= d && !b[j]) //d = diametru
                lant_diametral(j,s + gf[x][j], v, b);
    }
}

int main ()
{
    int i,j;

    f>>n>>m;

    for(i = 0; i < m; i++)
    {
        int x, y, p;

        f>>x>>y>>p;

        gf[x][y] = p;
        gf[y][x] = p;

        a[x][y] = p;
        a[y][x] = p;

    }

    floyd_warshall();

    //excentricitatea lui i = maximul de pe linia i
    //fie raza = minim(excentricitati)
	//Diametrul = maxim(excentricitati) <=> maximul matricei
    //centru = multimea nodurilor cu excentricitatea == raza

	int centru[10001], x, raza = INT_MAX, e, l=0, jaux;

    for (i = 1; i <= n; i++)
	{
	    int e = 0;   //excentricitatea lui i

		for (j = 1; j <= n; j++)
            if(a[i][j] > e)
            {
                e = a[i][j];
                jaux = j;
            }

        if(e > d)
        {
            d = e;
            x = i;
            y2 = jaux;
        }

        if( e == raza)
        {
            l++;
            centru[l] = i;
        }

        if( e < raza)
        {
            raza = e;
            l = 1;
            centru[l] = i;
        }


	}

	g<<"Raza este: "<<raza<<'\n';
	g<<"Diametrul este: "<<d<<'\n';
	g<<"Centrul grafului este: ";

	for(i = 1; i <= l; i++)
        g<<centru[i]<<" ";
    g<<'\n';

    g<<"Un lant diametral este: ";

    vector<int>v;
    bool b[10001];
    lant_diametral(x,0,v,b);

	return 0;
}


