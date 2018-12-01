struct decomposer_t
{
  void process(const graph_t &g, int root)
  {
    // process tree `g` with root `root`
    
  }

  vector<int> cnt;
  
  int dfs_cnt(const graph_t &g, int u, int pred = -1)
  {
    cnt[u] = 0;
    for(size_t i = 0; i < g[u].size(); ++i)
    {
      int v = g[u][i].v;
      if(v == pred)
        continue;
      int cur = dfs_cnt(g, v, u);
      cnt[u] += cur;
    }
    cnt[u]++;
    return cnt[u];
  }

  int dfs_root(const graph_t &g, int u, int n, int pred = -1)
  {
    int mx = n - cnt[u];
    for(size_t i = 0; i < g[u].size(); ++i)
    {
      int v = g[u][i].v;
      if(v == pred)
        continue;
      mx = max(mx, cnt[v]);
    }
    if(mx <= n / 2)
      return u;

    for(size_t i = 0; i < g[u].size(); ++i)
    {
      int v = g[u][i].v;
      if(v == pred)
        continue;
      int cur = dfs_root(g, v, n, u);
      if(cur != -1)
        return cur;
    }
    return -1;      
  }
  
  int find_root(const graph_t &g, int root)
  {
    int n = dfs_cnt(g, root);
    int u = dfs_root(g, root, n);
    return u;
  }

  void delete_root(graph_t &g, int root)
  {
    for(size_t i = 0; i < g[root].size(); ++i)
    {
      int v = g[root][i].v;
      for(size_t j = 0; j < g[v].size(); ++j)
        if(g[v][j].v == root)
        {
          swap(g[v][j], g[v].back());
          g[v].pop_back();
          break;
        }
    }
  }
  
  void process_tree(graph_t &g)
  {
    cnt.assign(g.size(), 0);
    process_tree(g, 0);
  }
  
  void process_tree(graph_t &g, int root)
  {
    if(root == -1)
      return;
    root = find_root(g, root);
    process(g, root);
    delete_root(g, root);
    for(size_t i = 0; i < g[root].size(); ++i)
      process_tree(g, g[root][i].v);
  }
};
