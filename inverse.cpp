typedef long long lint;
const lint mod=1e9+7; // m を入れる
const int N=10000000;
lint ext_gcd(lint a,lint b,lint&x,lint&y){
  if(b==0){
    x=1;y=0;return a;
  }
  lint q=a/b;
  lint g=ext_gcd(b,a-q*b,x,y);
  lint z=x-q*y;
  x=y;y=z;
  return g;
}

// aのmod mにおける逆元を返す。aとmは互いに素であることが要請される。
lint invmod(lint a,lint m){
  lint x,y;
  ext_gcd(a,m,x,y);
  x%=m;
  if(x<0)x+=m;
  return x;
}
// fac[n] は n! mod m, invfac[n] は n!^{-1} mod m, inv[n] は n^{-1} mod m
lint fac[N], invfac[N], inv[N];
void ini(){
  fac[0]=1%mod;
  for(int i=1;i<N;++i)fac[i]=fac[i-1]*i%mod;
  invfac[N-1]=invmod(fac[N-1],mod);
  for(int i=N-2;i>=0;--i)invfac[i]=invfac[i+1]*(i+1)%mod;
  for(int i=1;i<N;++i)inv[i]=invfac[i]*fac[i-1]%mod;
}
