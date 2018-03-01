typedef long long lint;

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
