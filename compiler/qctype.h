#ifndef QCTYPE_H
#define QCTYPE_H

#include <string>
#include <vector>

struct Gate {
    std::string name;
    std::vector<int> subj;
    double param;
};
// You may use `Gate{ name, { i, j, ... }, param }` to construct a Gate subj.

typedef std::vector<Gate> Schedule;
typedef std::vector<std::vector<int>> Graph;

#endif