#include <bits/stdc++.h>

using namespace std;

int n, m;

bool isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int countAntinodes(vector<string> map, unordered_map<char, vector<pair<int, int>>> &antinodes) {
    int ans = 0;
    for (auto it : antinodes) {
        auto nodes = it.second;
        for (int i = 0; i < nodes.size() - 1; ++i) {
            for (int j = i + 1; j < nodes.size(); ++j) {
                int dx = nodes[i].first - nodes[j].first, dy = nodes[i].second - nodes[j].second;
                int nx = nodes[i].first + dx, ny = nodes[i].second + dy;

                if (isValid(nx, ny) && map[nx][ny] != '#') {
                    ++ans;
                    map[nx][ny] = '#';
                }

                int px = nodes[j].first - dx, py = nodes[j].second - dy;
                if (isValid(px, py) && map[px][py] != '#') {
                    ++ans;
                    map[px][py] = '#';
                }
            }
        }
    }
    return ans;
}

int countAntinodes_part2(vector<string> map, unordered_map<char, vector<pair<int, int>>> &antinodes) {
    int ans = 0;
    for (auto it : antinodes) {
        auto nodes = it.second;
        ans += nodes.size();
        for (int i = 0; i < nodes.size() - 1; ++i) {
            for (int j = i + 1; j < nodes.size(); ++j) {
                int dx = nodes[i].first - nodes[j].first, dy = nodes[i].second - nodes[j].second;
                int nx = nodes[i].first + dx, ny = nodes[i].second + dy;

                while (isValid(nx, ny)) {
                    if (map[nx][ny] == '.') {
                        map[nx][ny] = '#';
                        ++ans;
                    }
                    nx += dx;
                    ny += dy;
                }
                
                int px = nodes[j].first - dx, py = nodes[j].second - dy;
                while (isValid(px, py)) {
                    if (map[px][py] == '.') {
                        map[px][py] = '#';
                        ++ans;
                    }
                    px -= dx;
                    py -= dy;
                }

            }
        }
    }
    return ans;
}




int main() {
    string s;
    vector<string> map;
    ifstream in("in.txt");
    while (getline(in, s)) {
        map.push_back(s);
    }

    n = map.size();
    m = map[0].size();
    
    unordered_map<char, vector<pair<int, int>>> antinodes;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
			if (map[i][j] != '.') {
				antinodes[map[i][j]].push_back({i, j});
			}
        }
    }
    


    int part1 = countAntinodes(map, antinodes);
    cout << "Part 1:" << part1 << endl;

    int part2 = countAntinodes_part2(map, antinodes);
    cout << "Part 2:" << part2 << endl;

    return 0;
}