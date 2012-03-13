#include <cstdio>
#include <cstring>

int main()
{
  int a, m, p, q, r, s, t;

  freopen("addmul.in", "r", stdin);
  freopen("addmul.out", "w", stdout);

  for(t = 1; true; ++t)
  {
    scanf("%d %d %d %d %d %d", &a, &m, &p, &q, &r, &s);

    if(!a && !m && !p && !q && !r && !s) break;

    printf("Case %d:", t);
    if(r <= p && q <= s)
    {
      printf(" empty\n");
      continue;
    }

    if(m == 1)
    {
      int nop = r>p ? (r-p-1)/a+1 : 0;
      if(p+nop*a >= r && q+nop*a <= s)
        printf(" %dA\n", nop);
      else printf(" impossible\n");
      continue;
    }

    long long mlag, mg;
    const long long max = 1e9 + 1;

    int h[100], g, cnt, i, h2[100], nra2 = 0, nrm = -1;
    memset(h2, 0, sizeof(h2));
    for(g = 0, mlag = 1; g <= 29; ++g, mlag *= m)
    {
      if(mlag > max || q*mlag > max || q*mlag > s) break;

      int u = (r <= p * mlag) ? 0 : ((r - p * mlag - 1)/a + 1);
      int v = (s == q * mlag) ? 0 : ((s - q * mlag - 1)/a + 1), aux = 0, j, nra = 0;
     
      if( u > v || v < 0 || q*mlag + u*a > s) continue;

      memset(h, 0, sizeof(h));
      for(i = 0, mg = mlag; i <= g && aux < u; ++i, mg /= m)
      {
        h[i] = v / mg;
        aux += h[i] * mg;
        v -= h[i] * mg;
        if(aux > u)  h[i] -= (aux - u)/mg, aux -= (aux-u)/mg * mg;
        if(h[i]) nra += h[i];
      }

      if(nrm == -1 || nra + g < nra2 + nrm)
      {
        nrm = g;
        memcpy(h2, h, sizeof(h));
        nra2 = nra;
      }
      else if(nra + g > nra2 + nrm) ;
      else for(i = 0; i <= g; ++i)
              if(h[i] > h2[i])
              { 
                nrm = g;
                memcpy(h2, h, sizeof(h));
                nra2 = nra;
                break;
              }
              else if(h[i] < h2[i]) break;
    }

    if(nrm == -1) printf(" impossible\n");
    else 
    {
      for(i = 0; i <= nrm; ++i)
      {
        if(h2[i]) printf(" %dA", h2[i]);
        if(i < nrm)
        {
          for(cnt = 1; i < nrm-1 && h2[i+1] == 0; ++i) ++cnt;
          printf(" %dM", cnt);
        }
      } 
      printf("\n");
    }
  }
  return 0;
}
