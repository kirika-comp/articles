typedef long long lint;
const lint mod=1e9+7; // m を入れる
const int N=10000000;
// inv[n] は n^{-1} mod m
lint inv[N];
// http://takapt0226.hatenablog.com/entry/2013/03/15/213551
void ini(){
  inv[1]=1;
  for (int i=2;i<N;++i)
    inv[i]=inv[mod%i]*(mod-mod/i)%mod;
}
