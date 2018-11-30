struct Vec {
  LL x, y;
  explicit Vec(LL x = 0 , LL y = 0) : x(x), y(y) {}
  Vec operator+(const Vec& o) const {
    return Vec(x + o.x, y + o.y); }
  Vec operator-(const Vec& o) const {
    return Vec(x - o.x, y - o.y); }
  Vec operator*(const LL p) const {
    return Vec(x * p, y * p); }
  double len() const { return sqrt(x * x + y * y); }
  LL cross(const Vec& o) const { return x * o.y - y * o.x; }
  LL dot(const Vec& o) const { return x * o.x + y * o.y; }
  static Vec read(istream& cin) {
    LL x, y;
    cin >> x >> y;
    return Vec(x, y);
  }
};
bool cmp(Vec a, Vec b) {
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}
bool cw(Vec a, Vec b, Vec c) {
  return (b - a).cross(c - b) < 0;
}
bool ccw(Vec a, Vec b, Vec c) {
  return (b - a).cross(c - b) > 0;
}
void convex_hull(vector<Vec> & a) {
  if (a.size() == 1) return;
  sort(a.begin(), a.end(), &cmp);
  Vec p1 = a[0], p2 = a.back();
  vector<Vec> up, down;
  up.push_back(p1);
  down.push_back(p1);
  for (size_t i=1; i<a.size(); ++i) {
    if (i==a.size()-1 || cw(p1, a[i], p2)) {
      while (up.size()>=2
          && !cw(up[up.size()-2], up[up.size()-1], a[i]))
        up.pop_back();
      up.push_back (a[i]);
    }
    if (i == a.size()-1 || ccw(p1, a[i], p2)) {
      while (down.size()>=2
          && !ccw(down[down.size()-2],
            down[down.size()-1], a[i]))
        down.pop_back();
      down.push_back(a[i]);
    }
  }
  a.clear();
  for (size_t i=0; i<up.size(); ++i)
    a.push_back(up[i]);
  for (size_t i=down.size()-2; i>0; --i)
    a.push_back(down[i]);
}
