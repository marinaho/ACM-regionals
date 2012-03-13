#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

#define x first
#define y second

using namespace std;

vector<pair<int, int> > pinit, pfin, p, prot;

inline int norma(pair<int, int> p)
{
  return p.x * p.x + p.y * p.y;
};

pair<int, int> rotate(pair<int, int> center, pair<int, int> point)
{
  double cos = center.x / sqrt(norma(center));
  double sin = center.y / sqrt(norma(center));
  double xx = point.x * cos - point.y * sin;
  double yy = point.x * sin + point.y * cos;

  return make_pair(floor(xx + 0.5), floor(yy + 0.5));
}

bool read()
{
    bool flag = true;
    int a, b, i;
    pinit.clear();
    for(i = 0; i < 3; ++i)      
    {
      scanf("%d %d", &a, &b);
      pinit.push_back(make_pair(a, b));
      if(a || b) flag = false;
    }
    if(flag) return false;

    pfin.clear();
    for(i = 0; i < 3; ++i)
    {
      scanf("%d %d", &a, &b);
      pfin.push_back(make_pair(a, b));
    }
    return true;
}

const double EPS = 1e-9;
inline bool isInteger(double a)
{
  return abs(a - round(a)) < EPS;
}

int solveEq(double a1, double b1, double c1, double a2, double b2, double c2, double &xx, double &yy)
{
  double det = a1*b2 - a2*b1;
  if(det == 0) 
     if(b2*c1 - b1*c2 != 0) return -4; //no solutions
     else return 0; //infinity solutions
  xx = (b2*c1 - b1*c2)/det;
  yy = (a1*c2 - a2*c1)/det;
  return 1; //unique solution
}

bool verify(int scale, int trans, int a)
{
  int i;
  for(i = 0; i < 3; ++i)
    if(a && prot[i].x * scale + trans != pfin[i].x) return false;
    else if(!a && prot[i].y * scale + trans != pfin[i].y) return false;
  return true;
}
int main()
{
  freopen("affine.in", "r", stdin);
  freopen("affine.out", "w", stdout);

  int t, a, b, i;

  for(t = 1; true; ++t)
  {

    if(!read()) break;

    printf("Case %d:", t);
    int first3[] = {0, 1, 2}, xx, yy, i;
    bool haveSol = false, uniqueSol = true;
    double tx, ty, sx, sy, xrot, yrot;
    do {
      p.clear();
      for(i = 0; i < 3; ++i)
        p.push_back( pinit[first3[i]] );

      for(xx = -10; xx <= 10; ++xx)
        for(yy = -10; yy <= 10; yy += (abs(xx) == 10) ? 1 : 20)
        {
          prot.clear();
          for(i = 0; i < 3; ++i)
            prot.push_back(rotate(make_pair(xx, yy), p[i]));

          double scalex = 1, transx = 1, scaley = 1, transy = 1;
          int solved = solveEq(prot[0].x, 1, pfin[0].x, prot[1].x, 1, pfin[1].x, scalex, transx) +
                       solveEq(prot[1].x, 1, pfin[1].x, prot[2].x, 1, pfin[2].x, scalex, transx) +
                       solveEq(prot[2].x, 1, pfin[2].x, prot[0].x, 1, pfin[0].x, scalex, transx);
          if(solved < 0 || (solved > 0 && (!isInteger(scalex) || abs(scalex) < EPS || !isInteger(transx) || !verify(scalex, transx, 1)))) continue;
    
          int solved2 = solveEq(prot[0].y, 1, pfin[0].y, prot[1].y, 1, pfin[1].y, scaley, transy) +
                        solveEq(prot[1].y, 1, pfin[1].y, prot[2].y, 1, pfin[2].y, scaley, transy) +
                        solveEq(prot[2].y, 1, pfin[2].y, prot[0].y, 1, pfin[0].y, scaley, transy);

          if(solved2 < 0 || (solved2 > 0 && (!isInteger(scaley) || abs(scaley) < EPS || !isInteger(transy) || !verify(scaley, transy, 0)))) continue;

          if(!solved || !solved2) haveSol = true, uniqueSol = false;
          else if(!haveSol) haveSol = true, xrot = xx, yrot = yy, tx = transx, ty = transy, sx = scalex, sy = scaley;
          else if(xx != -xrot || yy != -yrot || scalex != -sx || scaley != -sy || transx != tx || transy != ty)
            uniqueSol = false;
    
      //  printf("Am rotit la (%d,%d), scaleaza cu %lf,%lf si translateaza cu %lf,%lf\n", xx, yy, scalex, scaley, transx, transy);
        }
       
    }while(next_permutation(first3, first3 + 3));

    if(!haveSol) printf(" no solution\n");
    else if(!uniqueSol) printf(" inconsistent solutions\n");
    else printf(" equivalent solutions\n");
  }
  return 0;
}
