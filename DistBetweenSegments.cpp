#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
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
  ld dist(Point b){
    return sqrtl((x-b.x)*(x-b.x)+(y-b.y)*(y-b.y));
  }
  void NewSize(ld d){ // нормирование вектора на нужную длину
    ld sz = len();
    this->x = this->x/sz*d;
    this->y = this->y/sz*d;
  }
  bool IsEqual(Point b){
    return this->x == b.x && this->y == b.y;
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
  bool AreSegmentsCrossed(Segment B){ // если точки одного отрезка лежат по разные стороны относительно другого отрезка, либо какие-то точки совпадают,
                                      // то отрезки пересекаются
    return !L.OnSameSide(B.P1, B.P2) && !B.L.OnSameSide(P1, P2) || dist(B.P1) == 0 || dist(B.P2) == 0 || B.dist(P1) == 0 || B.dist(P2) == 0;
  }
};
ld DistBetweenSegments(Segment S1, Segment S2){
  if(S1.P1.IsEqual(S1.P2) && S2.P1.IsEqual(S2.P2)){
    return S1.P1.dist(S2.P1);
  }
  if(S1.P1.IsEqual(S1.P2)){
    return S2.dist(S1.P1);
  }
  if(S2.P1.IsEqual(S2.P2)){
    return S1.dist(S2.P1);
  }
  if(S1.AreSegmentsCrossed(S2)){
    return 0;
  }

  ld a = S1.dist(S2.P1);
  ld b = S1.dist(S2.P2);
  ld c = S2.dist(S1.P1);
  ld d = S2.dist(S1.P2);
  return min({a, b, c, d});
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout<<fixed<<setprecision(16);
  Segment S1, S2;
  cin>>S1.P1.x>>S1.P1.y>>S1.P2.x>>S1.P2.y;
  cin>>S2.P1.x>>S2.P1.y>>S2.P2.x>>S2.P2.y;

  cout<<DistBetweenSegments(S1, S2)<<"\n";
  return 0;
} 
