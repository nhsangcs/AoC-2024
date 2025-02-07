#include <bits/stdc++.h>

using namespace std;

const int N = 103, M = 101;
int N_mid = N / 2, M_mid = M / 2;

int quadrants[4];
void solve(int x, int y, int vx, int vy) {
    int m = ((x + vx * 100) % M + M) % M;
	int n = ((y + vy * 100) % N + N) % N;
	if (m < M_mid && n < N_mid) {
		quadrants[0]++;
	} else if (m < M_mid && n > N_mid) {
		quadrants[1]++;
	} else if (m > M_mid && n < N_mid) {
		quadrants[2]++;
	} else if (m > M_mid && n > N_mid) {
		quadrants[3]++;
	}
}

int main() {
    ifstream in("in.txt");
    string line;
    regex pattern(R"(p=(\d+),(\d+)\s+v=(-?\d+),(-?\d+))");
    smatch match;

    while (getline(in, line)) {
        regex_search(line, match, pattern);
        int x = stoi(match[1].str()), y = stoi(match[2].str()), vx = stoi(match[3].str()), vy = stoi(match[4].str());
        solve(x, y, vx, vy);
    }
    int part1 = 1;
    for (int i : quadrants) {
        part1 *= i;
    }
    cout << "Part 1: " << part1 << endl;

    return 0;
}