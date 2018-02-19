## 前提知識
フェルマーの小定理から、a^(p-1)=1 (mod p)であることに注意しましょう。
a = x^2 (mod p)　となる　x が存在する場合、aを*平方剰余*、そうで無い場合aを*平方非剰余*と呼びます。
pが奇素数の時、0を除くと平方剰余と平方非剰余の割合は1:1です。
また、a!=0 (mod p) のときa^((p-1)/2) は mod p で 1　か -1 かのどちらかですが、aが平方剰余のとき1、平方非剰余のとき-1です。


## 問題
ある x について a = x^2 (mod p) が成り立つ a が与えられる。この時、x を求めよ。

## 解法
pがmod 4で3の時は簡単です。x = a^((p+1)/4)とすると、x^2 = a^((p+1)/2)です。ここで、a = y^2となるyが存在するので、a^((p-1)/2)=y^(p-1)=1 (mod p)です。
だから、x^2 = aが成り立ちます。

p が mod 4 で 1の時は結構複雑なことをします。ここではTonelli-Shanksの方法と呼ばれるアルゴリズムを説明します。

### Tonelli-Shanks (トネリ-シャンクス) のアルゴリズム
[reference](https://en.wikipedia.org/wiki/Tonelli%E2%80%93Shanks_algorithm)

入力: p: 素数, a (!= 0): 平方剰余

出力: r^2 = a (mod p) を満たすr

p = q * 2^s + 1 とします。 (s >= 1, qは奇数)

注意: 以下の疑似コードでは代入は全部同時に行います。特に5.で、tに代入する値は前のcによって決まります。

注意2: 本来の Tonelli-Shanks とは違いますが、筆者の地頭で復元できたのが以下のアルゴリズムなので、こちらの方が理解しやすいと思います。(効率は悪い)

1. z^((p-1)/2) = -1 (mod p) となるような z を選ぶ。このようなzは確率1/2でヒットするため、何回も繰り返せば必ず見つかる。
2. m := s, c:= z^q, t := a^q, r := a^((q + 1)/2) とする。以降 **不変量 r^2=at (mod p), t^(2^(m - 1)) = 1 (mod p), c^(2^(m-1)) = -1 (mod p)** を崩さないように注意して操作する。
3. 以降mを減らしていく。mが1なら終了。そうでなければ、t^(2^(m-2)) = 1 (mod p) なら4.へ、そうでなければ5.へ行く。
4. c := c^2 (mod p), m := m - 1, 6.へ行く。
5. c := c^2 (mod p), t := c^2 t (mod p), r := cr (mod p), m := m - 1, 6.へ行く。
6. 3.へ行く。

終了時にはm=1なので、t=1になっているはずで、そのときのrが求める値です。(不変量 r^2=at (mod p) に注意。)


C++での実装は以下のようになります。
```
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
```

例を挙げて見ていきましょう。
p = 41, a = 8 とします。

p = 5 * 2^3 + 1 なので、q = 5, s = 3 です。
z として、ここでは 7 をとります。

m := 3, c := 7^5 = 16807 = 38, t := 8^5 = 32768 = 9, r = 8^3 = 512 = 20 となります。 (mod 41 は適宜省略)

|m|c|t|r|
|---|---|---|---|
|3|38|9|20|
|2|9|40|22|
|1|40|1|34|


よって、plusminus 34 (= plusminus 7) が答えになります。


以上のアルゴリズムで、4.のパートに無駄があります。4.ではcとmしか変更していないので、t^(2^i)!=1となる最大のiが見つけられれば、4.の操作をまとめることができます。このアイデアを使うのが、本来の Tonelli-Shanks のアルゴリズムです。

(Wikipedia のTonelli-Shanks の説明)
