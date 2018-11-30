// g++ -std=c++11 main.cpp -o main -D"_DEBUG_TEMICH_"

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

using LL = long long;
using pii = pair<int, int>;

#define X first
#define Y second

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v);

template<typename U, typename V>
ostream& operator<<(ostream& out, const map<U, V>& v);

template<typename U, typename V>
ostream& operator<<(ostream& out, const pair<U, V>& v);

template<typename U, typename V>
ostream& operator<<(ostream& out, const pair<U, V>& v) {
  return out << "(" << v.first << ", " << v.second << ")";
}

template<typename U, typename V>
ostream& operator<<(ostream& out, const map<U, V>& v) {
  out << "{";
  bool f = false;
  for (const auto& p : v) {
    out << (!f ? "" : ", ") << p;
    f = true;
  }
  return out << "}";
}

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v) {
  out << "{";
  for (int i = 0; i < int(v.size()); ++i)
    out << (i == 0 ? "" : ", ") << v[i];
  return out << "}";
}

void cerr_printer(bool start) {}
template<typename T, typename ... Args>
void cerr_printer(bool start, const T& x, const Args& ... args) {
  if (!start) cerr << ", ";
  cerr << x;
  cerr_printer(false, args...);
}

template<typename ... Args>
void dbg(const char * name, int line, const Args& ... args) {
  cerr << "[" << line << "] (" << name << ") = (";
  cerr_printer(true, args...);
  cerr << ")" << endl;
}

#define DBG(...) { dbg(#__VA_ARGS__, __LINE__, __VA_ARGS__); }

struct Solver {
  void solve(istream& cin, ostream& cout) {
    int a, b;
    cin >> a >> b;
    cout << a + b << endl;
  }
};

struct Brute {
  void solve(istream& cin, ostream& cout) {
    int a, b;
    cin >> a >> b;
    while (b--) ++a;
    cout << a << endl;
  }
};

template <typename Solution>
struct SolutionStr {
  string solve(string input) {
    istringstream is(input);
    ostringstream os;
    Solution().solve(is, os);
    return os.str();
  }
};

string gen_input(int it) {
  (void)it;
  return "10 20";
}

void stress() {
  for (int it = 0; it < 1000; ++it) {
    auto input = gen_input(it);
    auto brute_out = SolutionStr<Solver>().solve(input);
    auto sol_out = SolutionStr<Brute>().solve(input);
    if (sol_out != brute_out) {
      cerr << "WA #" << it << endl;
      cerr << "input: " << endl;
      cerr << input << endl;
      cerr << "expected: " << brute_out << endl;
      cerr << "got: " << sol_out << endl;
      exit(1);
    }
  }

  cerr << "OK" << endl;
}

int main() {
  #ifdef _DEBUG_TEMICH_
  stress();
  #endif
  Solver().solve(cin, cout);
}
