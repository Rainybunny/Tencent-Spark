#ifndef OUTPUTER_H
#define OUTPUTER_H

#include "qctype.h"
#include <bits/stdc++.h>
/*
void output(const Schedule& ans, const char* CNAME = "cir") {
    // puts("import tensorcircuit as tc\n");
    // printf("%s = tc.Circuit(%d)\n", CNAME, 13);
    for (Gate cur: ans) {
        // printf("%s.%s(", CNAME, cur.name.c_str());
        puts(cur.name.c_str());
        for (int i = 0; i < (int)cur.subj.size(); ++i) {
            if (i) putchar(' ');
            printf("%d", cur.subj[i]);
        }
        if (cur.name == "rz") printf(" %.12f", cur.param);
        putchar('\n');
        // if (cur.name == "rz") {
        //     printf("%d, %.12f", cur.subj[0], cur.param);
        // } else if (cur.name == "cz" || cur.name == "swap") {
        //     printf("%d, %d", cur.subj[0], cur.subj[1]);
        // } else {
        //     printf("%d", cur.subj[0]);
        // }
        // puts(")");
    }
}
*/

CircuitFile output(const std::vector<int>& prm, const Schedule& ans) {
    CircuitFile ncf;
    ncf.resize(ans.size() * 2 + 1);

    std::stringstream out;
    auto load = [&](const int i) { out = std::stringstream(ncf[i]); };

    load(0);
    for (int i = 0; i < (int)prm.size(); ++i) {
        out << prm[i];
        if (i + 1 != (int)prm.size()) out << ' ';
    }
    // puts("import tensorcircuit as tc\n");
    // printf("%s = tc.Circuit(%d)\n", CNAME, 13);
    for (int i = 0; i < (int)ans.size(); ++i) {
        const Gate& cur = ans[i];
        // printf("%s.%s(", CNAME, cur.name.c_str());
        load(2 * i + 1), out << cur.name;
        load(2 * i + 2);
        for (int i = 0; i < (int)cur.subj.size(); ++i) {
            if (i) out << ' ';
            out << cur.subj[i];
        }
        if (cur.name == "rz") {
            out << std::fixed << std::setprecision(12) << cur.param;
        }
        // if (cur.name == "rz") {
        //     printf("%d, %.12f", cur.subj[0], cur.param);
        // } else if (cur.name == "cz" || cur.name == "swap") {
        //     printf("%d, %d", cur.subj[0], cur.subj[1]);
        // } else {
        //     printf("%d", cur.subj[0]);
        // }
        // puts(")");
    }
    return ncf;
}

#endif