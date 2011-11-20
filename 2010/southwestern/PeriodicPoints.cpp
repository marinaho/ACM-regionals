//ACM-ICPC SouthWestern European 2010
//Periodic Points

#include <cstdio>
#include <cstring>
#include <vector>

#define MAXM 128

#define min(x, y) ((x) < (y) ? (x):(y))
#define max(x, y) ((x) > (y) ? (x):(y))
#define abs(x) (x) > 0 ? (x) : (-(x))

using namespace std;

typedef vector<vector<int> > matrix;

int m, n, mod;
int v[MAXM];

#define v (v+1)

int sign(int x)
{
    if(x == 0) return x;
    return x > 0 ? 1 : -1;
}
void computeA(matrix &A)
{
     int i, j;
     for(i = 0; i < m; ++i)
         for(j = min(v[i], v[i+1]); j < max(v[i], v[i+1]); ++j) A[i][j] = 1;
}
matrix multiply(int n, const matrix &A, const matrix &B)
{
    int i, j, k;
    matrix C(n, vector<int>(n));
    for(i = 0; i < n; ++i)
        for(j = 0; j < n; ++j)
            for(k = 0; k < n; ++k)
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
    return C;
}
matrix computeAlaN(int n, matrix &A)
{
    int i;
    matrix res(m, vector<int>(m));
    for(i = 0; i < m; ++i) res[i][i] = 1;
    
    for(i = 0; (1<<i) <= n; ++i)
    {
        if(n & (1<<i)) res = multiply(m, res, A);
        A = multiply(m, A, A);
    }   
    
    return res;    
}
void solve()
{
     int rez = 0, i, j;
     matrix A(m, vector<int>(m));             
     computeA(A);
     matrix An = computeAlaN(n, A);
    
     for(i = 0; i < m; ++i)
           rez = (rez + An[i][i]) % mod;
             
     v[-1] = v[0]; v[m+1] = v[m];
     bool inf = false;
     for(i = 0; i <= m && !inf; ++i)
     {
         int x = i, y = i+1, dir[2] = {1, -1};
         bool can_inf = true;
         for(j  = 1; j <= n; ++j)
         {
             if(dir[0] == 1) dir[0] = sign(v[x] - v[x-1]);
             else if(dir[0] == -1) dir[0] =  sign(v[x] - v[x+1]);
             if(dir[1] == 1) dir[1] = sign(v[x] - v[x-1]);
             else if(dir[1] == -1) dir[1] =  sign(v[x] - v[x+1]);
  
             can_inf &= (abs(v[x] - v[y]) == 1);
             
             x = v[x];   y = v[y];
         }
         if(x == i)
         {
              ++rez;
              if(dir[0] == 1) --rez;
              if(dir[1] == -1) --rez;
              if(rez < 0) rez += mod;
              if(i < m && can_inf == true && x == i && dir[1] == -1) {inf = true;}
         }   
     }

     if(inf) printf("Infinity\n");
     else printf("%d\n", rez % mod);
}
int main()
{
//    freopen("B.in", "r", stdin);
//    freopen("B.out", "w", stdout);
    int i;
    scanf("%d", &m);
    while(m)
    {
        for(i = 0; i <= m; ++i)
            scanf("%d", &v[i]);
        scanf("%d %d", &n, &mod);
        solve();
        scanf("%d", &m);
    }
    return 0;
}
