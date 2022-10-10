#include <iostream>
#include <queue>

using namespace std;

int w[1005][1005], dist[1005][1005], vi[5] = {1, -1, 0, 0}, vj[5] = {0, 0, 1, -1};
queue <pair<int, int>> q;
int n, m, k;

bool ok(int i, int j)
{
    if( i <= 0 || i > n || j <= 0 || j > m)
        return false;

    return true;
}

void lee()
{
    while (!q.empty())
    {
        int i = q.front().first;
        int j = q.front().second;

        q.pop();

        for (int z = 0; z < 4;z++)
        {
            int i2 = i + vi[z];
            int j2 = j + vj[z];

            if (ok(i2,j2) && w[i2][j2] == 0 && ( dist[i2][j2] == -1 || dist[i2][j2] > dist[i][j] + 1) )
            {
                dist[i2][j2] = dist[i][j] + 1;
                q.push(make_pair(i2, j2));
            }
        }
    }
}

int main()
{
    cin >> n >> m >> k;

    char c;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            cin >> c;

            if (c == '.')
                w[i][j] = 0;
            else
                w[i][j] = 1;

            dist[i][j] = -1;
        }

    int x, y;

    for (int i = 1; i <= k; i++)
    {
        cin >> x >> y;
        dist[x][y] = 0;
        q.push(make_pair(x, y));
    }

    lee();

    int s = 0;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if(dist[i][j]!=-1)
            s += dist[i][j];

    cout << s;

    return 0;
}
