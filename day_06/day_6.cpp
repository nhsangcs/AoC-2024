#include <bits/stdc++.h>

using namespace std;

bool isValidIndex(int i, int j, int n, int m) {
    return i >= 0 && i < n && j >= 0 && j < m;
}

pair<pair<int, int>, char> findpos(vector<string> map) {
    int n = map.size();
    int m = map[0].size();
    pair<pair<int, int>, char> res;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c = map[i][j];
            if (c == '^' || c == 'v' || c == '<' || c == '>') {
                res.first = {i, j};
                res.second = c;
                return res;
            }
        }
    }
    return res;
}

pair<pair<int, int>, char> turnRight(pair<pair<int, int>, char> pos) {
    char c = pos.second;
    if (c == '^') {
        pos.second = '>';
    } else if (c == '>') {
        pos.second = 'v';
    } else if (c == 'v') {
        pos.second = '<';
    } else {
        pos.second = '^';
    }
    return pos;
}

pair<int, int> next(pair<pair<int, int>, char> pos) {
    int x = pos.first.first;
    int y = pos.first.second;
    char c = pos.second;
    if (c == '^') {
        x--;
    } else if (c == '>') {
        y++;
    } else if (c == 'v') {
        x++;
    } else {
        y--;
    }
    return {x, y};
}


int path(vector<string> map) {
    int n = map.size();
    int m = map[0].size();
    pair<pair<int, int>, char> pos = findpos(map);

    int x = pos.first.first;
    int y = pos.first.second;
    char c = pos.second;
    int ans = 1;

    if (!isValidIndex(x, y, n, m)) {
        return -1;
    }
    int turn = 0;
    while (true) {
        pair<int, int> nextPos = next(pos);
        int nextX = nextPos.first;
        int nextY = nextPos.second;
        if (!isValidIndex(nextX, nextY, n, m)) {
            ans++;
            break;
        }
        if (map[nextX][nextY] == '#') {
            pos = turnRight(pos);
            turn++;
            if (turn == 4) {
                break;
            }
        } else {
            turn = 0;
            if (map[x][y] == '.') {
                ans++;
            }
            map[x][y] = '*';
            pos.first = nextPos;
            x = nextX;
            y = nextY;
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

    int n = map.size();
    int m = map[0].size();

    cout << "Part 1: " << path(map) << endl;

    return 0;

}