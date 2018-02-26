#include<algorithm>
#include<cassert>
#include<iostream>
#include<vector>
using namespace std;
typedef long long lint;
#define rep(i,n)for(int i=0;i<(int)(n);++i)

// http://math314.hateblo.jp/entry/2015/05/07/014908
namespace math314{
  typedef long long ll;
  typedef pair<int, int> Pii;

#define FOR(i,n) for(int i = 0; i < (n); i++)
#define sz(c) ((int)(c).size())
#define ten(x) ((int)1e##x)

  template<class T> T extgcd(T a, T b, T& x, T& y) { for (T u = y = 1, v = x = 0; a;) { T q = b / a; swap(x -= q * u, u); swap(y -= q * v, v); swap(b -= q * a, a); } return b; }
  template<class T> T mod_inv(T a, T m) { T x, y; extgcd(a, m, x, y); return (m + x % m) % m; }
  ll mod_pow(ll a, ll n, ll mod) { ll ret = 1; ll p = a % mod; while (n) { if (n & 1) ret = ret * p % mod; p = p * p % mod; n >>= 1; } return ret; }

  template<int mod, int primitive_root>
  class NTT {
  public:
    int get_mod() const { return mod; }
    void _ntt(vector<ll>& a, int sign) {
      const int n = sz(a);
      assert((n ^ (n&-n)) == 0); //n = 2^k

      const int g = 3; //g is primitive root of mod
      int h = (int)mod_pow(g, (mod - 1) / n, mod); // h^n = 1
      if (sign == -1) h = (int)mod_inv(h, mod); //h = h^-1 % mod

      //bit reverse
      int i = 0;
      for (int j = 1; j < n - 1; ++j) {
	for (int k = n >> 1; k >(i ^= k); k >>= 1);
	if (j < i) swap(a[i], a[j]);
      }

      for (int m = 1; m < n; m *= 2) {
	const int m2 = 2 * m;
	const ll base = mod_pow(h, n / m2, mod);
	ll w = 1;
	FOR(x, m) {
	  for (int s = x; s < n; s += m2) {
	    ll u = a[s];
	    ll d = a[s + m] * w % mod;
	    a[s] = u + d;
	    if (a[s] >= mod) a[s] -= mod;
	    a[s + m] = u - d;
	    if (a[s + m] < 0) a[s + m] += mod;
	  }
	  w = w * base % mod;
	}
      }

      for (auto& x : a) if (x < 0) x += mod;
    }
    void ntt(vector<ll>& input) {
      _ntt(input, 1);
    }
    void intt(vector<ll>& input) {
      _ntt(input, -1);
      const int n_inv = mod_inv(sz(input), mod);
      for (auto& x : input) x = x * n_inv % mod;
    }

    // 畳み込み演算を行う
    vector<ll> convolution(const vector<ll>& a, const vector<ll>& b){
      int ntt_size = 1;
      while (ntt_size < sz(a) + sz(b)) ntt_size *= 2;

      vector<ll> _a = a, _b = b;
      _a.resize(ntt_size); _b.resize(ntt_size);

      ntt(_a);
      ntt(_b);

      FOR(i, ntt_size){
	(_a[i] *= _b[i]) %= mod;
      }

      intt(_a);
      return _a;
    }
  };

  typedef NTT<167772161, 3> NTT_1;
  typedef NTT<469762049, 3> NTT_2;
  typedef NTT<1224736769, 3> NTT_3;

  // garnerのアルゴリズムを直書きしたversion，速い
  vector<ll> fast_int32mod_convolution(vector<ll> a, vector<ll> b,int mod){
    for (auto& x : a) x %= mod;
    for (auto& x : b) x %= mod;
	
    NTT_1 ntt1; NTT_2 ntt2; NTT_3 ntt3;
    assert(ntt1.get_mod() < ntt2.get_mod() && ntt2.get_mod() < ntt3.get_mod());
    auto x = ntt1.convolution(a, b);
    auto y = ntt2.convolution(a, b);
    auto z = ntt3.convolution(a, b);

    // garnerのアルゴリズムを極力高速化した
    const ll m1 = ntt1.get_mod(), m2 = ntt2.get_mod(), m3 = ntt3.get_mod();
    const ll m1_inv_m2 = mod_inv<ll>(m1, m2);
    const ll m12_inv_m3 = mod_inv<ll>(m1 * m2, m3);
    const ll m12_mod = m1 * m2 % mod;
    vector<ll> ret(sz(x));
    FOR(i, sz(x)){
      ll v1 = (y[i] - x[i]) *  m1_inv_m2 % m2;
      if (v1 < 0) v1 += m2;
      ll v2 = (z[i] - (x[i] + m1 * v1) % m3) * m12_inv_m3 % m3;
      if (v2 < 0) v2 += m3;
      ll constants3 = (x[i] + m1 * v1 + m12_mod * v2) % mod;
      if (constants3 < 0) constants3 += mod;
      ret[i] = constants3;
    }

    return ret;
  }
}

pair<string,lint> divide(const string &n,lint r){
  string res;
  lint rem=0;
  bool cont_zero=1;
  rep(i,n.size()){
    rem=10*rem+(n[i]-'0');
    lint q=rem/r;
    rem%=r;
    if(cont_zero&&q==0)continue;
    if(q!=0)cont_zero=0;
    res+='0'+q;
  }
  return make_pair(res,rem);
}


vector<lint> parse(const string &n,lint r){
  vector<lint> dig;
  string cur(n);
  while(1){
    pair<string,lint>sub=divide(cur,r);
    dig.push_back(sub.second);
    cur=sub.first;
    if(cur=="")break;
  }
  return dig;
}

vector<lint> g(lint p,lint l,lint r){
  if(l>r){
    return vector<lint>(1,1);
  }
  if(l==r){
    vector<lint> ret(2);
    ret[0]=1;
    ret[1]=l;
    return ret;
  }
  lint mid=(l+r+1)/2;
  vector<lint>fst=g(p,l,mid-1);
  vector<lint>snd=g(p,mid,r);
  return math314::fast_int32mod_convolution(fst,snd,p);
}


lint f(string n,lint p){
  const lint mod=1e9+7;
  vector<lint> dig=parse(n,p);
  if(dig[0]==p-1){
    //propagate
    dig[0]=0;
    int car=1,pos=1;
    while(car>0&&pos<(int)dig.size()){
      dig[pos]++;
      car=0;
      if(dig[pos]>=p){
	dig[pos]=0;
	car=1;
      }
      pos++;
    }
    if(car>0)dig.push_back(car);
  }
  vector<lint> ans=g(p,1,dig[0]);
  lint ret=0;
  rep(i,dig[0]+1){
    if(ans[i]!=0)ret++;
  }
  rep(i,dig.size()-1)
    ret=ret*(dig[i+1]+1)%mod;
  return ret;
}

int main(){
  int t;
  cin>>t;
  while(t--){
    string n;
    lint p;
    cin>>n>>p;
    cout<<f(n,p)<<endl;
  }
}
