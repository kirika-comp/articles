typedef long long lint;

lint powmod(lint x,lint e,lint mod){
  lint prod=1;
  lint cur=x;
  while(e>0){
    if(e%2==1)prod=prod*cur%mod;
    cur=cur*cur%mod;
    e/=2;
  }
  return prod;
}
