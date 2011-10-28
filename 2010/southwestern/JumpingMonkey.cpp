#include <cstdio>
#include <vector>

#define NMAX 25
#define MAX 1000
#define STATEMAX (1<<21)+5

using namespace std;

int n, m;
int graf[NMAX];
unsigned int first[NMAX], last[NMAX];
int coada[STATEMAX], prevState[STATEMAX], pas[STATEMAX];
bool viz[STATEMAX];

void afis()
{
     int drum[MAX];
     int i, npas = 0, u = 0;
     for(i = 0; prevState[i] != -1; i = prevState[i])
         ++npas, drum[u++] = pas[i];
     printf("%d:",npas);
     for(i = u-1; i >= 0; --i)
         printf(" %d", drum[i]);
     printf("\n");
}

void solve()
{
     int p = 0, u = 0, i, src;
     unsigned int nxSt;
     bool stop = false;
     
     for(i = 0; i < 1<<n; ++i)
           coada[i] = prevState[i] = 0, viz[i] = false;
     coada[0] = (1<<n) - 1;
     viz[(1<<n) - 1] = true;
     prevState[(1<<n) - 1] = -1;
     for(;p <= u && !stop; ++p)
     {
         src = coada[p];
         first[0] = last[n] = 0;         
         for(i = 0; i < n-1; ++i)
             if(src & (1<<i)) first[i+1] = first[i] | graf[i];
             else first[i+1] = first[i];
         for(i = n; i > 0; --i)
             if(src & (1<<i)) last[i - 1] = last[i] | graf[i];
             else last[i - 1] = last[i];
         for(i = 0; i < n && !stop; ++i)
             if(src & (1 << i))
             {
                 nxSt = first[i] | last[i];
                 if(!viz[nxSt])
                 {
                     coada[++u] = nxSt;
                     viz[nxSt] = true;
                     prevState[nxSt] = src;
                     pas[nxSt] = i;
                     if(nxSt == 0) stop = true, afis();
                 }
             }
     }
     if(!stop) printf("Impossible\n");
}
int main()
{
    int i, x, y;
    
//    freopen("f.in", "r", stdin);
//   freopen("f.out", "w", stdout);
    
    for(;;)
    {
        scanf("%d %d", &n, &m);
        if(!n && !m) break;
        for(i = 0; i < n; ++i) graf[i] = 0;
        for(i = 0; i < m; ++i)
        {
            scanf("%d %d", &x, &y);
            graf[x] |= 1 << y; graf[y] |= 1 << x;
        }
        solve();
    }
    return 0;
}
