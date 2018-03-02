#include<cmath>
#include<complex>
#include<iostream>
#include<string>
#include<vector>
using namespace std;
typedef long long lint;
#define rep(i,n)for(int i=0;i<(int)(n);++i)

typedef complex<double> comp;

const double pi=acos(-1);

// n は2冪で、a.size()==n
void fft(int n,vector<comp> &a,double dir) {
  // ビット反転は http://math314.hateblo.jp/entry/2015/05/07/014908 を参考にしている。
  int i = 0;
  for (int j = 1; j < n - 1; ++j) {
    for (int k = n >> 1; k >(i ^= k); k >>= 1);
    if (j < i) swap(a[i], a[j]);
  }
  vector<comp> zeta_pow(n);
  rep(i,n){
    double theta=pi/n*i*dir;
    zeta_pow[i]=comp(cos(theta),sin(theta));// 毎回計算することで、誤差を回避する。
  }
  // ここも http://math314.hateblo.jp/entry/2015/05/07/014908 を参考にしている。
  for(int m=1;m<n;m*=2){
    for(int y=0;y<m;++y){
      comp fac=zeta_pow[n/m*y];
      for(int x=0;x<n;x+=2*m){
	int u=x+y;
	int v=x+y+m;
	comp s=a[u]+fac*a[v];
	comp t=a[u]-fac*a[v];
	a[u]=s;a[v]=t;
      }
    }
  }
}

template<class T>
vector<comp> convolution(vector<T> a,vector<T> b){
  int n=1;
  while(n<(int)a.size()+(int)b.size())n*=2;
  vector<comp>a_(n),b_(n);
  rep(i,a.size())a_[i]=a[i];
  rep(i,b.size())b_[i]=b[i];
  fft(n,a_,1);fft(n,b_,1);
  rep(i,n)a_[i]*=b_[i];
  fft(n,a_,-1);
  rep(i,n)a_[i]/=n;
  return a_;
}


// 要素数n, 要素の最大値をcとしたとき、n * c^2 <= 10^15 でなければ精度が保証されない。
vector<lint> integral_convolution(vector<lint> a,vector<lint> b){
  vector<comp>a_(a.size()),b_(b.size());
  rep(i,a.size())a_[i]=a[i];
  rep(i,b.size())b_[i]=b[i];
  vector<comp>ans=convolution(a_,b_);
  vector<lint>ret(ans.size());
  rep(i,ans.size())ret[i]=floor(ans[i].real()+0.5);
  return ret;
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
    ret[1]=l%p;
    return ret;
  }
  lint mid=(l+r+1)/2;
  vector<lint>fst=g(p,l,mid-1);
  vector<lint>snd=g(p,mid,r);
  vector<lint>ans=integral_convolution(fst,snd);
  rep(i,ans.size())ans[i]%=p;
  return ans;
}


lint f(string n,lint p){
  const lint mod=1e9+7;
  vector<lint> dig=parse(n,p);
  if(dig[0]==p-1){
    //propagate
    dig[0]=0;
    int car=1;
    for(int pos=1;pos<(int)dig.size();++pos){
      dig[pos]+=car;
      car=dig[pos]/p;
      dig[pos]%=p;
    }
    if(car>0)dig.push_back(car);
  }
  vector<lint> ans=g(p,1,dig[0]);
  lint ret=0;
  rep(i,dig[0]+1)
    if(ans[i]!=0)ret++;
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
