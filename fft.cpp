#include<cmath>
#include<complex>
#include<iostream>
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
