#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>

using namespace std;

int mat[256][410], h, w, viz[256][410], holeCnt[80000];
int xx[] = {1, 0, -1, 0};
int yy[] = {0, 1, 0, -1};

int hexToDec(char lit)
{
    if(lit <= '9') return lit - '0';
    return lit - 'a' + 10;
}

void fill(int i, int j, int c, int v)
{
     viz[i][j] = c;
     int k;
     for(k = 0; k < 4; ++k)
     {
         int ii = i + xx[k], jj = j + yy[k];
         if(0 <= ii && ii <= h && 0 <= jj && jj <= w && mat[ii][jj] == v && !viz[ii][jj])
             fill(ii, jj, c, v);
     }
}
string lit(int ng)
{
    if(ng == 0) return "W";
    if(ng == 1) return "A";
    if(ng == 2) return "K";
    if(ng == 3) return "J";
    if(ng == 4) return "S";
    return "D";   
}
int main()
{
#ifndef ONLINE_JUDGE    
    freopen("ancient.in", "r", stdin);
    freopen("ancient.out", "w", stdout);
#endif
    
    int ntest;
    for(ntest = 1; true; ++ntest)
    {
        scanf("%d %d ", &h, &w);
        if(!h && !w) break;
        
        int i, j, k;
        char aux[128];
        memset(mat, 0, sizeof(mat));
        for(i = 0; i < h; ++i)
        {
             scanf("%s", &aux);
             for(j = 0; j < w; ++j)
             {
                 int val = hexToDec(aux[j]);
                 for(k = 0; (1<<k) <= val; ++k) 
                      if(val & (1<<k)) mat[i][j*4 + 3-k] = 1;
             }
        }
        
        w *= 4;
    
        memset(viz, 0, sizeof(viz));
        memset(holeCnt, 0, sizeof(holeCnt));
        int nc = 0, ng = 0;
        for(i = 0; i < h; ++i)
            for(j = 0; j < w; ++j)
                 if(mat[i][j] && !viz[i][j])
                 {
                     ++nc;
//                      printf("am gasit comp %d la %d,%d\n", nc, i, j);
                     fill(i, j, nc, 1);
                 }  
                 
        for(j = 0; j < w; ++j)
        {
           if(!mat[0][j] && !viz[0][j]) fill(0, j, -1, 0);
           if(!mat[h-1][j] && !viz[h-1][j]) fill(h-1, j, -1, 0);
        }
        for(i = 0; i < h; ++i)
        {
           if(!mat[i][0] && !viz[i][0]) fill(i, 0, -1, 0);
           if(!mat[i][w-1] && !viz[i][w-1]) fill(i, w-1, -1, 0);     
        }
        
        for(i = 0; i < h; ++i)
            for(j = 0; j < w; ++j)
                if(!viz[i][j])
                {
                    ++ng;
                    for(k = 0; k < 4; ++k)
                    {
                        int ii = i + xx[k], jj = j + yy[k];
                        if(0 <= ii && ii <= h && 0 <= jj && jj <= w && mat[ii][jj] == 1)
                        {   
                            holeCnt[ viz[ii][jj] ]++;
  //                          printf("hole %d vecina cu %d la %d,%d\n", ng, viz[ii][jj], i,j);
                            break; 
                        }
                    }
                    fill(i, j, nc + ng,0);
                }
        
        string result = "";
        for(i = 1; i <= nc; ++i)
           result += lit( holeCnt[i] );
           
        sort(result.begin(), result.end());   
        printf("Case %d: %s\n", ntest, result.c_str());           
    }
    return 0;
}
