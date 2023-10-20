#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const ll inf = 2e9;8);
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
  void NewSize(ld d){ // нормирование вектора на нужную длину
    ld sz = len();
    this->x = this->x/sz*d;
    this->y = this->y/sz*d;
  }
};
struct Line{
  ld A = 0, B = 0, C = 0;
  Line(){}
  Line(Point a, Point b){ // прямая по двум точкам
    this->A = b.y-a.y;
    this->B = a.x-b.x;
    this->C = b.x*a.y-a.x*b.y;
  }
  Line(ld a, ld b, ld c){ // прямая по известным коэффициентам
    this->A = a;
    this->B = b;
    this->C = c;
  }
  Line(Point a, Line other){ // прямая перпендикулярная данной, проходящая через точку
    Point b = {a.x+other.A, a.y+other.B};
    Line Perpendicular(a, b);

    this->A = Perpendicular.A;
    this->B = Perpendicular.B;
    this->C = Perpendicular.C;
  }
  ld dist(Point p){ // расстояние от точки до прямой
    return abs(this->A*p.x+this->B*p.y+this->C)/sqrtl(this->A*this->A+this->B*this->B);
  }
  Point CrossLines(Line L){ // решение системы уравнений методом Крамера
    ld x = this->A*L.B-this->B*L.A;
    ld y = L.C*this->B-this->C*L.B;
    ld z = this->C*L.A-L.C*this->A;

    return {y/x, z/x};
  }
};
struct Circle{
  Point P1;
  ld R;
  Circle(){}
  Circle(Point p1, ld r){
    this->P1 = p1;
    this->R = r;
  }
  vector<Point>CrossWithLine(Line L){
    ld dist = L.dist(P1);
    if(dist>R){
      return {};
    }
    else if(dist == R){
      Line L2(P1, L);
      Point p = L.CrossLines(L2);
      return {p};
    }
    else{
      Line L2(P1, L);
      Point P2 = L.CrossLines(L2);
      Point P3(-L.B, L.A); // направляющий вектор прямой L
      P3.NewSize(sqrtl(R*R-dist*dist)); // нормируем вектор на расстояние до точки пересечения
      return {Point(P2.x+P3.x, P2.y+P3.y), Point(P2.x-P3.x, P2.y-P3.y)};
    }
  }
  vector<Point>CrossWithCircle(Circle C){
    if(P1.x == C.P1.x && P1.y == C.P1.y){ // если центры совпадают
      if(C.R != R){ // если разные радиусы, то пересечений нет
        return {};
      }
      else{
        return {Point(inf, inf), Point(inf, inf), Point(inf, inf)}; // если одинаковые то бесконечно много пересечений
      }
    }
    C.P1 = C.P1-P1;
    Line L(C.P1.x*(-2), C.P1.y*(-2), C.P1.x*C.P1.x+C.P1.y*C.P1.y+R*R-C.R*C.R);
    Circle C2({0, 0}, R);
    vector<Point>ans = C2.CrossWithLine(L);
    for(auto &i:ans){
      i = i+P1;
    }
    return ans;
  }
};
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout<<fixed<<setprecision(16);
  Circle C1, C2;
  cin>>C1.P1.x>>C1.P1.y>>C1.R;
  cin>>C2.P1.x>>C2.P1.y>>C2.R;

  vector<Point>ans = C1.CrossWithCircle(C2);
  cout<<ans.size()<<"\n";
  if(ans.size() == 3)return 0;
  for(auto i:ans){
    cout<<i.x<<" "<<i.y<<"\n";
  }
  return 0;
} 
