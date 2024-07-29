#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <bits/stdc++.h>

#include "qctype.h"

namespace Init {

/**
 * Read source circuit from a formatted text file.
 **/
std::pair<int, Schedule> readScr() {
    Schedule res;
    std::string buf;

    int n = 13;
    // std::cin >> n;
    while (std::getline(std::cin, buf)) {
        if (buf == "") continue;
        Gate cur; int siz;
        cur.name = buf;
        std::cin >> siz, cur.subj.resize(siz);
        for (int& s: cur.subj) std::cin >> s;
        std::cin >> cur.param;
        res.emplace_back(cur);
    }
    return { n, res };
}

namespace TranslateBase {

Schedule res;

const double PI = acos(-1);

void append(const Gate&);
void cnot(int, int);
void toffoli(int, int, int);
void sqx(int);
void ry(int, double);
void rx(int, double);
void rzz(int, int, double);

void append(const Gate& g) {
    static const std::set<std::string> BASE = {
        "h", "s", "sd", "x", "y", "z", "cz", "swap", "rz"
    };

    if (BASE.find(g.name) != BASE.end()) res.emplace_back(g);
    else if (g.name == "cnot") {
        // res.emplace_back(g);
        cnot(g.subj[0], g.subj[1]);
    }
    else if (g.name == "toffoli") toffoli(g.subj[0], g.subj[1], g.subj[2]);
    else if (g.name == "sqx") sqx(g.subj[0]);
    else if (g.name == "ry") ry(g.subj[0], g.param);
    else if (g.name == "rx") rx(g.subj[0], g.param);
    else if (g.name == "rzz") rzz(g.subj[0], g.subj[1], g.param);
    else {
        fprintf(stderr, "Unsupported gate '%s'.\n", g.name.c_str());
        exit(1); // error code
    }
}

void toffoli(const int _0, const int _1, const int _2) {
    append({ "h", { _2 }, 0 });
    append({ "cnot", { _1, _2 }, 0 });
    append({ "td", { _2 }, 0 });
    append({ "cnot", { _0, _2 }, 0 });
    append({ "t", { _2 }, 0 });
    append({ "cnot", { _1, _2 }, 0 });
    append({ "td", { _1 }, 0 });
    append({ "t", { _2 }, 0 });
    append({ "cnot", { _0, _1 }, 0 });
    append({ "h", { _2 }, 0 });
    append({ "td", { _1 }, 0 });
    append({ "cnot", { _0, _1 }, 0 });
    append({ "t", { _0 }, 0 });
    append({ "s", { _1 }, 0 });
}

void cnot(int i, int j)
{
	append({ "h",{j},0.0 });
	append({ "cz",{i,j},0.0 });
	append({ "h",{j},0.0 });
}

void sqx(int j)//[[1,j],[j,1]]
{
	append({ "h",{j},0.0 });
	append({ "rz",{j},-PI/2 });
	append({ "h",{j},0.0 });
}

void ry(int x, double theta)
{
	append({ "sqx",{x},0.0 });
	append({ "rz",{x},-theta });
	append({ "x",{x},0.0 });
	append({ "sqx",{x},0.0 });
}

void rx(int x, double theta)
{
	append({ "h",{x},0.0 });
	append({ "rz",{x},theta });
	append({ "h",{x},0.0 });
}

inline bool sign(const double x) {
    static const double EPS = 1e-8;
    if (-EPS < x && x < EPS) return 0;
    return x < 0 ? -1 : 1;
}

void rzz(int x, int y, double theta)
{
    static const double HALF_PI = PI / 2.;
    if (!sign(theta - HALF_PI)) { // theta = pi/2
        append({ "x", { y }, 0 }), append({ "h", { y }, 0 });
        append({ "cnot", { x, y } });
        append({ "h", { y }, 0 }), append({ "x", { y }, 0 });
        append({ "s", { x }, 0 }), append({ "s", { y }, 0 });
    } else if (!sign(theta + HALF_PI)) { // theta = -pi/2
        append({ "sd", { x }, 0 }), append({ "sd", { y }, 0 });
        append({ "x", { y }, 0 }), append({ "h", { y }, 0 });
        append({ "cnot", { x, y }, 0 });
        append({ "h", { y }, 0 }), append({ "x", { y }, 0 });
    } else {
        append({ "cnot",{x,y},0.0 });
        append({ "rz",{y},theta });
        append({ "cnot",{x,y},0.0 });
    }
}



} // namespace TranslateBase

Schedule translate(const Schedule& ori) {
    using namespace TranslateBase;
    res.clear();
    for (Gate cur: ori) append(cur);
    return res;
}

Schedule cancelSingle(const int n, Schedule sch) {
    size_t nsiz = sch.size();
    std::vector<std::vector<int>> sgate(n);
    for (int i = 0; i < (int)sch.size(); ++i) {
        Gate cur = sch[i];
        assert(1 <= cur.subj.size() && cur.subj.size() <= 2);
        if (cur.subj.size() == 2) {
            sgate[cur.subj[0]].clear(), sgate[cur.subj[1]].clear();
        } else {
            int p = cur.subj[0];
            static const std::set<std::string> CANCEL = {
                "x", "y", "z", "h"
            };
            if (sgate[p].size() && sch[sgate[p].back()].name == cur.name
            && CANCEL.find(cur.name) != CANCEL.end()) {
                nsiz -= 2;
                sch[sgate[p].back()].name = sch[i].name = "_ignore_";
            } else {
                sgate[p].push_back(i);
            }
        }
    }

    Schedule res; res.reserve(nsiz);
    for (Gate cur: sch) if (cur.name != "_ignore_") res.emplace_back(cur);
    return res;
}

Graph buildGraph(const int n, const Schedule& sch) {
    Graph G(sch.size());
    std::vector<int> lastRef(n, -1);
    for (int i = 0; i < (int)sch.size(); ++i) {
        Gate cur = sch[i];
        assert(1 <= cur.subj.size() && cur.subj.size() <= 2);
        if (cur.subj.size() == 1) {
            int &p = lastRef[cur.subj[0]];
            if (~p) G[p].push_back(i);
            p = i;
        } else {
            int &p = lastRef[cur.subj[0]], &q = lastRef[cur.subj[1]];
            if (~p) G[p].push_back(i);
            if (~q) G[q].push_back(i);
            p = q = i;
        }
    }
    return G;
}

void init(int& n, Schedule& sch, Graph& grp) {
    auto scr = readScr();
    n = scr.first;
    sch = cancelSingle(n, translate(scr.second));
#ifdef GATE_LOG
    fprintf(stderr, "initial basic gate: %zd\n", sch.size());
    size_t two = 0;
    for (Gate g: sch) {
        two += g.name == "swap" || g.name == "cz";
    }
    fprintf(stderr, "... with two-qubit gate: %zd\n", two);
#endif
    grp = buildGraph(n, sch);
}

} // namespace Init

// Schedule sch;
// Graph grp;

// int main() {
//     Init::init(n, sch, grp);
// }

#endif