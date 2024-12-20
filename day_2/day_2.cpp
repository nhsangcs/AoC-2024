#include <bits/stdc++.h>

using namespace std;

int isSafe(vector<int> v) {
    int n = v.size();
    if (n <= 1) {
        return -1;
    }
    bool isDecreasing = false;
    if (v[0] > v[1]) {
        isDecreasing = -1;
    }
    for (int i = 1; i < n; i++) {
        if (isDecreasing) {
            if (v[i - 1] - v[i] > 3 || v[i - 1] - v[i] < 1) {
                return i;
            }
        }
        else if (v[i] - v[i - 1] > 3 || v[i] - v[i - 1] < 1) {
            return i;
        }
    }
    return -1;
}

int main() {
    freopen("in.txt", "r", stdin);

    int res_part1 = 0, res_part2 = 0;
    string line;
    while (getline(cin, line)) {
        vector<int> v;
        istringstream iss(line);
        int a;
        while (iss >> a) {
            v.push_back(a);
        }
        int pivot = isSafe(v);
        if (pivot <= 0) {
            res_part1++;
            res_part2++;
        }
        else {
            if (v.size() == 2) {
                res_part2++;
                continue;
            }
            for (int i = -2; i < 2; i++) {
                vector<int> v1 = v;
                if (pivot + i >= 0 && pivot + i < v.size())
                    v1.erase(v1.begin() + pivot + i);
                if (isSafe(v1) <= 0) {
                    res_part2++;
                    break;
                }
            }
            

        }
    }
    cout << "Part 1: " << res_part1 << endl;
    cout << "Part 2: " << res_part2 << endl;

    return 0;
}