#include <bits/stdc++.h>

using namespace std;

long long checksum_part1(vector<int> &file_sys) {
    vector<int> tree;
    long long sum = 0;
    for (int i = 0; i < file_sys.size(); ++i) {
        if (i & 1) {
            tree.insert(tree.end(), file_sys[i], -1);
        }
        else {
            tree.insert(tree.end(), file_sys[i], i / 2);
        }
    }

    int i = 0, j = tree.size() - 1;
    while (i < j) {
        if (tree[i] == -1 && tree[j] != -1) {
            swap(tree[i], tree[j]);
        }
        else {
            if (tree[i] != -1) {
                ++i;
            }
            if (tree[j] == -1) {
                --j;
            }
        }
    }

    for (int i = 0; i < tree.size() && tree[i] != -1; ++i) {
        sum += i * tree[i];
    }

    return sum;
}

long long chunk_checksum(vector<int> &file_sys) {
    int n = file_sys.size();
    int offset = n / 2 + 1;  // Offset to handle negative indices
    vector<int> sz(2 * offset, 0);  // Stores chunk sizes
    vector<int> pos(2 * offset, 0); // Stores chunk positions

    int j = 0, l = 0;
    for (int i = 0; i < n; i++) {
        int k = (i % 2 == 1) ? -(i / 2 + 1) : i / 2;
        if (i % 2 == 0) {
            j = k;
        }

        sz[k + offset] = file_sys[i];
        pos[k + offset] = l;
        l += file_sys[i];
    }

    while (j > 0) {
        for (int i = 1; i <= j; i++) {
            if (sz[-i + offset] < sz[j + offset]) {
                continue;
            }

            sz[-i + offset] -= sz[j + offset];
            pos[j + offset] = pos[-i + offset];
            pos[-i + offset] += sz[j + offset];

            break;
        }

        j--;
    }

    long long ans = 0;
    for (int i = 0; i < sz.size(); i++) {
        int n = i - offset; // Convert back to the original index
        if (n < 0) {
            continue;
        }

        for (int x = 0; x < sz[i]; x++) {
            ans += n * (pos[i] + x);
        }
    }

    return ans;
}

int main() {
    string s;
    ifstream in("in.txt");
    getline(in, s);
    vector<int> file_sys;
    for (char c : s) {
        file_sys.push_back(c - '0');
    }

    in.close();

    long long part1 = checksum_part1(file_sys);
    cout << "Part 1: " << part1 << endl;

    long long part2 = chunk_checksum(file_sys);
    cout << "Part 2: " << part2 << endl;
    
    return 0;
}