#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

bool isValid(int x, int y, int prevHeight, vector<vector<int>>& map, vector<vector<bool>>& visited) {
    return x >= 0 && x < n && y >= 0 && y < m && !visited[x][y] && map[x][y] == prevHeight + 1;
}

int dfs(int x, int y, vector<vector<int>>& map, vector<vector<bool>>& visited, set<pair<int, int>>& endpoints) {
    if (map[x][y] == 9) {
        endpoints.insert({x, y});
        return 1;
    }

    visited[x][y] = true;
    int paths = 0;

    for (auto dir : dirs) {
        int newX = x + dir[0];
        int newY = y + dir[1];
        if (isValid(newX, newY, map[x][y], map, visited)) {
            paths += dfs(newX, newY, map, visited, endpoints);
        }
    }

    visited[x][y] = false;
    return paths;
}

int main() {
    vector<vector<int>> map;
    string line;

    ifstream in("in.txt");
    while (getline(in, line)) {
        vector<int> row;
        for (char c : line) {
            row.push_back(c - '0');
        }
        map.push_back(row);
    }
    in.close();

    n = map.size();
    m = map[0].size();

    int totalPaths = 0;
    int uniquePaths = 0;
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map[i][j] == 0) {
                set<pair<int, int>> endpoints;
                totalPaths += dfs(i, j, map, visited, endpoints);
                uniquePaths += endpoints.size();
            }
        }
    }

    cout << "Part 1: " << uniquePaths << endl;

    cout << "Part 2: " << totalPaths << endl;

    return 0;
}