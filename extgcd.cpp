#include <iostream>
using namespace std;
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

int main(){
  lint a,b;
  cin>>a>>b;
  lint x,y;
  lint g=ext_gcd(a,b,x,y);
  cout<<a<<" "
      <<b<<" "<<x<<" "<<y
      <<endl;
  cout<<g<<endl;
}
