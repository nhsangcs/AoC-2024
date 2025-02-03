#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
long long part1 = 0, part2 = 0;

class Region {
public:
    vector<vector<bool>> visited;
    int l, r, t, b;

    Region() {
        visited = vector<vector<bool>>(n, vector<bool>(m, false));
        l = m - 1, r = 0, t = n - 1, b = 0;
    }

    void add_point(int x, int y) {
        visited[x][y] = true;
        l = min(l, x);
        r = max(r, x);
        t = min(t, y);
        b = max(b, y);
    }
};

void dfs(vector<string> &map, vector<vector<bool>> &visited, int x, int y, long long &area, long long &perimeter, Region &region) {

    if (visited[x][y]) {
        return;
    }


    visited[x][y] = true;
    region.add_point(x, y);
    area++;
    perimeter += 4;


    for (auto &dir : dirs) {
        int nx = x + dir[0], ny = y + dir[1];
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && map[nx][ny] == map[x][y] && visited[nx][ny]) {
            perimeter -= 2;
        }
    }
    
    for (auto &dir : dirs) {
        int nx = x + dir[0], ny = y + dir[1];
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && map[nx][ny] == map[x][y]) {
            dfs(map, visited, nx, ny, area, perimeter, region);
        }
    }
}

void count(Region &region, bool &fence, long long &ans, int i, int j, int x,
		   int y) {
	if (!region.visited[i][j]) {
		fence = false;
	} else if (x < 0 || x >= n || y < 0 || y >= m || !region.visited[x][y]) {
		if (!fence) {
			fence = true, ans++;
		}
	} else {
		fence = false;
	}
}

long long count_sides(Region &region) {
	long long ans = 0;

	for (int i = region.l; i <= region.r; ++i) {
		bool fence = false;
		for (int j = region.t; j <= region.b; ++j) {
			count(region, fence, ans, i, j, i - 1, j);
		}

		fence = false;
		for (int j = region.t; j <= region.b; ++j) {
			count(region, fence, ans, i, j, i + 1, j);
		}
	}

	for (int j = region.t; j <= region.b; j++) {
		bool fence = false;
		for (int i = region.l; i <= region.r; i++) {
			count(region, fence, ans, i, j, i, j - 1);
		}

		fence = false;
		for (int i = region.l; i <= region.r; i++) {
			count(region, fence, ans, i, j, i, j + 1);
		}
	}
	return ans;
}

void total_price(vector<string> &map) {
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            long long area = 0, perimeter = 0;
            Region region = Region();
            dfs(map, visited, i, j, area, perimeter, region);
            if (area == 0) {
                continue;
            }
            part1 += perimeter * area;

            long long sides = count_sides(region);
            part2 += sides * area;

        }
    }
}


int main() {
    vector<string> map;
    string line;
    ifstream in("in.txt");
    while (getline(in, line)) {
        map.push_back(line);
    }
    n = map.size();
    m = map[0].size();

    total_price(map);

    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;

    return 0;
}