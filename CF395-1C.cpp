#include<algorithm>
#include<cstdio>
#include<vector>
#include<random>
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

void add(lint &x,lint y,lint m){
  x=(x+y)%m;
}

int main(){
  lint m;
  int n;
  scanf("%lld%d",&m,&n);
  vector<lint>a(n);
  rep(i,n)scanf("%lld",&a[i]);
  if(m<=3){
    // brute force
    sort(a.begin(),a.end());
    rep(x,m){
      rep(d,m){
	vector<lint> b(n);
	rep(i,n)b[i]=(x+d*i)%m;
	sort(b.begin(),b.end());
	if(a==b){
	  printf("%d %d\n",x,d);
	  return 0;
	}
      }
    }
    puts("-1");
    return 0;
  }
  if(n==m){
    puts("0 1");
    return 0;
  }
  lint sum=0;
  lint squsum=0;
  rep(i,n){
    add(sum,a[i],m);
    add(squsum,a[i]*a[i],m);
  }
  lint avg=sum*powmod(n,m-2,m)%m;
  lint vari=squsum*powmod(n,m-2,m)%m;
  add(vari,avg*(m-avg),m);
  lint d;
  if(2<=n&&n<=m-2){
    lint d2=vari*12%m;
    d2=d2*powmod(((lint)n*n-1)%m,m-2,m)%m;
    
    d=simplified_tonelli_shanks(m,d2);
    if(d==-1){
      puts("-1");
      return 0;
    }
  }else if(n==1){
    d=0;
  }else{
    d=1;
  }
  lint x=avg;
  lint tmp=(n-1)*d%m;
  tmp=(tmp*(m+1)/2)%m;
  add(x,m-tmp,m);
  vector<lint> b(n);
  rep(i,n)b[i]=(x+d*i)%m;
  sort(a.begin(),a.end());
  sort(b.begin(),b.end());
  if(a==b){
    printf("%lld %lld\n",x,d);
  }else{
    puts("-1");
  }
}
