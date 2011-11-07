//Palindromic DNA
//SouthWestern European Reagional ACM 2010


#include <cstdio>
#include <cstring>
#include <vector>

#define NMAX 10010

using namespace std;

int N, T;
char sir[NMAX];

vector<int> cand[NMAX];
int aux[NMAX], comp[NMAX], posibil[NMAX][4], color[NMAX], prev[NMAX];
char adn[] = "AGTC";

int rad(int i)
{
    int t, t2, temp;
    for(t = i; comp[t] != t; t = comp[t]) ;
    for(t2 = i; t2 != t; )
           temp = t2,
           t2 = comp[t2],
           comp[temp] = t;
    return t;
}
void uneste(int a, int b)
{
     int t1 = rad(a), t2 = rad(b);
     comp[t1] = t2;
}

char next(char c)
{
     int i;
     for(i = 0; i < 4; ++i)
         if(adn[i] == c) return adn[(i+1)%4];
}
bool posColor(int nrComp, char cul)
{
     int i, ii, prev;
     for(ii = 0; ii < cand[nrComp].size(); ++ii)
     {
         i = cand[nrComp][ii];
         if(sir[i] == cul) continue;
         else if(next(next(sir[i])) == cul) return false;
         else if(ii > 0 && (prev = cand[nrComp][ii-1]) == i-1 && sir[prev] != cul) return false;
     }
    return true;
}
int index(char c)
{
     int i;
     for(i = 0; i < 4; ++i)
         if(adn[i] == c) return i;
     return 0;
}
bool set(int ncomp, int c)
{
     int i, ii;  
     
     if(color[ncomp] != -1) return color[ncomp] == c;
     if(!posibil[ncomp][c]) return false;
             
     color[ncomp] = c;

     for(ii = 0; ii < cand[ncomp].size(); ++ii)
     {
         i = cand[ncomp][ii]; 
         if(index(sir[i]) != c)
         {
             if(i > 0 && !set(comp[i-1], index(sir[i-1]))) return false;
             if(i < N-1 && !set(comp[i+1], index(sir[i+1]))) return false;
         }
     }
     
     return true;
}

int main()
{
    int i, j, k, L;
    
 //   freopen("e.in", "r", stdin);
 //   freopen("e.out", "w", stdout);
    
    for(;;) {
        scanf("%d %d", &N, &T);
        if(N == 0 && T == 0) break;
        scanf(" %s", &sir);
        for(i = 0; i < N; ++i)  comp[i] = i;
        for(i = 0; i < T; ++i)
        {
            scanf("%d:", &L);
            for(j = 0; j < L; ++j)
                  scanf("%d", &aux[j]);
            for(j = 0, k = L-1; j < k; ++j, --k)
                  uneste(aux[j], aux[k]);
        }
        
        for(i = 0; i < N; ++i) cand[i].clear();
        for(i = 0; i < N; ++i) cand[rad(i)].push_back(i);
        
        memset(posibil, 0, sizeof(posibil));
        
        for(i = 0; i < N; ++i)
            if(cand[i].size() > 0)
                for(j = 0; j < 4; ++j)
                    if(posColor(i, adn[j])) posibil[i][j] = 1;  
       
        memset(color, -1, sizeof(color));        

        bool okay = true;
        for(i = 0; i < N && okay; ++i)
            if(color[ comp[i] ] == -1)
            {
                okay = false;
                for(j = 0; j < 4 && !okay; ++j)
                {
                    memcpy(prev, color, sizeof(prev));  
                    if(posibil[comp[i]][j] && set(comp[i] , j)) okay = true;
                    else memcpy(color, prev, sizeof(prev));
                }
            }
        if(okay) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
