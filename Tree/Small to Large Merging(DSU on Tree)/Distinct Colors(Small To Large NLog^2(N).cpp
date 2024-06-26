/*
Problem Name: Distinct Colors
Problem Link: https://cses.fi/problemset/task/1139
Complexity: NLog^2(N)
*/
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 1;
int color[N+1], distinct[N+1];
vector<int> adj[N+1];
 
set<int> dfs(int u, int p) {
  set<int> st_u = {color[u]};
  for (auto v: adj[u]) {
    if (v == p)  continue;
    set<int> st_v = dfs(v, u);
    if(st_u.size() < st_v.size())swap(st_u, st_v);
    for(auto x : st_v) {
        st_u.insert(x);
    }
  }
  distinct[u] = st_u.size();
  return st_u;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        int n;
        cin >> n;
        for(int i = 1; i <= n; i++) {
          cin >> color[i];
        }
        for(int i = 0; i < n-1; i++) {
          int u, v;
          cin >> u >> v;;
          adj[u].push_back(v);
          adj[v].push_back(u);
        }
        dfs(1, -1);
        for(int i = 1; i <= n; i++)cout << distinct[i] << " ";
    }
    return 0;
}