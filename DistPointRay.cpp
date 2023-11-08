#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const ld pi = acos(-1);

struct Point{
  ld x, y;
  Point(){}
  Point(ld x, ld y){
    this->x = x;
    this->y = y;
  }
  Point operator -(Point b){
    return {x-b.x, y-b.y};
  }
  Point operator +(Point b){
    return {x+b.x, y+b.y};
  }
  ld len(){
    return sqrtl(x*x+y*y);
  }
  ld dist(Point b){
    return sqrtl((x-b.x)*(x-b.x)+(y-b.y)*(y-b.y));
  }
  void NewSize(ld d){ // нормирование вектора на нужную длину
    ld sz = len();
    this->x = this->x/sz*d;
    this->y = this->y/sz*d;
  }
};

struct Ray{
  Point P, P1;
  Line L, LP;

  Ray(){}
  Ray(Point P, Point P1){
    this->P = P;
    this->P1 = P1;

    this->L = Line(P, P1); // прямая, проходящая через точку P и P1
    this->LP = Line(P, L); // прямая, перпендикулярная прямой выше и проходяшая через точку P
  }

  ld dist(Point P2){
    if(LP.OnSameSide(P2, P1)){ // если точка лежит над лучем, то расстояние это расстояние от точки до прямой
      return L.dist(P2);
    }
    return P.dist(P2); // иначе это расстояние от начала луча до точки
  }
};
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout<<fixed<<setprecision(16);
  Ray R;
  Point p;
  cin>>p.x>>p.y;
  cin>>R.P.x>>R.P.y>>R.P1.x>>R.P1.y;

  cout<<R.dist(p);
  return 0;
} 
