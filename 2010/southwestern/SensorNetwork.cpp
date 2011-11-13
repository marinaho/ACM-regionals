//Sensor Network - ACM 2010 SouthWestern

#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

#define MAXM 62000
#define MAXN 400

using namespace std;

int n, m;
int cost[MAXN][MAXN];

struct muchie {
    int x, y;
}graf[MAXM];

struct comp {
    bool operator ()(muchie a, muchie b)
    {
        return cost[a.x][a.y] < cost[b.x][b.y];
    }
};

vector<int> graf2[MAXN];
int tata[MAXN];

int dfs(int src)
{
    int i, y, x;
    for(i = 0; i < graf2[src].size(); ++i)
    {
          y = graf2[src][i];
          if(tata[y] == -1) 
          {
              tata[y] = src;
              if(!dfs(y)) return 0;
          }
          else if(y != tata[src])
          {
               int min = cost[y][src], a = y, b = src;
               for(x = src; x != y; x = tata[x])
                     if(min > cost[x][ tata[x] ])
                         min = cost[x][ tata[x] ], a = x, b = tata[x];
               graf2[a].erase( find(graf2[a].begin(), graf2[a].end(), b));
               graf2[b].erase( find(graf2[b].begin(), graf2[b].end(), a));               
               return 0;
          }
    }
    return 1;
}

int calc()
{
    int i, j, max = 0, min = 0x3f3f3f3f;
    for(i = 0; i < n; ++i)
         for(j = 0; j < graf2[i].size(); ++j)
               if(cost[i][ graf2[i][j] ] > max) max = cost[i][ graf2[i][j] ];
               else if(cost[i][ graf2[i][j] ] < min) min = cost[i][ graf2[i][j] ];
    return max - min;
}
int main()
{
    int i, j, k;
    
//    freopen("g.in", "r", stdin);
//    freopen("g.out", "w", stdout);

    for(;;)
    {
        scanf("%d", &n);
        if(n == 0) break;
        scanf("%d", &m);
        for(i = 0; i < m; ++i)
        {
              int c;
              scanf("%d %d %d", &graf[i].x, &graf[i].y, &c);
              cost[graf[i].x][graf[i].y] = c;
              cost[graf[i].y][graf[i].x] = c;              
        }
        sort(graf, graf + m, comp());
        
        int nmuchii = 0;
        int best = 0x3f3f3f3f, temp;
        for(i = 0; i < n; ++i) graf2[i].clear();
        for(i = 0; i < m; ++i)
        {
             int a = graf[i].x, b = graf[i].y;
             graf2[a].push_back(b); graf2[b].push_back(a);
             memset(tata, -1, sizeof(tata));
             tata[a] = a;
             nmuchii += dfs(a);
             if(nmuchii == n-1)
                 if(best > (temp = calc()) )
                         best = temp;
        }  
        printf("%d\n", best);    
    }       
    fflush(stdout); 
    return 0;
}
