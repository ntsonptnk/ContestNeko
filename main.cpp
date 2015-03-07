#define SUBMIT

#ifdef SUBMIT
#define LOGLEVEL 0
#define NDEBUG
#else
#define LOGLEVEL 1
#endif

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <cstdlib>
#include <array>
#include <type_traits>
#include <queue>
#include <stack>
#include <functional>

using namespace std;

#define LOG(l, x) if (l <= LOGLEVEL) cout << x << endl

#define int64 long long
#define repeat(x) for (auto repeat_var = 0; repeat_var < x; ++repeat_var)

#define for_inc(i, x) for (auto i = 0; i < x; ++i)
#define for_dec(i, x) for (auto i = x - 1; i >= 0; --i)
#define for_inc_range(i, x, y) for (auto i = x; i <= y; ++i)
#define for_dec_range(i, x, y) for (auto i = x; i >= y; --i)

#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF ((int)2E9L)
#define INT64_INF ((int64)1E18L)
#define MOD 1000000007
int MODP(int64 x) {
  int r = x % MOD;
  if (r < 0) r += MOD;
  return r;
}

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

int n, k;
vector<int> a, pos;

int getDist(int x, int y) {
  if (pos[x] <= pos[y]) {
    return pos[y] - pos[x];
  }
  return pos[y] + n - pos[x];
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  
  cin >> n >> k;
  
  a.resize(n + 1);
  pos.resize(n + 1);
  
  for_inc_range(i, 1, n) {
    cin >> a[i];
    pos[a[i]] = i;
  }
  
  vector<int64> ans(n + 1);
  
  ans[1] = getDist(n, 1);
  for_inc_range(i, 2, n) {
    ans[i] = ans[i - 1] + getDist(i - 1, i);
  }
  
  int64 ret = 0;
  
  if (k >= n) {
    ret = ret + (k / n) * ans[n];
  }
  
  if (k % n > 0) {
    ret = ret + ans[k % n];
  }
  
  ret -= getDist(n, 1);
  ret += pos[1] - 1;
  cout << ret << endl;
  return 0;
}
