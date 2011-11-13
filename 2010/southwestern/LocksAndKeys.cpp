//Locks and Keys
//ACM SothWestern 2010

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define VMAX 1510
#define debug 0

using namespace std;

vector<pair<int, int> > graf[VMAX];
vector<int> path;
            
bool viz[VMAX];
int keyAt[VMAX];
int keys[VMAX]; // keys[i] = j, j > -1 if we have key i, and key i is found in vertex j
int locks[VMAX];// locks[i] = j, j > -1 if we reached lock i, and lock[i] was found when going to vertex j
int sortTop[VMAX], ult, t[VMAX];
int V, X, Y, C;

bool dfs(int x)
{
     viz[x] = true;
     int cheie = keyAt[x], i;
     if(cheie > -1) 
     {
         keys[ cheie ] = x;
         if(locks[ cheie ] > -1) 
         {
             sortTop[++ult] = cheie;      
             dfs(locks[ cheie ]);
         }
     }
     for(i = 0; i < graf[x].size(); ++i)
     {
           pair<int, int> p = graf[x][i];
           if(viz[p.first]) continue;
           locks[p.second] = p.first;
           t[p.first] = x;
           if(p.second > -1 && keys[p.second] == -1) continue;
           if(p.second > -1) sortTop[++ult] = p.second;
           dfs(p.first);
     }
}
void goUp(int p)
{
    for(; p != X; p = t[p])
        path.push_back(t[p]);
}
void goDown(int p)
{
     if(t[p] != X) goDown(t[p]);
     path.push_back(p);
}
void get(int p)
{
     if(p == X) return;
     goDown(p);
     goUp(p);
}
int main()
{
    int i, p;
    
    freopen("i.in", "r", stdin);
    freopen("ii.out", "w", stdout);
    

    while(true) {
        scanf("%d %d %d %d", &V, &C, &X, &Y);
        if(V == 0 && C == 0 && X == 0 && Y == 0) break;
        memset(keyAt, -1, sizeof(keyAt));
        for(i = 0; i < C; ++i)
        {
            scanf("%d ", &p);
            keyAt[p] = i;
        }
        for(i = 0; i < V; ++i) graf[i].clear();
        for(i = 0; i < V-1; ++i)
        {
            int a, b, l;
            scanf("%d %d %d", &a, &b, &l);
            graf[a].push_back(make_pair(b, l));
            graf[b].push_back(make_pair(a, l));            
        }
        
        memset(viz, false, sizeof(viz));
        memset(keys, -1, sizeof(keys));
        memset(locks, -1, sizeof(locks));
        ult = -1;
        dfs(X);
        if(!viz[Y]) printf("Impossible\n");
        else {
             path.clear();
             path.push_back(X);
             
             if(debug) printf("\n");
             for(i = 0; i <= ult; ++i)
             {
                   if(debug) 
                   {
                      printf("%d, ", sortTop[i]);
                   }
                   get(keys[ sortTop[i] ]);
                   get(locks[ sortTop[i] ]);
             }
             if(debug) fflush(stdout);
             if(Y != X) goDown(Y);
             
             vector<int>::iterator it, it2;
             it = find(path.begin(), path.end(), Y);
             printf("%d:", it - path.begin());
             for(it2 = path.begin(); it2 <= it; ++it2)
                 printf(" %d", *it2);
             printf("\n");
        }
    }

    return 0;
}
