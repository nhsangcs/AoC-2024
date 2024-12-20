#include <bits/stdc++.h>

using namespace std;

long mul_string(smatch match) {
    long a = stol(match[1]);
    long b = stol(match[2]);
    return a * b;
}

long regex_mul(string s) {
    regex pattern(R"(mul\((\d+),(\d+)\))");
    smatch match;
    long res = 0;

    while (regex_search(s, match, pattern)) {
        res += mul_string(match);
        s = match.suffix();
    }

    return res;
}

bool enable = true;

long regex_mul_with_ins(string s) {
    regex pattern(R"(mul\((\d+),(\d+)\)|do\(\)|don't\(\))");
    smatch match;
    long res = 0;

    while (regex_search(s, match, pattern)) {
        if (match[0] == "do()") {
            enable = true;
        }
        else if (match[0] == "don't()") {
            enable = false;
        }
        else if (enable) {
            res += mul_string(match);
        }
        s = match.suffix();
        
    }

    return res;

}

int main() {
    string s, input;
    ifstream in("in.txt");
    while (getline(in, s)) {
        input += s;
    }

    long res_part1 = regex_mul(input);
    cout << "Part 1: " << res_part1 << endl;
    
    long res_part2 = regex_mul_with_ins(input);
    cout << "Part 2: " << res_part2 << endl;

    return 0;
}