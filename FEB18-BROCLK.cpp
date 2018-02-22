#include<iostream>
using namespace std;
typedef long long lint;
typedef pair<lint,lint>pll;
const lint mod=1e9+7;

lint powmod(lint x,lint e){
  lint c=1;
  for(int i=63;i>=0;--i){
    c=c*c%mod;
    if(e&1LL<<i)c=c*x%mod;
  }
  return c;
}

pll mul_pll(pll a,pll b,lint c){
  lint x=a.first*b.first%mod;
  lint nx=a.second*b.second%mod;
  x=(x+nx*c)%mod;
  lint y=(a.first*b.second+a.second*b.first)%mod;
  return pll(x,y);
}

pll pow_pll(pll a,lint e,lint c){
  pll p(1,0);
  for(int i=63;i>=0;--i){
    p=mul_pll(p,p,c);
    if(e&1LL<<i)p=mul_pll(p,a,c);
  }
  return p;
}

int main(){
  int tt;
  cin>>tt;
  while(tt--){
    lint l,d,t;
    cin>>l>>d>>t;
    lint cos=d*powmod(l,mod-2)%mod;
    lint s2=(cos*cos%mod)+mod-1;
    s2%=mod;
    lint ans=pow_pll(pll(cos,1),t,s2).first;
    cout<<ans*l%mod<<endl;
  }
}
