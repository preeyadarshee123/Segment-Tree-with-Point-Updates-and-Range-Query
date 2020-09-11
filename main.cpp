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
