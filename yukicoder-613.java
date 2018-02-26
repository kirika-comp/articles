import java.util.*;

class Main {
    static long powerMod(long x, long exponent,long m) {
	long prod = 1;
	for (int i = 63; i >= 0; --i) {
	    prod = (prod * prod) % m;
	    if ((exponent & 1L << i) != 0) {
		prod = (prod * x) % m;
	    }
	}
	return prod;
    }
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        long n=scan.nextLong();
        long m=scan.nextLong();
        long p=m==2||m%12==1||m%12==11?m-1:m+1;
        long e=powerMod(2,n,p);
        long x=1,y=0;
        for(int i=31;i>=0;--i){
            long z=(x*x+3*y*y)%m,w=2*x*y%m;
            x=z;y=w;
            if((e&1L<<i)!=0){
                z=(2*x+3*y)%m;w=(x+2*y)%m;
                x=z;y=w;
            }
        }
        System.out.println((2*x+m-2)%m);
    }
}
