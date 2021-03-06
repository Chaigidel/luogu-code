#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define per(i, l, r) for (int i = (l); i >= (r); --i)
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
typedef pair<int, int> pii;
typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;

const int N = 109;
double a[N][N];
int n;
void swapline(int x, int y) {
    if (x == y) return;
    rep(i, 1, n + 1) std::swap(a[x][i], a[y][i]);
}

const double eps = 1e-8;

int main() {
#ifdef LOCAL
    freopen("input", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);
    cout.tie(0);
    cin >> n;
    rep(i, 1, n) rep(j, 1, n + 1) cin >> a[i][j];
    rep(i, 1, n) {
        rep(j, i, n) {
            if (std::abs(a[j][i]) > eps) {
                swapline(i, j);
                break;
            }
        }
        if (std::abs(a[i][i]) < eps) {
            cout << "No Solution";
            return 0;
        }
        rep(j, 1, n) {
            if (i == j) continue;
            double rate = a[j][i] / a[i][i];
            rep(k, 1, n + 1) a[j][k] -= a[i][k] * rate;
        }
    }
    cout.setf(std::ios::fixed);
    rep(i, 1, n) { cout << std::setprecision(2) << (a[i][n + 1] / a[i][i]) << endl; }
    return 0;
}