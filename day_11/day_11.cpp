#include <bits/stdc++.h>

typedef long long ll;
using namespace std;

int nums_digits(ll num) {
    int digits = 0;
    while (num) {
        num /= 10;
        digits++;
    }
    return digits;
}

ll stones_blinking(unordered_map<ll, unordered_map<int, ll>> &cache, ll stone, int iters) {
    if (iters == 0) {
        return 1;
    }

    if (cache.find(stone) != cache.end() && cache[stone].find(iters) != cache[stone].end()) {
        return cache[stone][iters];
    }

    if (stone == 0) {
        return cache[stone][iters] = stones_blinking(cache, 1, iters - 1);
    }

    int digits = nums_digits(stone);

    if (!(digits & 1)) {
        ll half = stone / pow(10, digits / 2);
        ll half2 = stone % (ll)pow(10, digits / 2);
        return cache[stone][iters] = stones_blinking(cache, half, iters - 1) + stones_blinking(cache, half2, iters - 1);
        
    }

    return cache[stone][iters] = stones_blinking(cache, stone * 2024, iters - 1);

}

int main() {
    vector<long long> v;
    ifstream in("in.txt");
    string ln;
    if (getline(in, ln)) {
        stringstream ss(ln);
        long long num;
        while (ss >> num) {
            v.push_back(num);
        }
    }

    ll part_1 = 0;
    ll part_2 = 0;
    
    unordered_map<ll, unordered_map<int, ll>> cache;

    for (auto i : v) {
        part_1 += stones_blinking(cache, i, 25);
    }

    for (auto i : v) {
        part_2 += stones_blinking(cache, i, 75);
    }

    cout << "Part 1: " << part_1 << endl;

    cout << "Part 2: " << part_2 << endl;

    return 0;
}