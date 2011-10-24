//SouthWestern ACM ICPC 2010
//Comparing answers

#include <cstdio>
#include <stdlib.h>

#define NMAX  1010
#define MAX 8096
#define cifra(x) (('0' <= (x)) && ((x) <= '9'))
#define TRYCNT 10

int n;
int A[NMAX][NMAX], B[NMAX][NMAX];
int x[NMAX], aux[NMAX], aux2[NMAX];
char input[MAX];

void readAndParse()
{
    int i, j, k;
    
    scanf("%d\n", &n);
    if(n == 0) return;
    for(i = 0; i < n; ++i)
    {        
        fgets(input, MAX, stdin);
        for(j = k = 0; input[j] != NULL; ++j)
        {
            for(;input[j] != NULL && !(cifra(input[j])); ++j) ;
            if(input[j] == NULL) break;
            for(A[i][k] = 0; input[j] != NULL && cifra(input[j]); ++j) A[i][k] = A[i][k] * 10 + input[j] - '0';
            if(input[j] == NULL) break;
            ++k;
        }
    }
    for(i = 0; i < n; ++i)
    {     
        fgets(input, MAX, stdin);
        for(j = k = 0; input[j] != NULL; ++j)
        {
            for(;input[j] != NULL && !(cifra(input[j])); ++j) ;
            if(input[j] == NULL) break;
            for(B[i][k] = 0; input[j] != NULL && cifra(input[j]); ++j) B[i][k] = B[i][k] * 10 + input[j] - '0';
            if(input[j] == NULL) break;
            ++k;
        }
    }    
}
void afis()
{
     int i, j;
     printf("n=%d\n",n);
     for(i = 0; i < n; ++i)
     {
        for(j = 0; j < n; ++j)
            printf("%d ", B[i][j]);
        printf("\n");
     }
}
void generateX()
{
     int i;
     for(i = 0; i < n; ++i)
           x[i] = rand();
}
int solveForX()
{
    int i, j;
    //aux = A * x
    for(i = 0; i < n; ++i)
    {
        aux[i] = 0;
        for(j = 0; j < n; ++j)
          aux[i] += A[i][j] * x[j];    
    }
    // aux2 = A * (A * x)
    for(i = 0; i < n; ++i)
    {
        aux2[i] = 0;
        for(j = 0; j < n; ++j)
          aux2[i] += A[i][j] * aux[j];    
    }
    // compare aux2 with B * x
    for(i = 0; i < n; ++i)
    {
        int temp = 0;
        for(j = 0; j < n; ++j)
            temp += B[i][j] * x[j];
        if(temp != aux2[i]) return 0;
    }
    return 1;
}
int main()
{
    int i;
    
//    freopen("comp.in", "r", stdin);
//    freopen("comp.out", "w", stdout);
                        
    for(;;)
    {
      readAndParse();
      if(n == 0) break;
      for(i = 0; i < TRYCNT; ++i)
      {
           generateX();
           if(solveForX() == 0)
           {
               printf("NO\n");
               break;
           };
      }
      if(i == TRYCNT) printf("YES\n");
    }

    return 0;
}
