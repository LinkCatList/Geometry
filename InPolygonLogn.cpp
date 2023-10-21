/*
Дается выпуклый многоугольник и t точек, проверить, сколько из них лежат внутри мноугольника
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
struct Point {
  ld x, y;
  Point() {}
  Point(ld x, ld y) {
    this->x = x;
    this->y = y;
  }
  Point operator-(Point a) { return {x - a.x, y - a.y}; }
};
ll IsPointInside(Point a, Point b,
                 Point c) {  // определение знака поворота ломаной
  ld q = (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x);
  return (q > 0) - (q < 0);  // если отрицательный, то вправо, иначе - влево
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  ll n;
  cin >> n;
  ll t;
  cin >> t;
  vector<Point> polygon(n);
  for (ll i = 0; i < n; i++) {
    cin >> polygon[i].x >> polygon[i].y;
  }
  Point start = polygon[0];
  ll cnt = 0;
  while (t--) {
    Point p;
    cin >> p.x >> p.y;
    if (IsPointInside(start, polygon[1], p) <
            0 ||  // точка лежит вне правой полуплоскости start polygon[1],
                  // значит точно не может быть внутри многоугольника
        IsPointInside(start, polygon.back(), p) >
            0)  // точка лежит вне левой полуплоскости start polygon[n-1],
                // значит точно не может быть внутри многоугольника
      continue;
    ll l = 1, r = n - 1;
    while (r - l > 1) {
      ll m = (l + r) / 2;
      if (IsPointInside(start, polygon[m], p) <
          0) {  // точка p лежит внутри угла
        r = m;
      } else {
        l = m;
      }
    }
    if (IsPointInside(polygon[r], polygon[l], p) <=
        0) {  // точка лежит слева от вектора polygon[l]polygon[r], то есть
              // внутри треугольника и многуогольника
      cnt++;
    }
  }
  cout << cnt << "\n";
  return 0;
}
