#include <iostream>
#include<fstream>
#include<queue>

using namespace std;

ifstream f("rj.in");
ofstream g("rj.out");

#define inf 100000

int vi[] = {0, 0, 1, -1, 1, 1, -1, -1};
int vj[] = {1, -1, 0, 0, 1, -1, 1, -1};

int n, m, R[102][102], J[102][102], ji, jj, ri, rj;
queue<pair<int, int>> q;

bool ok(int i, int j)
{
    if(i < 1 || i > n || j < 1 || j > m)
        return false;
    return true;
}

void Lee(int M[102][102])
{
    while(!q.empty())
    {
        int i = q.front().first;
        int j = q.front().second;
        q.pop();

        for(int k = 0; k < 8; k++)
        {
            int i2 = i + vi[k]; //i next
            int j2 = j + vj[k]; //j next

            if(ok(i2,j2) && M[i2][j2] != -1 && M[i2][j2] > M[i][j] + 1)
            {
                M[i2][j2] = M[i][j] + 1;
                q.push(make_pair(i2,j2));
            }
        }
    }
}

int main()
{
    f >> n >> m;

    char s[m + 2];

    f.get();


    for(int i = 1; i <= n; i++)
    {
        f.getline(s, m + 1);

        for(int j = 1; j <= m; j++)
        {
            if(s[j-1] == 'R')
            {
                R[i][j] = 0;
                ri = i;
                rj = j;
                J[i][j] = inf;
            }
            else if(s[j-1] == 'J')
            {
                J[i][j] = 0;
                ji = i;
                jj = j;
                R[i][j] = inf;
            }
            else if(s[j-1] == 'X')
            {
                R[i][j] = -1;
                J[i][j] = -1;
            }
            else
            {
                R[i][j] = inf;
                J[i][j] = inf;
            }
        }
    }

    q.push(make_pair(ri, rj));

    Lee(R);


    q.push(make_pair(ji, jj));

    Lee(J);

    int min = inf, l, c;

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            if(R[i][j] == J[i][j] && R[i][j] != -1 && R[i][j] < min)
            {
                l = i;
                c = j;
                min = R[i][j];
            }

    g << min + 1 <<" "<< l <<" "<< c;
}
