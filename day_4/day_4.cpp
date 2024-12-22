#include <bits/stdc++.h>

using namespace std;

long xmas_part1(vector<string> input) {
    long ans = 0;
    vector<vector<int>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
    string pattern = "MAS";
    int n = input.size();
    int m = input[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (input[i][j] != 'X') {
                continue;
            }

            for (auto dir : dirs) {
                string res = "";
                int x = i;
                int y = j;
                for (int k = 0; k < 3; k++) {
                    x += dir[0];
                    y += dir[1];
                    if (x < 0 || x >= n || y < 0 || y >= m) {
                        break;
                    }
                    res += input[x][y];
                }
                if (res == pattern) {
                    ans++;
                }
            
            }
        }

    }
    return ans;
}

long xmas_part2(vector<string> input) {
    long ans = 0;
    vector<vector<int>> dirs = {{1 , 1}, {-1, -1}, {1, -1}, {-1, 1}};
    string p1 = "MS", p2 = "SM";
    int n = input.size();
    int m = input[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (input[i][j] != 'A') {
                continue;
            }

            string a, b;

            for (int k = 0; k < 2; k++) {
                int x = i + dirs[k][0];
                int y = j + dirs[k][1];
                if (x < 0 || x >= n || y < 0 || y >= m) {
                    break;
                }
                a += input[x][y];
            }

            if (a != p1 && a != p2) {
                continue;
            }

            for (int k = 2; k < 4; k++) {
                int x = i + dirs[k][0];
                int y = j + dirs[k][1];
                if (x < 0 || x >= n || y < 0 || y >= m) {
                    break;
                }
                b += input[x][y];
            }

            if (b != p1 && b != p2) {
                continue;
            }
            ans++;
        }

    }
    return ans;
}


int main() {
    string s;
    vector<string> input;
    ifstream in("in.txt");
    while (getline(in, s)) {
        input.push_back(s);
    }
    cout << xmas_part1(input) << endl;
    cout << xmas_part2(input) << endl;
    return 0;
}