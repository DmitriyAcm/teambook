struct Edge {
  int u, v, flow, cap;
  Edge() : u(0), v(0), flow(0), cap(0) {}
  Edge(int u, int v, int c) : u(u), v(v), flow(0), cap(c) {}
};

const int N = 666;
const int T = 1111;

const int MAXN = N + 2 * T + 100;


vector<int> g[500000];
vector<Edge> edges;

int flow, s, t;
int start[MAXN], used[MAXN], dist[MAXN];

bool bfs() {
  memset(start, 0, sizeof(start));
  memset(dist, -1, sizeof(dist));
  dist[s] = 0;

  queue<int> q;
  q.push(s);

  while (q.size()) {
    int u = q.front();
    q.pop();

    for (int id : g[u]) {
      Edge &e = edges[id];
      int v = e.v;

      if (dist[v] == -1 && e.flow < e.cap) {
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
  }
  return dist[t] != -1;  
}

int dfs(int u, int fl = -1) {
  if (fl == -1) memset(used, false, sizeof(used));
  used[u] = true;

  if (u == t) return fl;

  for (int &i = start[u]; i < g[u].size(); ++i) {
    int id = g[u][i];
    Edge &e = edges[id];
    int v = e.v;
    if (!used[v] && dist[v] == dist[u] + 1 && e.flow < e.cap) {
      int can = e.cap - e.flow;
      int df = dfs(v, fl == -1 ? can : min(fl, can));
      if (df > 0) {
        edges[id ^ 0].flow += df;
        edges[id ^ 1].flow -= df;
        return df;
      }
    }
  }
  return 0;
}

void add_edge(int u, int v, int c) {
  //cout << "add (" << u << " " << v << " " << c << ") " << endl;
  g[u].push_back(edges.size());
  edges.emplace_back(u, v, c);
  g[v].push_back(edges.size());
  edges.emplace_back(v, u, 0);
}

int calc(int ss, int tt) {
  //cout << "calc (" << ss << ", " << tt << ")" << endl;
  flow = 0, s = ss, t = tt;
  while (bfs()) {
    while (int add = dfs(ss)) {
      flow += add;
    }
  }
  return flow;
}
