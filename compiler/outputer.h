#ifndef OUTPUTER_H
#define OUTPUTER_H

#include "qctype.h"
#include <cstdio>
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

void output(const std::vector<int>& prm, const Schedule& ans) {
    for (int i = 0; i < (int)prm.size(); ++i) {
        printf("%d%c", prm[i], "\n "[i + 1 != (int)prm.size()]);
    }
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

#endif