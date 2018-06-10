typedef long long lint;
const lint mod=1e9+7; // m を入れる
const int N=10000000;
lint pw[N]; // pw[n] は c^n mod m
void ini(lint c){
  pw[0]=1%mod;
  for(int i=1;i<N;++i)pw[i]=pw[i-1]*c%mod;
}
