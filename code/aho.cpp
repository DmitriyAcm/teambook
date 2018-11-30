struct Matcher {
  static const int LETTERS_COUNT = 'z' - 'a' + 1;
  struct Next {
    int nxt[LETTERS_COUNT];
    Next() { fill(nxt, nxt + LETTERS_COUNT, -1); }
    int& operator[](char c) { return nxt[c - 'a']; }
  };

  vector<Next> next;
  vector<int> link;
  vector<char> p_char;
  vector<int> p;
  vector<int> id;

  void build(const set<string>& strings) {
    int total_size = 0;
    for (const auto& s : strings)
      total_size += s.size();
    next.reserve(total_size);
    link.reserve(total_size);
    p_char.reserve(total_size);
    p.reserve(total_size);

    push();

    int _id = 0;
    for (const auto& s : strings) {
      add(s, _id);
      ++_id;
    }
  }

  void push() {
    next.push_back(Next());
    link.push_back(-1);
    p_char.push_back('#');
    p.push_back(-1);
    id.push_back(-1);
  }

  void add(const string& s, int _id) {
    int state = 0;

    for (char c : s) {
      int next_state = next[state][c];
      if (next_state == -1) {
        push();
        p_char.back() = c;
        p.back() = state;
        next_state = p.size() - 1;
        next[state][c] = next_state;
      }

      state = next_state;
    }

    id[state] = _id;
  }

  int get_next(int state, char c) {
    int x = _get_next(state, c);
    // cerr << "get next " << state << " " << c << " = " << x << endl;
    return x;
  }

  int _get_next(int state, char c) {
    if (next[state][c] == -1 && state == 0)
      return 0;
    if (next[state][c] == -1)
      next[state][c] = get_next(get_link(state), c);
    return next[state][c];
  }

  int get_link(int state) { int x = _get_link(state);
    // cerr << "get link " << state << " = " << x << endl;
    return x;
  }

  int _get_link(int state) {
    if (state == 0)
      return 0;
    if (p[state] == 0)
      return 0;

    int& l = link[state];
    if (l == -1)
      l = get_next(get_link(p[state]), p_char[state]);
    return l;
  }

  int get_id(int state) { return id[state]; }
};
