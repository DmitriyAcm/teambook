class SegmTreeSum {
  vector<int> tree;
  int n;

  int get(int v, int l, int r, int L, int R) const {
    if (L > R) return 0;
    if (l == L && r == R) return tree[v];

    int mid = (l + r) / 2;

    int a = get(2 * v + 1, l, mid, L, min(R, mid));
    int b = get(2 * v + 2, mid + 1, r, max(L, mid + 1), R);

    return a + b;
  }

  void set(int v, int l, int r, int pos, int val) {
    if (l == r) {
      tree[pos] = val;
      return;
    }

    int mid = (l + r) / 2;

    if (pos <= mid) set(2 * v + 1, l, mid, pos, val);
    else set(2 * v + 2, mid + 1, r, pos, val);

    tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
  }

public:
  void init(int n_) {
    n = n_;
    tree.assign(4 * n, 0);
  }

  int get(int l, int r) const {
    return get(0, 0, n - 1, l, r);
  }

  void set(int pos, int val) {
    set(0, 0, n - 1, pos, val);
  }
};

class SegmTreeMax {
  vector<Pair> tree;
  vector<int> psh;
  int n;

  void build(int v, int l, int r, const vector<int>& dp) {
    if (l == r) {
      tree[v] = Pair(dp[l], l);
      return;
    }

    int mid = (l + r) / 2;

    build(2 * v + 1, l, mid, dp);
    build(2 * v + 2, mid + 1, r, dp);

    tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
  }

  void push(int v, int l, int r) {
    if (l != r) {
      psh[2 * v + 1] += psh[v];
      psh[2 * v + 2] += psh[v];
    }
    tree[v].X += psh[v];
    psh[v] = 0;
  }

  Pair getMax(int v, int l, int r, int L, int R) {
    push(v, l, r);
    if (L > R) return Pair(-INF, -INF);

    if (l == L && r == R)
      return tree[v];

    int mid = (l + r) / 2;

    Pair a = getMax(2 * v + 1, l, mid, L, min(R, mid));
    Pair b = getMax(2 * v + 2, mid + 1, r, max(L, mid + 1), R);

    return max(a, b);
  }

  void add(int v, int l, int r, int L, int R, int val) {
    push(v, l, r);

    if (L > R) return;
    if (l == L && r == R) {
      psh[v] += val;
      push(v, l, r);
      return;
    }

    int mid = (l + r) / 2;

    add(2 * v + 1, l, mid, L, min(R, mid), val);
    add(2 * v + 2, mid + 1, r, max(L, mid + 1), R, val);

    tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
  }

public:
  void init(const vector<int>& dp) {
    n = dp.size();
    tree.resize(4 * n);
    psh.assign(4 * n, 0);

    build(0, 0, n - 1, dp);
  }

  Pair getMax(int l, int r) {
    return getMax(0, 0, n - 1, l, r);
  }

  void add(int l, int r, int val) {
    add(0, 0, n - 1, l, r, val);
  }
};
