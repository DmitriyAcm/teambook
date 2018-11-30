struct Complex {
  long double re, im;
  explicit Complex(long double re = 0,
      long double im = 0) : re(re), im(im) {}
  Complex operator+(const Complex& o) const {
    return Complex(re + o.re, im + o.im); }
  Complex operator-(const Complex& o) const {
    return Complex(re - o.re, im - o.im); }
  Complex operator*(const Complex& o) const {
    return Complex(re * o.re - im * o.im, re * o.im + im * o.re); }
};

const int MAX_SHIFT = 22;
const int MAX_N     = 1 << MAX_SHIFT;

const double Pi = acos(-1);

Complex roots[MAX_N / 2];
int bit_reverse[MAX_N];

void prep() {
  bit_reverse[0] = 0;
  for (int i = 1; i < MAX_N; ++i)
    bit_reverse[i] = (bit_reverse[i >> 1]
        | ((i & 1) << MAX_SHIFT)) >> 1;
    
  for (int i = 0; i + i < MAX_N; ++i) {
    double angle = 2 * i * Pi / MAX_N;
    roots[i] = Complex(cos(angle), sin(angle));
  }
}

Complex arr[MAX_N];
void fft(int k) {
  assert(k <= MAX_SHIFT);
  
  const int n = 1 << k;
  for (int i = 0; i < n; ++i) {
    int rv = bit_reverse[i] >> (MAX_SHIFT - k);
    if (rv < i) swap(arr[i], arr[rv]);
  }
  
  for (int bs = 2; bs <= n; bs *= 2) {
    const int hbs = bs / 2;
    const int factor = (MAX_N / 2) / hbs;
    for (int i = 0; i < n; i += bs) {
      for (int j = 0; j < hbs; ++j) {
        auto a = arr[i + j];
        auto b = arr[i + j + hbs] * roots[factor * j];
        arr[i + j] = a + b;
        arr[i + j + hbs] = a - b;
      }
    }
  }
}

const int Base = 100;

void square(vector<int>& number) {
  int sz = number.size() * 2;
  int k = 1;
  {
    int rsz = 2;
    while (rsz < sz) {
      rsz *= 2;
      ++k;
    }
    
    sz = rsz;
  }
  
  assert(sz <= MAX_N);
  
  for (int i = 0; i < sz; ++i)
    arr[i] = Complex(i < number.size() ? number[i] : 0);
  
  fft(k);
  for (int i = 0; i < sz; ++i)
    arr[i] = arr[i] * arr[i];
  fft(k);
  reverse(arr + 1, arr + sz);
  
  number.resize(sz);
  int cr = 0;
  for (int i = 0; i < sz; ++i) {
    number[i] = cr + int(arr[i].re / sz + 0.5);
    cr = number[i] / Base;
    number[i] %= Base;
  }
  
  while (number.back() == 0) number.pop_back();
}
