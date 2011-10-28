//ACM ICPC SouthWestern Europe 2010
//3-sided dice
//Geometry - Determine if a point is in triangle interior 3D

#include <cstdio>
#include <cmath>

/*
* Pt calc det |a1 a2 1|
*             |a3 a4 1|
*             |a5 a6 1|
*/
#define det(a1,a2,a3,a4,a5,a6) a1*(a4-a6) + a3*(a6-a2) + a5*(a2-a4)
#define EPS 1e-6

bool isZero(long double a)
{
	return (a > 0 ? a: -a) < EPS;
}
long long min(long long a, long long b, long long c)
{
	long long min = a;
	if(b < min) min = b;
	if(c < min) min = c;
	return min;
}
long long max(long long a, long long b, long long c)
{
	long long max = a;
	if(b > max) max = b;
	if(c > max) max = c;
	return max;
}
int main()
{
//    freopen("j.in", "r", stdin);
//    freopen("j.out", "w", stdout);
    
    long long x1, x2, x3, y1, y2, y3, z1, z2, z3, x, y, z, temp1, temp2, temp3;
    long double sabc, sabm, sbcm, sacm, t1, t2, t3;
    for(;;)
    {
           scanf("%lld %lld %lld", &x1, &y1, &z1);
           if(!x1 && !y1 && !z1) break;
           scanf("%lld %lld %lld", &x2, &y2, &z2);            
           scanf("%lld %lld %lld", &x3, &y3, &z3);           
           scanf("%lld %lld %lld", &x, &y, &z);            

		   //Ariile tri. ABC, ABM, BCM, ACM
           sabc = 1./2 * sqrt((long double)(temp1 = det(x1,y1,x2,y2,x3,y3))*temp1 + (temp2 = det(y1,z1,y2,z2,y3,z3))*temp2 + (temp3 = det(x1,z1,x2,z2,x3,z3))*temp3 ); 
           sabm = 1./2 * sqrt((long double)(temp1 = det(x1,y1,x2,y2,x,y))*temp1 + (temp2 = det(y1,z1,y2,z2,y,z))*temp2 + (temp3 = det(x1,z1,x2,z2,x,z))*temp3 );
           sacm = 1./2 * sqrt((long double)(temp1 = det(x1,y1,x3,y3,x,y))*temp1 + (temp2 = det(y1,z1,y3,z3,y,z))*temp2 + (temp3 = det(x1,z1,x3,z3,x,z))*temp3 );
           sbcm = 1./2 * sqrt((long double)(temp1 = det(x2,y2,x3,y3,x,y))*temp1 + (temp2 = det(y2,z2,y3,z3,y,z))*temp2 + (temp3 = det(x2,z2,x3,z3,x,z))*temp3 );
           
          // printf("%lf %lf %lf %lf\n", sabc, sabm, sbcm, sacm);

           if(isZero(sabc - sabm - sbcm - sacm)) 
		   {
			   if(!isZero(sabc) && (isZero(sabm) || isZero(sbcm) || isZero(sacm)))
			   {//point is on an edge
				   printf("NO\n");
				   continue;
			   }
			   if(isZero(sabc))
			   {//points are all on the same line and M must be in the segment interior
				   long long xm = min(x1, x2, x3), xM = max(x1,x2,x3);
				   long long ym = min(y1, y2, y3), yM = max(y1,y2,y3);
				   long long zm = min(z1, z2, z3), zM = max(z1,z2,z3);
				   if((xm < x && x < xM) || (ym < y && y < yM) || (zm < z && z < zM))
					   printf("YES\n");
				   else printf("NO\n");
			   }
			   else printf("YES\n");
		   }
		   else printf("NO\n");
    }
    return 0;
}

