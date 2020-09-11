#include<bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//#include <functional>
#define pb                    push_back
#define ll                    long long
#define ss                       second
#define ff                        first
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
#define eps                   0.000000001
#define all(c)               (c).begin(),(c).end()
#define present(c,x)         ((c).find(x) != (c).end())
#define cpresent(c,x)        (find(all(c),x) != (c).end())
//#define pi                   pair<int,int>
#define pll                  pair<ll,ll>
#define endl                 '\n'
#define ull                  unsigned long long
using namespace std;
vector<string> split(const string& s, char c) {
    vector<string> v; stringstream ss(s); string x;
    while (getline(ss, x, c)) v.emplace_back(x); return move(v);
}
template<typename T, typename... Args>
inline string arrStr(T arr, int n) {
    stringstream s; s << "[";
    for(int i = 0; i < n - 1; i++) s << arr[i] << ",";
    s << arr[n - 1] << "]";
    return s.str();
}

#define debug(args...) {__evars_begin(__LINE__); __evars(split(#args, ',').begin(), args);}

inline void __evars_begin(int line) { cerr << "#" << line << ": "; }
template<typename T> inline void __evars_out_var(vector<T> val) { cerr << arrStr(val, val.size()); }
template<typename T> inline void __evars_out_var(T* val) { cerr << arrStr(val, 10); }
template<typename T> inline void __evars_out_var(T val) { cerr << val; }
inline void __evars(vector<string>::iterator it) { cerr << endl; }

template<typename T, typename... Args>
inline void __evars(vector<string>::iterator it, T a, Args... args) {
    cerr << it->substr((*it)[0] == ' ', it->length()) << "=";
    __evars_out_var(a);
    cerr << "; ";
    __evars(++it, args...);
}
//using namespace __gnu_pbds;
//typedef tree<int, null_type, int>, rb_tree_tag,tree_order_statistics_node_update> policy;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
typedef vector< int > vi;
typedef vector< vi > vvi;
int dx[8]={1,-1,0,0,1,1,-1,-1};
int dy[8]={0,0,-1,1,2,-2,2,-2};
vector<int> vis(200010,0),dis(200010,0),par(200010,0),ed(200010,0);
vector<pair<int,int>> adj[200010];
vector<vector<int>> ad;
int myrandom (int i) { return std::rand()%i;}
const int MAX=200010;
const ull inf = 1000000007;
class SegTree{
    public :
    vector<ll> t,a;
    void init(int sz,vector<int> &v){
        t.resize(4*sz);
        a.resize(sz+1);
        for(int i = 1;i <= sz;i++){
            a[i] = v[i];
        }
    }
    void build(int v,int l,int r){
        if(l==r){
            t[v]=a[l];
            return ;
        }
        int mid=(l+r)/2;
        build(2*v,l,mid);
        build(2*v+1,mid+1,r);
        t[v]=max(t[2*v],t[2*v+1]);
    }
    void upd(int v,int l,int r,int id){
        if(l == r){
            t[v]  = a[l];
            return ;
        }
        int mid = (l+r)/2;
        if(mid < id)
            upd(2*v+1,mid+1,r,id);
        else
            upd(2*v,l,mid,id);
        t[v] = max(t[2*v] , t[2*v+1]);
    }
    ll query(int v,int l,int r,int a,int b){
        if(l > r || l > b || r < a)
            return 0;
        if(l >= a && r <= b){
            return t[v];
        }
        int mid=(l+r)/2;
        return max(query(2*v+1, mid+1, r, a,b),query(2*v, l, mid, a,b));
    }
};
class HLD{
    public :
    vector<int> parent, depth, heavy, head, pos;
    int cur_pos;
    int dfs(int v, vector<vector<int>> const& adj) {
        int size = 1;
        int max_c_size = 0;
        for (int c : adj[v]) {
            if (c != parent[v]) {
                parent[c] = v, depth[c] = depth[v] + 1;
                int c_size = dfs(c, adj);
                size += c_size;
                if (c_size > max_c_size)
                    max_c_size = c_size, heavy[v] = c;
            }        }
        return size;
    }
    void decompose(int v, int h, vector<vector<int>> const& adj) {
        head[v] = h, pos[v] = cur_pos++;
        if (heavy[v] != -1)
            decompose(heavy[v], h, adj);
        for (int c : adj[v]) {
            if (c != parent[v] && c != heavy[v])
                decompose(c, c, adj);
        }
    }
    
    void init(vector<vector<int>> const& adj) {
        int n = adj.size();
        parent = vector<int>(n);
        depth = vector<int>(n);
        heavy = vector<int>(n, -1);
        head = vector<int>(n);
        pos = vector<int>(n);
        cur_pos = 1;
        
        dfs(1, adj);
        decompose(1, 1, adj);
    }
    int query(int a, int b,SegTree &s) {
        int res = 0;
        int n = (int)parent.size();
        for (; head[a] != head[b]; b = parent[head[b]]) {
            if (depth[head[a]] > depth[head[b]])
                swap(a, b);
            int cur_heavy_path_max = s.query(1,1,n-1,pos[head[b]], pos[b]);
            res = max(res, cur_heavy_path_max);
        }
        if (depth[a] > depth[b])
            swap(a, b);
        int last_heavy_path_max = s.query(1,1,n-1,pos[a], pos[b]);
        res = max(res, last_heavy_path_max);
        return res;
    }
    
};
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //ifstream fin;
    //ofstream fout;
    //fin.open("input.txt");
    //fout.open("output.txt");
    //clock_t launch=clock();
    
}
