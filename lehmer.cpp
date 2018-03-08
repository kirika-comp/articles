#include<utility>
#include<random>
using namespace std;
typedef long long lint;
typedef pair<lint,lint>pll; // <a,b> は a*x+b を表す。

lint powmod(lint a,lint e,lint p){
  a%=p;
  lint ans=1;
  for(int i=63;i>=0;--i){
    ans=ans*ans%p;
    if(e&1LL<<i)ans=ans*a%p;
  }
  return ans;
}

// 多項式の掛け算 mod x^2-ca.first*x-ca.second
pll mul_poly(pll a,pll b,pll ca,lint p){
  lint s=a.first*b.first%p;
  lint t=(a.first*b.second+a.second*b.first)%p;
  lint u=a.second*b.second%p;
  t=(t+ca.first*s)%p;
  u=(u+ca.second*s)%p;
  return pll(t,u);
}

// 2次体上の冪乗
pll pow_poly(pll a,lint e,pll ca,lint p){
  pll ans(0,1);
  for(int i=63;i>=0;--i){
    ans=mul_poly(ans,ans,ca,p);
    if(e&1LL<<i)ans=mul_poly(ans,a,ca,p);
  }
  return ans;
}

// p:奇素数, a:mod pの平方剰余であることが要請される。
lint lehmer_mod_sqrt(lint p,lint a){
  a%=p;
  if(a==0)return 0;
  lint c,t;
  mt19937 mt;
  do{
    c=mt()%p;
    t=(c*c+p-a)%p;
  }while(powmod(t,(p-1)/2,p)!=p-1);
  pll ans=pow_poly(pll(1,0),(p-1)/2,pll((2*c)%p,(p-t)%p),p);
  ans.second=(ans.second+p-1)%p;// 最大公約数
  return (c+powmod(ans.first,p-2,p)*ans.second+p)%p;
}
