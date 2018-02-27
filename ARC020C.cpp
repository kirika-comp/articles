#include<iostream>
#include<vector>
using namespace std;
typedef long long lint;
#define rep(i,n)for(int i=0;i<(int)(n);++i)

lint powmod(lint x,lint e,lint mod){
  lint prod=1%mod;
  for(int i=63;i>=0;--i){
    prod=prod*prod%mod;
    if(e&1LL<<i)prod=prod*x%mod;
  }
  return prod;
}

lint f(lint y,lint z,lint mod){
  if(z==0)return 0;
  if(z%2==0){
    lint fac=1+powmod(y,z/2,mod);
    return fac*f(y,z/2,mod)%mod;
  }
  return (1+y*f(y,z-1,mod))%mod;
}

int main(){
  int n;
  cin >> n;
  vector<lint> a(n),l(n);
  rep(i,n)cin>>a[i]>>l[i];
  lint mod;
  cin>>mod;
  lint ans=0;
  rep(i,n){
    lint enc=1;
    while(a[i]>=enc)enc*=10; // enc=10^{b_i}
    ans=ans*powmod(enc%mod,l[i],mod)%mod;
    ans=(ans+a[i]*f(enc%mod,l[i],mod))%mod;
  }
  cout<<ans<<endl;
}
