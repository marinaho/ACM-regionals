//Fake Scoreboard - ACM SWERC 2010

#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define MAXN 200

vector<int> graf[MAXN];
int t, p, v[MAXN], c[MAXN][MAXN], f[MAXN][MAXN], queue[MAXN], tt[MAXN];

bool bfs()
{
     int pp, u, i;
     memset(tt, -1, sizeof(tt));
     queue[u = 0] = 0;
     tt[0] = 0;
     for(pp = 0; pp <= u; ++pp)
     {
         int src = queue[pp];
         if(src == t+p+1) continue;
         for(i = 0; i < graf[src].size(); ++i)
         {
             int y = graf[src][i];
             if(c[src][y] <= f[src][y] || tt[y] != -1) continue;
             queue[++u] = y;
             tt[y] = src;
         }
     }
     return tt[t+p+1] != -1;
}

int calcFlux()
{
    int flux = 0, i, j;
    for(; bfs();)
        for(i = 0; i < graf[t+p+1].size(); ++i)
        {
            int y = graf[t+p+1][i];
            if(tt[y] == -1) continue;
            tt[t+p+1] = y;
            bool ok = true;
            for(j = t+p+1; j != 0 && ok; j = tt[j])
                if(c[tt[j]][j] <= f[tt[j]][j]) ok = false;
            if(!ok) continue;
                      
            for(j = t+p+1; j != 0; j = tt[j])
                ++f[tt[j]][j], --f[j][tt[j]];
            ++flux;
        }
    return flux;
}
void add(int a, int b, int cp)
{
     graf[a].push_back(b);
     graf[b].push_back(a);
     c[a][b] = cp;
}
int main()
{
    int i, j, flux, sum1, sum2, k;
    
//    freopen("d.in", "r", stdin);
//    freopen("d.out", "w", stdout);
    
    bool first = true;
    for(;;)
    {
        scanf("%d %d", &t, &p);
        if(t == 0 && p == 0) break;
        if(!first) printf("\n");
        else first = false;
        for(i = 1, sum1 = 0, sum2 = 0; i <= t+p; ++i)
        {
            scanf("%d", &v[i]);
            if(i <= t) sum1 += v[i];
            else sum2 += v[i];
        }   
        
        if(sum1 != sum2) 
        {
            printf("Impossible\n");
            continue;
        }
        memset(c, 0, sizeof(c));
        memset(f, 0, sizeof(f));
        for(i = 0; i <= t + p + 1; ++i) graf[i].clear();
        
        for(i = 1; i <= t; ++i)
            add(0, i, v[i]);

        for(i = t + 1; i <= t + p; ++i)
            add(i, t+p+1, v[i]);
            
        for(i = 1; i <= t; ++i)
            for(j = t+1; j <= t+p; ++j)
                add(i, j, 1);
           
           
        if(calcFlux() != sum1)
        {
            printf("Impossible\n");
            continue;
        } 
        for(i = 1; i <= t; ++i)
        {
            for(j = t+1; j <= t+p; ++j)
                if(f[i][j]) 
                {
                    c[i][j] = 0; c[j][i] = -0x3f3f3f3f;                    
                    --f[0][i]; ++f[i][0]; --f[j][t+p+1]; ++f[t+p+1][j];
                    if(calcFlux() > 0)
                    {
                        printf("N");
                        continue;
                    }    
                    printf("Y");
                    c[i][j] = 1; c[j][i] = 0;
                    ++f[0][i]; --f[i][0]; ++f[j][t+p+1]; --f[t+p+1][j];
                }
                else 
                {
                     f[i][j] = c[i][j]; f[j][i] = 0;
                     printf("N");   
                }
            printf("\n");
        }
    }    
    return 0;
}
