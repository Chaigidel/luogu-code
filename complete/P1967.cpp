#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("inline")
// #pragma GCC optimize("-fgcse")
// #pragma GCC optimize("-fgcse-lm")
// #pragma GCC optimize("-fipa-sra")
// #pragma GCC optimize("-ftree-pre")
// #pragma GCC optimize("-ftree-vrp")
// #pragma GCC optimize("-fpeephole2")
// #pragma GCC optimize("-ffast-math")
// #pragma GCC optimize("-fsched-spec")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC optimize("-falign-jumps")
// #pragma GCC optimize("-falign-loops")
// #pragma GCC optimize("-falign-labels")
// #pragma GCC optimize("-fdevirtualize")
// #pragma GCC optimize("-fcaller-saves")
// #pragma GCC optimize("-fcrossjumping")
// #pragma GCC optimize("-fthread-jumps")
// #pragma GCC optimize("-funroll-loops")
// #pragma GCC optimize("-fwhole-program")
// #pragma GCC optimize("-freorder-blocks")
// #pragma GCC optimize("-fschedule-insns")
// #pragma GCC optimize("inline-functions")
// #pragma GCC optimize("-ftree-tail-merge")
// #pragma GCC optimize("-fschedule-insns2")
// #pragma GCC optimize("-fstrict-aliasing")
// #pragma GCC optimize("-fstrict-overflow")
// #pragma GCC optimize("-falign-functions")
// #pragma GCC optimize("-fcse-skip-blocks")
// #pragma GCC optimize("-fcse-follow-jumps")
// #pragma GCC optimize("-fsched-interblock")
// #pragma GCC optimize("-fpartial-inlining")
// #pragma GCC optimize("no-stack-protector")
// #pragma GCC optimize("-freorder-functions")
// #pragma GCC optimize("-findirect-inlining")
// #pragma GCC optimize("-fhoist-adjacent-loads")
// #pragma GCC optimize("-frerun-cse-after-loop")
// #pragma GCC optimize("inline-small-functions")
// #pragma GCC optimize("-finline-small-functions")
// #pragma GCC optimize("-ftree-switch-conversion")
// #pragma GCC optimize("-foptimize-sibling-calls")
// #pragma GCC optimize("-fexpensive-optimizations")
// #pragma GCC optimize("-funsafe-loop-optimizations")
// #pragma GCC optimize("inline-functions-called-once")
// #pragma GCC optimize("-fdelete-null-pointer-checks")
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define per(i, l, r) for (int i = (l); i >= (r); --i)
using std::cerr;
using std::endl;
using std::make_pair;
using std::pair;
typedef pair<int, int> pii;
typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;

// #define DEBUG 1  //调试开关
struct IO {
#define MAXSIZE (1 << 20)
#define isdigit(x) (x >= '0' && x <= '9')
    char buf[MAXSIZE], *p1, *p2;
    char pbuf[MAXSIZE], *pp;
#if DEBUG
#else
    IO() : p1(buf), p2(buf), pp(pbuf) {}
    ~IO() { fwrite(pbuf, 1, pp - pbuf, stdout); }
#endif
    inline char gc() {
#if DEBUG  //调试，可显示字符
        return getchar();
#endif
        if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin);
        return p1 == p2 ? -1 : *p1++;
    }
    inline bool blank(char ch) { return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t'; }
    template <class T>
    inline void read(T &x) {
        register double tmp = 1;
        register bool sign = 0;
        x = 0;
        register char ch = gc();
        for (; !isdigit(ch); ch = gc())
            if (ch == '-') sign = 1;
        for (; isdigit(ch); ch = gc()) x = x * 10 + (ch - '0');
        if (ch == '.')
            for (ch = gc(); isdigit(ch); ch = gc()) tmp /= 10.0, x += tmp * (ch - '0');
        if (sign) x = -x;
    }
    inline void read(char *s) {
        register char ch = gc();
        for (; blank(ch); ch = gc())
            ;
        for (; !blank(ch); ch = gc()) *s++ = ch;
        *s = 0;
    }
    inline void read(char &c) {
        for (c = gc(); blank(c); c = gc())
            ;
    }
    inline void push(const char &c) {
#if DEBUG  //调试，可显示字符
        putchar(c);
#else
        if (pp - pbuf == MAXSIZE) fwrite(pbuf, 1, MAXSIZE, stdout), pp = pbuf;
        *pp++ = c;
#endif
    }
    template <class T>
    inline void write(T x) {
        if (x < 0) x = -x, push('-');  // 负数输出
        static T sta[35];
        T top = 0;
        do {
            sta[top++] = x % 10, x /= 10;
        } while (x);
        while (top) push(sta[--top] + '0');
    }
    inline void write(const char *s) {
        while (*s != '\0') push(*(s++));
    }
    template <class T>
    inline void write(T x, char lastChar) {
        write(x), push(lastChar);
    }
} io;

