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

// CONVEX HULL: last point == first point
vector<Vec> convex_hull(vector<Vec> a) {
  int n = a.size(), k = 0;
  vector<Vec> p(n * 2);
  sort(a.begin(), a.end());

  for(int i = 0; i < n; p[k++] = a[i++])
    while(k > 1 && (p[k - 1] - p[k - 2])
        % (p[k - 1] - a[i]) >= 0) --k;
  for(int i = n - 2, w = k; i >= 0; p[k++] = a[i--])
    while(k > w && (p[k - 1] - p[k - 2])
        % (p[k - 1] - a[i]) >= 0) --k;
  p.resize(k);
  return p;
}
