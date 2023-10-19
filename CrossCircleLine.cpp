#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
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
};
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout<<fixed<<setprecision(16);
  Circle C;
  cin>>C.P1.x>>C.P1.y;
  cin>>C.R;
  Line L;
  cin>>L.A>>L.B>>L.C;
  
  vector<Point>v = C.CrossWithLine(L);
  cout<<(ll)v.size()<<"\n";
  for(auto i:v){
    cout<<i.x<<" "<<i.y<<"\n";
  }
  return 0;
} 
