#include<random>
using namespace std;
typedef long long lint;

lint powmod(lint a,lint e,lint p){
  lint r=1;
  for(int i=63;i>=0;--i){
    r=r*r%p;
    if(e&1LL<<i)r=r*a%p;
  }
  return r;
}

// p:素数, aは0でなく、平方剰余
lint simplified_tonelli_shanks(lint p,lint a){
  mt19937 mt;
  if(powmod(a,(p-1)/2,p)!=1)return -1;
  lint q=p-1;
  lint m=0;
  while(q%2==0)q/=2,m++;
  lint z;
  do{
    z=mt()%p;
  }while(powmod(z,(p-1)/2,p)!=p-1);
  lint c=powmod(z,q,p);
  lint t=powmod(a,q,p);
  lint r=powmod(a,(q+1)/2,p);
  for(;m>1;--m){
    lint tmp=powmod(t,1<<(m-2),p);
    if(tmp!=1)
      r=r*c%p,t=t*(c*c%p)%p;
    c=c*c%p;
  }
  return r;
}
