#include<utility>
#include<random>
using namespace std;
typedef long long lint;
typedef pair<lint,lint>pll; // 2次体の数をエンコードするためのもの。(x,y) は x+y*theta を表す。

lint powmod(lint a,lint e,lint p){
  a%=p;
  lint ans=1;
  for(int i=63;i>=0;--i){
    ans=ans*ans%p;
    if(e&1LL<<i)ans=ans*a%p;
  }
  return ans;
}

// 2次体上の掛け算
pll mul_quad(pll a,pll b,lint theta,lint p){
  lint x=a.first*b.first+(theta*a.second%p)*b.second;
  x%=p;
  lint y=a.first*b.second+a.second*b.first;
  y%=p;
  return pll(x,y);
}

// 2次体上の冪乗
pll pow_quad(pll a,lint e,lint theta,lint p){
  pll ans(1,0);
  for(int i=63;i>=0;--i){
    ans=mul_quad(ans,ans,theta,p);
    if(e&1LL<<i)ans=mul_quad(ans,a,theta,p);
  }
  return ans;
}

// p:奇素数, a:mod pの平方剰余であることが要請される。
lint cipolla(lint p,lint a){
  a%=p;
  if(a==0)return 0;
  lint c,t;
  mt19937 mt;
  do{
    c=mt()%p;
    t=(c*c+p-a)%p;
  }while(powmod(t,(p-1)/2,p)!=p-1);
  pll ans=pow_quad(pll(c,1),(p+1)/2,t,p);// 証明中のx+y*theta
  return ans.first;
}
