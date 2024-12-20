#include <bits/stdc++.h>

using namespace std;

int part1(vector<int> v1, vector<int> v2) {
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    int res = 0;
    for (int i = 0; i < v1.size(); ++i) {
        res += abs(v1[i] - v2[i]);
    }
    return res;
}

int part2(vector<int> v1, vector<int> v2) {
    unordered_map<int, int> m;

    for (int i = 0; i < v2.size(); i++) {
        m[v2[i]]++;
    }
    int res = 0;
    for (int i = 0; i < v1.size(); i++) {
        if (m.find(v1[i]) != m.end()) {
            res += v1[i] * m[v1[i]];
        }
    }
    
    return res;
}



int main() {
    freopen("in.txt", "r", stdin);

    int sum = 0;
    
    int a, b;
    vector<int> v1, v2;
    while (cin >> a >> b) {
        v1.push_back(a);
        v2.push_back(b);
    }

    int res_part1 = part1(v1, v2);
    int res_part2 = part2(v1, v2);
    cout << "Part 1: " << res_part1 << endl;
    cout << "Part 2: " << res_part2 << endl;
    return 0;
}