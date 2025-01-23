#include <bits/stdc++.h>


using namespace std;

const int N = 1000;


bool follows_rules(vector<unordered_set<int>>& dag, vector<int>& order) {
    for (int i = 1; i < order.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (dag[order[i]].count(order[j])) {
                return false;
            }
        }
    }
    return true;
}

vector<int> topo(vector<unordered_set<int>>& dag, vector<int>& order) {
    vector<int> ins;

    unordered_set<int> order_set(order.begin(), order.end());
    unordered_map<int, vector<int>> graph;

    for (int u = 0; u < dag.size(); ++u) {
        if (!order_set.count(u)) continue;

        for (int v : dag[u]) {
            if (order_set.count(v)) {
                graph[v].push_back(u);
            }
        }
    }

    unordered_map<int, int> degree;
    for (const auto& [u, vs] : graph) {
        degree[u]; // Ensure u is in the degree map
        for (int v : vs) {
            degree[v]++;
        }
    }

    deque<int> q;
    for (const auto& [u, d] : degree) {
        if (d == 0) {
            q.push_back(u);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        ins.push_back(u);

        if (graph.count(u)) {
            for (int v : graph[u]) {
                degree[v]--;
                if (degree[v] == 0) {
                    q.push_back(v);
                }
            }
        }
    }

    return ins;
}

int main() {
    string s;
    ifstream in("in.txt");
    vector<unordered_set<int>> dag(N);
    while (getline(in, s)) {
        if (s.empty()) {
            break;
        }
        int a = stoi(s.substr(0, 2));
        int b = stoi(s.substr(3));
        dag[a].insert(b);
    }

    int res_part1 = 0, res_part2 = 0, res_part2_recur = 0;
    
    while (getline(in, s)) {
        vector<int> v;
        stringstream ss(s);
        string x;
        while (getline(ss, x, ',')) {
            v.push_back(stoi(x));
        }

        if (follows_rules(dag, v)) {
            res_part1 += v[v.size() / 2];
        }
        else {
            vector<int> ins = topo(dag, v);
            res_part2 += ins[ins.size() / 2];
            
        }
        
    }

    cout << "Part 1: " << res_part1 << endl;
    cout << "Part 2: " << res_part2 << endl;
    return 0;
}