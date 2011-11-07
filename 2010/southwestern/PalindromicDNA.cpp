//Palindromic DNA
//SouthWestern European Reagional ACM 2010
//2-SAT folosind alg lui Tarjan
//Una din solutiile oficiale, DAR -> TLE pe uva

#include <cstdio>
#include <vector>

#define NMAX 100010

using namespace std;

vector<int> graf[4*NMAX];
int viz[4*NMAX], niv[4*NMAX], nivmin[4*NMAX], comp[4*NMAX], stiva[4 * NMAX];

#define graf (graf + 2*N + 1)
#define viz (viz + 2*N + 1)
#define niv (niv + 2*N + 1)
#define nivmin (nivmin + 2*N + 1)
#define comp (comp + 2*N + 1)

int N, T;
char sir[NMAX];

int aux[NMAX], fail, ultStiva, ncomp;

char adn[] = "AGTC";
char next(char a)
{
    int i;
    for(i = 0; adn[i] != '\0'; ++i)
           if(adn[i] == a) return adn[(i+1)%4];
    return adn[0];
}

void comptare(int i)
{
     int j;
     viz[i] = 1; stiva[++ultStiva] = i;
     for(j = 0; j < graf[i].size(); ++j)
           if(! viz[ graf[i][j] ])
           {
                niv[graf[i][j]] = nivmin[graf[i][j]] = niv[i] + 1;
                comptare(graf[i][j]);
                if(nivmin[ graf[i][j] ] < nivmin[i]) nivmin[i] = nivmin[ graf[i][j] ];
           }
           else if(!comp[ graf[i][j] ] && niv[graf[i][j]] < nivmin[i]) nivmin[i] = niv[ graf[i][j] ];
     if(niv[i] == nivmin[i])
     {
         comp[i] = ++ncomp;
         for(j = ultStiva; j >= 0 && stiva[j] != i; --j)
             comp[ stiva[j]] = ncomp;
         ultStiva = j-1;
     }
}
void add_sau(int i, int j)
{
     graf[-i].push_back(j);
     graf[-j].push_back(i);
}
void add_egal(int i, int j)
{
     add_sau(i, -j);
     add_sau(-i, j);    
}
void add_distinct(int i, int j)
{
     add_sau(i, j); add_sau(-i, -j);
}
void set1(int i)
{
     graf[-i].push_back(i);
}
void add(int i, int j)
{
     graf[i].push_back(j);
}
void swap(int& i, int& j)
{
     i += j;
     j = i - j;
     i -= j;
}
int main()
{
    int i, j, l, v1, v2;
    
  //  freopen("e.in", "r", stdin);
  //  freopen("e.out", "w", stdout);

    for(;;) {
        scanf("%d %d\n", &N, &T);
        if(N == 0 && T == 0) break;
        scanf("%s\n", &sir[1]);
        for(i = -2*N; i <= 2*N; ++i) graf[i].clear();
        for(i = 1; i < N; ++i) add_sau(-i, -(i+1));
        for(i = 0; i < T; ++i)
        {
              scanf("%d:", &l); 
              for(j = 0; j < l; ++j) scanf("%d ", &aux[j]);
              for(j = 0; j <= l/2-1; ++j)
              {
                  v1 = aux[j]+1; v2 = aux[l-j-1]+1;
                  if(next(sir[v2]) == sir[v1] || next(next(sir[v2])) == sir[v1]) swap(v1, v2);
                  if(sir[v1] == sir[v2])
                      add_egal(v1, v2),
                      add_egal(v1+N, v2+N);       
                  else if(sir[v2] == next(sir[v1])) 
                      add_distinct(v1, v2),
                      add_sau(v1, -(v2+N)),
                      add_sau(v2, v1+N);
                  else if(sir[v2] == next(next(sir[v1])))
                      set1(v1), set1(v2),
                      add_distinct(v1+N, v2+N);
                  else printf("Error %c %c\n", sir[v1], sir[v2]);
              }
        }
        ncomp = 0; ultStiva = -1;
        for(i = -2*N; i <= 2*N; ++i) viz[i] = comp[i] = 0;
        for(i = -2*N; i <= 2*N; ++i)
                if(i == 0) continue;
                else if(!viz[i])
                {
                     niv[i] = nivmin[i] = 1;
                     comptare(i);
                }
        bool okay = true;
        for(i = 1; i <= 2*N && okay; ++i)
            if(comp[i] == comp[-i]) okay = false;
            
        if(okay) printf("YES\n");
        else printf("NO\n");
    }    
    return 0;
}
