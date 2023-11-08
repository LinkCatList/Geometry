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
  bool AreParallel(Line b){
    return (A*b.B-B*b.A) == 0;
  }
  bool OnSameSide(Point a, Point b){ // лежат ли точки по одну сторону от прямой
    return (A*a.x+B*a.y+C)*(A*b.x+B*b.y+C)>=0;
  }
};
struct Segment{
  Point P1, P2;
  Line L, LP1, LP2;

  Segment(){}

  Segment(Point P1, Point P2){
    this->P1 = P1;
    this->P2 = P2;

    L = Line(P1, P2); // прямая, на которой лежит отрезок
    LP1 = Line(P1, L); // прямая, перпендикулярная прямой, на которой лежит отрезок и содержащая P1
    LP2 = Line(P2, L); // прямая, перпендикулярная прямой, на которой лежит отрезок и содержащая P2
  }

  ld dist(Point a){
    if(LP2.OnSameSide(P1, a) && LP1.OnSameSide(P2, a)){ // если отрезок лежит на прямой, то расстояние это перпендикуляр
      return L.dist(a);
    }
    return min(a.dist(P1), a.dist(P2)); // иначе минимальное расстояние от точки до концов отрезка
  }

};
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout<<fixed<<setprecision(16);
  Segment Seg;
  cin>>Seg.P1.x>>Seg.P2.y;
  cin>>Seg.P2.x>>Seg.P2.y;

  Point P;
  cin>>P.x>>P.y;

  cout<<Seg.dist(P)<<"\n";
  return 0;
} 
