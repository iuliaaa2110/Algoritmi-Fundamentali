#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

ifstream f("padure.in");
ofstream g("padure.out");

int N, M;
queue <pair <int, int> > q;
int a[1001][1001], b[1001][1001];   //in b numar

int vi[4] = {0, 0, 1, -1};
int vj[4] = {1, -1, 0, 0};

bool ok(int i, int j)
{
    if (i < 1 || j < 1 || i > N || j > M)
        return false;
    return true;
}


int main()
{
    int cl, cc, pc, pl;

    f >> N >> M >> pl >> pc >> cl >> cc;

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
        f >> a[i][j];

    q.push( make_pair(pl, pc) );
    b[pl][pc] = 1;

    while(!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;

        q.pop();

        for (int k = 0; k < 4; k++)
        {
            int x2 = x + vi[k];
            int y2 = y + vj[k];

            if (ok(x2, y2))
            {
                int c;

                if (a[x2][y2] != a[x][y])
                    c = 1;
                else
                    c = 0;

                if (b[x2][y2] == 0 || b[x2][y2] > b[x][y] + c)
                {
                    b[x2][y2] = b[x][y] + c;
                    q.push( make_pair(x2, y2) ) ;
                }

            }
        }
    }

    g << b[cl][cc] - 1;

    return 0;
}
