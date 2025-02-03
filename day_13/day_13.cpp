#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll part1 = 0, part2 = 0;

void solve(ll a1, ll b1, ll a2, ll b2, ll x, ll y, ll &ans) {
    ll det = a1 * b2 - a2 * b1;

    if (det == 0) {
        return;
    }

    ll det_x = x * b2 - y * a2;
    ll det_y = a1 * y - b1 * x;

    if (det_x % det != 0 || det_y % det != 0) {
        return;
    }

    ll x1 = det_x / det, y1 = det_y / det;
    ans += 3 * x1 + y1;
}

int main() {
    ifstream in("in.txt");
    string line;
    regex button_a(R"(Button A: X\+(\d+), Y\+(\d+))"),
		button_b(R"(Button B: X\+(\d+), Y\+(\d+))"),
		prize(R"(Prize: X=(\d+), Y=(\d+))");
    smatch match;

    while (getline(in, line)) {
        regex_search(line, match, button_a);
        int x_a = stoi(match[1].str()), y_a = stoi(match[2].str());

        getline(in, line);
        regex_search(line, match, button_b);
        int x_b = stoi(match[1].str()), y_b = stoi(match[2].str());

        getline(in, line);
        regex_search(line, match, prize);
        int x_p = stoi(match[1].str()), y_p = stoi(match[2].str());

        solve(x_a, y_a, x_b, y_b, x_p, y_p, part1);
        solve(x_a, y_a, x_b, y_b, x_p + 1e13, y_p + 1e13, part2);

        getline(in, line);
    }
    
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    
    return 0;
}