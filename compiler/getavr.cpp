/*+Rainybunny+*/

#include <bits/stdc++.h>

#define rep(i, l, r) for (int i = l, rep##i = r; i <= rep##i; ++i)
#define per(i, r, l) for (int i = r, per##i = l; i >= per##i; --i)

inline char fgc() {
    static char buf[1 << 17], *p = buf, *q = buf;
    return p == q && (q = buf + fread(p = buf, 1, 1 << 17, stdin), p == q)
    ? EOF : *p++;
}

template <typename Tp = int>
inline Tp rint() {
    Tp x = 0, s = fgc(), f = 1;
    for (; s < '0' || '9' < s; s = fgc()) f = s == '-' ? -f : f;
    for (; '0' <= s && s <= '9'; s = fgc()) x = x * 10 + (s ^ '0');
    return x * f;
}

template <typename Tp>
inline void wint(Tp x) {
    if (x < 0) putchar('-'), x = -x;
    if (9 < x) wint(x / 10);
    putchar(x % 10 ^ '0');
}

int main() {
    int n = 100, sum = 0;
    while (n--) {
        int x = rint();
        sum += x;
    }
    printf("%f\n", sum / 100.);
    return 0;
}
