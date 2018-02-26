#include<algorithm>
#include<bitset>
#include<cassert>
#include<iostream>
#include<vector>
using namespace std;
typedef long long lint;
#define rep(i,n)for(int i=0;i<(int)(n);++i)

const int N=4000;
typedef bitset<N> bs;
const lint MOD=998244353;

bs read(){
  string s;
  cin>>s;
  int l=s.length();
  bs ret;
  rep(i,l)ret[i]=s[l-i-1]=='1';
  return ret;
}

// a%b
bs rem(bs a,bs b){
  int hi=-1;
  rep(i,N)
    if(b[i])hi=i;
  assert(hi>=0);
  for(int i=N-hi-1;i>=0;--i)
    if(a[i+hi])a^=b<<i;
  return a;
}

bs gcd(bs a,bs b){
  while(b.count()!=0){
    a=rem(a,b);
    swap(a,b);
  }
  return a;
}

int main(){
  int n;
  cin>>n;
  bs x=read();
  vector<bs> s(n);
  rep(i,n)s[i]=read();
  bs g=s[n-1];
  rep(i,n-1)g=gcd(s[i],g);
  lint ans=0;
  lint cur=1;
  int hi=-1;
  rep(i,N)
    if(g[i])hi=i;
  rep(i,N-hi){
    if(x[i+hi])ans=(ans+cur)%MOD;
    cur=cur*2%MOD;
  }
  bs y=x^rem(x,g);
  bool lt=false; //x<y?
  for(int i=N-1;i>=0;--i){
    if(x[i]!=y[i]){
      lt=x[i]<y[i];
      break;
    }
  }
  if(!lt)ans=(ans+1)%MOD; // y<=x; counts y
  cout<<ans<<endl;
}
