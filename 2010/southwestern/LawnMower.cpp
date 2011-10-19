//ACM-ICPC SouthWestern Europe 2010
//Lawn Mower

#include <cstdio>
#include <algorithm>

#define MAX 1001
#define L 100
#define W 75

using namespace std;

int nx, ny;
double w;
double v[MAX], u[MAX];

int solve()
{
    if(v[0] > w/2) return 0; 
    if(u[0] > w/2) return 0; 

    if(v[nx-1] + w/2 < W) return 0;    
    if(u[ny-1] + w/2 < L) return 0;

    for(int i = 1; i < nx; ++i)        
        if(v[i] > v[i-1] + w) return 0;
    for(int i = 1; i < ny; ++i)
        if(u[i] > u[i-1] + w) return 0;
    return 1;
}
int main()
{
 //   freopen("A.in", "r", stdin);
 //   freopen("A.out", "w", stdout);

    scanf("%d %d %lf", &nx, &ny, &w);
    while(nx || ny || w) {
        for(int i = 0; i < nx; ++i)            
            scanf("%lf", &v[i]);
        for(int i = 0; i < ny; ++i)            
            scanf("%lf", &u[i]);
        sort(v, v + nx);
        sort(u, u + ny);
        if(solve()) printf("YES\n");
        else printf("NO\n");
        scanf("%d %d %lf", &nx, &ny, &w);
    }
    return 0;
}
