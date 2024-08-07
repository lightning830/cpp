#pragma region Macros
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const int INF = 1001001001;
const ll LINF = 1e18;
const int MOD = 1e9+7;

#define rep(i,n) for(ll i = 0; i < (n); i++)
#define repd(i,n) for(ll i = n-1; i >= 0; i--)
#define FOR(i,a,b) for(ll i = a; i <= ll(b); i++)
#define FORD(i,a,b) for(ll i = a; i >= ll(b); i--)
#define FORA(i,I) for(const auto& i:I)

#define ALL(x) x.begin(),x.end() 
#define SIZE(x) ll(x.size()) 
#define pb push_back
#define mp make_pair

#define F first
#define S second
#define V vector
#define P pair<ll, ll>
#define M map<ll, ll>
//繰り上げ、繰り下げ
ll myceil(ll a,ll b){return (a+(b-1))/b;}
ll myfloor(ll a,ll b){return a/b;}
//最大値、最小値を更新
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
ll gcd(ll a, ll b){return b?gcd(b,a%b):a;}
ll lcm(ll a, ll b){return a*b/gcd(a, b);}

struct UnionFind
{
    vector<int> d;
    UnionFind(int n = 0): d(n, -1){}
    int find(int x){
        if(d[x] < 0) return x;
        return d[x] = find(d[x]);
    }

    bool unite(int x, int y){
        x = find(x); y = find(y);
        if(x == y) return false;
        if(d[x] > d[y]) swap(x, y);
        d[x] += d[y];
        d[y] = x;
        return true;
    }
    bool same(int x, int y){return find(x) == find(y);}
    int size(int x){return -d[find(x)];}
};

class mint {
    long long x;
public:
    mint(long long x=0) : x((x%MOD+MOD)%MOD) {}
    mint operator-() const { 
      return mint(-x);
    }
    mint& operator+=(const mint& a) {
        if ((x += a.x) >= MOD) x -= MOD;
        return *this;
    }
    mint& operator-=(const mint& a) {
        if ((x += MOD-a.x) >= MOD) x -= MOD;
        return *this;
    }
    mint& operator*=(const  mint& a) {
        (x *= a.x) %= MOD;
        return *this;
    }
    mint operator+(const mint& a) const {
        mint res(*this);
        return res+=a;
    }
    mint operator-(const mint& a) const {
        mint res(*this);
        return res-=a;
    }
    mint operator*(const mint& a) const {
        mint res(*this);
        return res*=a;
    }
    mint pow(ll t) const {
        if (!t) return 1;
        mint a = pow(t>>1);
        a *= a;
        if (t&1) a *= *this;
        return a;
    }
    // for prime MOD
    mint inv() const {
        return pow(MOD-2);
    }
    mint& operator/=(const mint& a) {
        return (*this) *= a.inv();
    }
    mint operator/(const mint& a) const {
        mint res(*this);
        return res/=a;
    }

    friend ostream& operator<<(ostream& os, const mint& m){
        os << m.x;
        return os;
    }
};


#pragma endregion


int main() {
    int h, w; cin >> h >> w;
    int s[h][w];
    rep(i, h)rep(j, w) cin >> s[i][j];

    V<V<int>> dp(h, V<int>(w));
    rep(i, w) dp[0][i] = s[0][i];

    rep(i, h-1){
        rep(j, w){
            if(j-1 >= 0){//左
                chmax(dp[i+1][j-1], dp[i][j] + s[i+1][j-1]);
            }
            if(j+1 < w){//右
                chmax(dp[i+1][j+1], dp[i][j] + s[i+1][j+1]);
            }
            //下
            chmax(dp[i+1][j], dp[i][j] + s[i+1][j]);
        }
    }
    int ans = 0;

    rep(i, w){
        chmax(ans, dp[h-1][i]);
    }
    cout << ans << endl;
    return 0;
}