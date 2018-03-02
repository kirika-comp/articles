#include<complex>
#include<iostream>
#include<utility>
#include<vector>
using namespace std;
typedef long long lint;
#define rep(i,n)for(int i=0;i<(int)(n);++i)

typedef complex<double> comp;

// n は2冪で、a.size()==n, zetaは1のn乗根
void fft(int n,vector<comp> &a,comp zeta) {
  // ビット反転は http://math314.hateblo.jp/entry/2015/05/07/014908 を参考にしている。
  int i = 0;
  for (int j = 1; j < n - 1; ++j) {
    for (int k = n >> 1; k >(i ^= k); k >>= 1);
    if (j < i) swap(a[i], a[j]);
  }
  vector<comp>zeta_pow;
  for(int m=1;m<n;m*=2){
    zeta_pow.push_back(zeta);
    zeta*=zeta;
  }
  int ind=zeta_pow.size();
  // ここも http://math314.hateblo.jp/entry/2015/05/07/014908 を参考にしている。
  for(int m=1;m<n;m*=2){
    comp base=zeta_pow[--ind];
    comp fac=1;
    for(int y=0;y<m;++y){
      for(int x=0;x<n;x+=2*m){
	int u=x+y;
	int v=x+y+m;
	comp s=a[u]+fac*a[v];
	comp t=a[u]-fac*a[v];
	a[u]=s;a[v]=t;
      }
      fac*=base;
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
  double theta=acos(-1)/n*2;
  comp zeta(cos(theta),sin(theta));
  fft(n,a_,zeta);fft(n,b_,zeta);
  rep(i,n)a_[i]*=b_[i];
  zeta.imag(-zeta.imag());
  fft(n,a_,zeta);
  rep(i,n)a_[i]/=n;
  return a_;
}

// 要素数n, 要素の最大値をcとしたとき、n * c^2 <= 10^15 でなければ制度が保証されない。
vector<lint> integral_convolution(vector<lint> a,vector<lint> b){
  vector<comp>a_(a.size()),b_(b.size());
  rep(i,a.size())a_[i]=a[i];
  rep(i,b.size())b_[i]=b[i];
  vector<comp>ans=convolution(a_,b_);
  vector<lint>ret(ans.size());
  rep(i,ans.size())ret[i]=floor(ans[i].real()+0.5);
  return ret;
}

int main(){
  vector<lint> a(3);
  a[0]=1,a[1]=2,a[2]=3;
  vector<lint> b(5);
  b[0]=1,b[1]=10,b[2]=15,b[3]=11,b[4]=1;
  rep(i,5)b[i]=-b[i];
  vector<lint> ab=integral_convolution(a,b);
  // -1 -12 -38 -71 -68 -35 -3 0
  rep(i,ab.size())cout<<" "<<ab[i];
  cout<<endl;
}
