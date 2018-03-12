#include<iostream>
using namespace std;
typedef long long lint;
typedef pair<lint,lint>pll; // ガウス整数の表現用。<a,b>はa+biを表す。

// a/bに一番近い整数を返す。
lint quo_nearest(lint a,lint b){
  lint q=a/b;
  lint r=a-q*b;
  if(abs(r)>abs(r-b))return q+1;
  if(abs(r)>abs(r+b))return q-1;
  return q;
}

// ガウス整数の剰余を計算する。一番絶対値が小さいものを返す。
pll rem_gaussian(pll a,pll b){
  lint bnorm=b.first*b.first+b.second*b.second;
  lint x=a.first*b.first+a.second*b.second;
  lint y=-a.first*b.second+a.second*b.first;
  // a/bに一番近いガウス整数をqとして、a-q*bを計算する。a/b=(x+yi)/bnorm なので、x/bnorm,y/bnormに一番近い整数がわかればよい。
  lint qx=quo_nearest(x,bnorm);
  lint qy=quo_nearest(y,bnorm);
  return pll(a.first-qx*b.first+qy*b.second,a.second-qx*b.second-qy*b.first);
}

// ガウス整数の最大公約数を計算する。
pll gcd_gaussian(pll a,pll b){
  while(b!=pll(0,0)){
    pll c=rem_gaussian(a,b);
    a=b;b=c;
  }
  return a;
}

int main(){
  lint p,q;
  int n;
  cin>>p>>q>>n;
  pll g=gcd_gaussian(pll(p,q),pll(p,-q));
  int ans=0;
  while(n--){
    lint x,y;
    cin>>x>>y;
    ans+=g==pll(0,0)?(x==0&&y==0):rem_gaussian(pll(x,y),g)==pll(0,0);
  }
  cout<<ans<<endl;
}
