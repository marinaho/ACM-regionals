//ACM-ICPC SouthWestern 2010
//Assembly Line

#include <cstdio>
#include <cstring>

#define SIMMAX 27
#define LENMAX 210
#define INF 0x3f3f3f3f

char simb[SIMMAX];
int time[SIMMAX][SIMMAX], piesa[SIMMAX][SIMMAX], sir[LENMAX];
char sir_init[LENMAX];
int n, k;
int cost[LENMAX][LENMAX][SIMMAX];

int find(char a)
{
    int i;
    for(i = 0; i < SIMMAX; ++i)
        if(simb[i] == a) return i;
    return -1;
}

int main()
{
    int i, j, l, d, p, cost_min, piesa_rez = 0, ii, a, b;
    int first_time = 1;
    char aux;
    
  //  freopen("h.in", "r", stdin);
 //   freopen("h.out", "w", stdout);
    while(true)
    {
        scanf("%d\n", &k);
        if(k == 0) break;
        
        if(!first_time) printf("\n");
        else first_time = 0;
        for(i = 0; i < k; ++i)
            scanf("%c ", simb + i);

        for(i = 0; i < k; ++i)
            for(j = 0; j < k; ++j)
            {
                scanf("%d-%c", &time[i][j], &aux);
                piesa[i][j] = find(aux);             
            }
        scanf("%d", &l);
        for(ii = 0; ii < l; ++ii)
        {
             scanf("%s", &sir_init);
             n = strlen(sir_init);
             for(j = 0; sir_init[j] != NULL; ++j)
                 sir[j] = find(sir_init[j]);
                
             for(i = 0; i < n; ++i)
             {
                 for(j = 0; j < n; ++j)
                     for(p = 0; p < k; ++p)
                       cost[i][j][p] =  INF;
                 cost[i][i][sir[i]] = 0;
             }
             for(d = 1; d < n; ++d)
                 for(i = 0; i < n-d; ++i)
                     for(p = i; p < i+d; ++p)
                         for(a = 0; a < k; ++a)
                             for(b = 0; b < k; ++b)
                                 if((cost[i][p][a] != INF) && (cost[p+1][i+d][b] != INF) && (cost[i][i+d][ piesa[a][b] ] > cost[i][p][a] + cost[p+1][i+d][b] + time[a][b]))
                                     cost[i][i+d][ piesa[a][b] ] = cost[i][p][a] + cost[p+1][i+d][b] + time[a][b]; 
             cost_min = INF;
             for(p = 0; p < k; ++p)
                   if(cost[0][n-1][p] < cost_min)
                       cost_min = cost[0][n-1][p], piesa_rez = p;
             printf("%d-%c\n", cost_min, simb[piesa_rez]);
        }
    }
    return 0;
}
