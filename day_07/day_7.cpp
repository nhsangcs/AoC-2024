#include <bits/stdc++.h>
using namespace std;

bool check_calibration(int64_t n, const vector<int64_t>& ns);
int64_t cal(const vector<int64_t>& ns, const vector<int>& ops);
bool check_calibration_with_concatenation(int64_t n, const vector<int64_t>& ns);
int64_t cal_with_concatenation(const vector<int64_t>& ns, const vector<int>& ops);
int64_t n_len(int64_t n);

int main() {
    ifstream file("in.txt");
    if (!file.is_open()) {
        cerr << "Problem opening input file." << endl;
        return 1;
    }

    string line;
    int64_t part_1 = 0;
    int64_t part_2 = 0;

    while (getline(file, line)) {
        replace(line.begin(), line.end(), ':', ' '); // Replace ':' with space
        stringstream ss(line);
        vector<int64_t> ns;
        int64_t num;

        while (ss >> num) {
            ns.push_back(num);
        }

        int64_t n = ns[0];
        ns.erase(ns.begin()); // Remove the first element from the list

        if (check_calibration(n, ns)) {
            part_1 += n;
        }

        if (check_calibration_with_concatenation(n, ns)) {
            part_2 += n;
        }
    }

    cout << part_1 << endl;
    cout << part_2 << endl;

    return 0;
}

bool check_calibration(int64_t n, const vector<int64_t>& ns) {
    int l = ns.size() - 1;
    vector<int> ops(l, 0);
    int all = 1 << l; // 2^l
    for (int i = 0; i < all; ++i) {
        int j = i;
        for (auto& op : ops) {
            op = j % 2;
            j /= 2;
        }

        if (cal(ns, ops) == n) {
            return true;
        }
    }
    return false;
}

int64_t cal(const vector<int64_t>& ns, const vector<int>& ops) {
    int64_t ans = ns[0];
    for (int i = 0; i < ops.size(); ++i) {
        ans = (ops[i] == 0) ? ans + ns[i + 1] : ans * ns[i + 1];
    }
    return ans;
}

bool check_calibration_with_concatenation(int64_t n, const vector<int64_t>& ns) {
    int l = ns.size() - 1;
    vector<int> ops(l, 0);
    int all = pow(3, l); // 3^l
    for (int i = 0; i < all; ++i) {
        int j = i;
        for (auto& op : ops) {
            op = j % 3;
            j /= 3;
        }

        if (cal_with_concatenation(ns, ops) == n) {
            return true;
        }
    }
    return false;
}

int64_t cal_with_concatenation(const vector<int64_t>& ns, const vector<int>& ops) {
    int64_t ans = ns[0];
    for (int i = 0; i < ops.size(); ++i) {
        if (ops[i] == 0) {
            ans += ns[i + 1];
        } else if (ops[i] == 1) {
            ans *= ns[i + 1];
        } else {
            ans = ans * n_len(ns[i + 1]) + ns[i + 1];
        }
    }
    return ans;
}

int64_t n_len(int64_t n) {
    int64_t ans = 1;
    while (n > 0) {
        ans *= 10;
        n /= 10;
    }
    return ans;
}
