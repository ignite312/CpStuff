#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
ll lazy[N*4+5][2], tree[N*4+5];
 
void build(vector<ll> &arr, int node, int l, int r) {
    if(l == r) {
        tree[node] = arr[l];
        return;
    }
    int mid = l + (r - l)/2;
    build(arr, node*2, l, mid);
    build(arr, node*2+1, mid+1, r);
    tree[node] = tree[node*2] + tree[node*2+1];
}
void push(int node, int l, int r) {
    if(lazy[node][0] != 0) {
        ll seg = r - l + 1;
        tree[node] += seg*lazy[node][0] + (seg*(seg-1)*1LL*lazy[node][1])/2;
        if(l != r) {
            int mid = l + (r - l)/2;
            lazy[node*2][0] += lazy[node][0];
            lazy[node*2+1][0] += lazy[node][0]+(mid-l+1)*lazy[node][1];
            lazy[node*2][1]+=lazy[node][1], lazy[node*2+1][1]+=lazy[node][1];
        }
        lazy[node][0] = 0;
        lazy[node][1] = 0;
    }
}
void update(int node, int l, int r, int i, int j) {
    push(node, l, r);
    if(l > j || r < i)return;
    if(l >= i && r <= j) {
        ll seg = r - l + 1;
        ll value = l - i + 1;
        tree[node] += seg*value + seg*(seg-1)/2;
        if(l != r) {
            int mid = l + (r - l)/2;
            lazy[node*2][0] += value;
            lazy[node*2+1][0] += value+(mid-l+1);
            lazy[node*2][1]++, lazy[node*2+1][1]++;
        }
        return;
    }
    int mid = l + (r - l)/2;
    update(node*2, l, mid, i, j); 
    update(node*2+1, mid+1, r, i, j);
    tree[node] = tree[node*2] + tree[node*2+1];
}
ll sum(int node, int l, int r, int i, int j) {
    push(node, l, r);
    if(l > j || r < i)return 0;
    if(l >= i && r <= j) return tree[node];
    int mid = l + (r - l)/2;
    return sum(node*2, l, mid, i, j) + sum(node*2+1, mid+1, r, i, j);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    while(tt--) {
        int n, q;
        cin >> n >> q;
        vector<ll> arr(n+1);
        for(int i = 1; i <= n; i++) {
            cin >> arr[i];
        }
        build(arr, 1, 1, n);
        while(q--) {
            int type;
            cin >> type;
            if(type == 1) {
                int i, j;
                cin >> i >> j;
                update(1, 1, n, i, j);
            }else {
                int i, j;
                cin >> i >> j;
                cout << sum(1, 1, n, i, j) << "\n";
            }
        }
    }
    return 0;
}
// https://cses.fi/problemset/task/1736
