typedef long long lint;
const lint mod=1e9+7; // m を入れる
const int N=10000000;
lint fac[N]; // fac[n] は n! mod m
void ini(){
  fac[0]=1%mod;
  for(int i=1;i<N;++i)fac[i]=fac[i-1]*i%mod;
}
