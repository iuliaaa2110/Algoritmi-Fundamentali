#include <bits/stdc++.h>

using namespace std;

ifstream f("lesbulan.in");
ofstream g("lesbulan.out");

int T, N, M, sel[53], gr[53], conexe;
vector<int> G[53];

int solve();
void df(int x);
void remove_leafs();

int main()
{
    f >> T;
    for(int i = 1; i <= T; i++) {
        f >> N >> M;
        g << solve() << "\n";
    }
    return 0;
}

int solve() {
    int x, y;
    conexe = 0;
    for(int i = 1; i <= N; i++)
        G[i].clear(), sel[i] = false, gr[i] = 0;
    for(int i = 1; i <= M; i++) {
        f >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for(int i = 1; i <= N; i++)
        if(!sel[i]) {
            conexe++;
            df(i);
        }
    if(N != M + conexe)
        return 0;
    for(int i = 1; i <= N; i++)
        sel[i] = false;
    remove_leafs();
    remove_leafs();
    for(int i = 1; i <= N; i++) {
        for(auto j : G[i])
            gr[j]++;
    }
    for(int i = 1; i <= N; i++) {
        if(gr[i] > 2) return 0;
    }
    return 1;

}

void df(int x) {
    sel[x] = true;
    for(auto i : G[x])
        if(!sel[i])
            df(i);
}

void remove_leafs() {
    vector<int> frunze;
    for(int i = 1; i <= N; i++) {
        if(G[i].size() == 1) {
            frunze.push_back(i);
        }
    }
    for(auto fr : frunze) {
        while(G[fr].size()) {
            int x = G[fr].back();
            G[x].erase(find(G[x].begin(), G[x].end(), fr));
            G[fr].pop_back();
        }
    }
}