struct Edge {
    int x, y, z;
} e[100100];
const int N = 10010;

namespace UnionFindSet {
template <int N>
struct UnionFindSet {
    int fa[N];
    UnionFindSet() {
        for (register int i = 0; i < N; ++i) fa[i] = i;
    }
    int getf(int x) { return fa[x] = (fa[x] == x ? x : getf(fa[x])); }
    inline void merge(int x, int y) { fa[getf(x)] = getf(y); }
    inline bool same(int x, int y) { return getf(x) == getf(y); }
};
};  // namespace UnionFindSet

UnionFindSet::UnionFindSet<N> ufs;

std::vector<pii> g[N];

const int K = 19;
int f[K + 1][N], fa[K + 1][N], dep[N];
void dfs1(int u) {
    for (auto i : g[u]) {
        int v = i.first, w = i.second;
        if (v == fa[0][u]) continue;
        // cerr << u << ' ' << v << ' ' << w << endl;
        fa[0][v] = u, dep[v] = dep[u] + 1, f[0][v] = w;
        dfs1(v);
    }
}

int main() {
#ifdef LOCAL
    freopen("input", "r", stdin);
#endif
    int n, m;
    io.read(n), io.read(m);
    rep(i, 1, m) io.read(e[i].x), io.read(e[i].y), io.read(e[i].z);
    int rt = 0;
    rep(i, 1, n) e[m + i].x = rt, e[m + i].y = i, e[m + i].z = -1;
    m += n;
    std::sort(e + 1, e + 1 + m, [](const Edge &a, const Edge &b) -> bool { return a.z > b.z; });
    for (int i = 1, cnt = 0; cnt <= n && i <= m; ++i) {
        if (!ufs.same(e[i].x, e[i].y)) {
            ufs.merge(e[i].x, e[i].y);
            g[e[i].x].push_back({e[i].y, e[i].z});
            g[e[i].y].push_back({e[i].x, e[i].z});
        }
    }

    // rep(u, 0, n) {
    //     for (auto i : g[u]) {
    //         cerr << u << ' ' << i.first << ' ' << i.second << endl;
    //     }
    // }
    // cerr << "printed edge " << endl;

    dfs1(rt);
    rep(k, 1, K) rep(i, 0, n) fa[k][i] = fa[k - 1][fa[k - 1][i]], f[k][i] = std::min(f[k - 1][i], f[k - 1][fa[k - 1][i]]);

    // rep(i, 1, n) cerr << f[1][i] << ' ';
    // cerr << endl;

#define ckmin(x, y) x = std::min(x, y)

    int q, x, y;
    io.read(q);
    while (q--) {
        io.read(x), io.read(y);
        int ans = 100000;
        if (dep[x] < dep[y]) std::swap(x, y);
        int delta = dep[x] - dep[y];
        per(k, K, 0) if (delta >= (1 << k)) ckmin(ans, f[k][x]), x = fa[k][x], delta -= (1 << k);
        if (x != y) {
            per(k, K, 0) {
                if (fa[k][x] != fa[k][y]) {
                    ckmin(ans, f[k][x]), x = fa[k][x];
                    ckmin(ans, f[k][y]), y = fa[k][y];
                }
            }
            ckmin(ans, f[0][x]), ckmin(ans, f[0][y]);
        }
        io.write(ans, '\n');
    }
    return 0;
}