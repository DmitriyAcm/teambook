struct State {
  map<char, int> nxt;
  int link;
  int len;
  bool added;
  int cnt;
};

State st[N];
int lst;
int sz;

void init() {
  lst = 0;
  sz = 1;
  st[0].link = -1;
  st[0].len = 1;
}

void ext(char c) {
  // cerr << "ext : " << c << endl;
  int cur = sz++;
  st[cur].len = st[lst].len + 1;

  int p;
  for (p = lst; p != -1 && !st[p].nxt.count(c); p = st[p].link)
    st[p].nxt[c] = cur;

  if (p == -1) {
    st[cur].link = 0;
  } else {
    int q = st[p].nxt[c];
    if (st[p].len + 1 == st[q].len) {
      st[cur].link = q;
    } else {
      int clone = sz++;
      st[clone] = st[q];
      st[clone].len = st[p].len + 1;
      st[clone].cnt = st[st[clone].link].cnt;
      
      st[q].link = st[cur].link = clone;

      for (; p != -1 && st[p].nxt[c] == q; p = st[p].link)
        st[p].nxt[c] = clone;
    }
  }

  lst = cur;
  st[cur].cnt = st[st[cur].link].cnt;
}
