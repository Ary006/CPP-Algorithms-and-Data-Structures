#ifndef STRINGCONSTRUCTION_H
#define STRINGCONSTRUCTION_H

#include <string>
#include <vector>
#include <algorithm>

using std::string;


// TODO: your code goes here:
std::vector<int> z_Function(const string& s) {
    int n = s.size();
    std::vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r)
            z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

std::size_t best_Clone(const string& s, int L_min) {
    string r = s;
    std::reverse(r.begin(), r.end());
    auto z = z_Function(r);
    std::size_t best = 0;
    for (std::size_t i = 0; i < z.size(); i++) {
        if (i >= L_min) {
            best = std::max(best, std::min((std::size_t)z[i], i));
        }
    }
    return s.length() - best;
}

int stringConstruction(const string& target, int cloneCost, int appendCost) {
    using Cost = unsigned long long;
    int n = target.size();
    std::vector<Cost> costs(n + 1, 0);

    int L_min = (cloneCost + appendCost - 1) / appendCost;

    for (int j = 0; j < n; ++j) {
        costs[j + 1] = costs[j] + appendCost;

        string s = target.substr(0, j + 1);
        std::size_t i = best_Clone(s, L_min);

        if (i <= j - L_min + 1) {
            costs[j + 1] = std::min(costs[j + 1], costs[i] + cloneCost);
        }
    }
    return costs[n];
}


// do not write or edit anything below this line


#endif