typedef long long lint;

lint powmod(lint x,lint e,lint mod){
  lint prod=1%mod;
  for(int i=63;i>=0;--i){
    prod=prod*prod%mod;
    if(e&1LL<<i)prod=prod*x%mod;
  }
  return prod;
}
