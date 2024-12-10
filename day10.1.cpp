#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef long long u64;

struct pair_hash {
    inline size_t operator()(const pair<int,int>& v) const {
        return v.first * 31 + v.second;
    }
};

void walk(vector<vector<int>>& m, int i, int j, int prev, unordered_set<pair<int, int>,pair_hash>& peaks) {
    if (i < 0 || j < 0 || i >= m.size() || j >= m[i].size()) return;
    
    int curr = m[i][j];
    if (curr - prev != 1) return;
    
    if (curr == 9) {
        peaks.insert({i, j});
        return;
    }
    
    walk(m, i - 1, j, curr, peaks);
    walk(m, i, j + 1, curr, peaks);
    walk(m, i + 1, j, curr, peaks);
    walk(m, i, j - 1, curr, peaks);
}

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    vector<vector<int>> map;
    string line;
    while (getline(file, line)) {
        vector<int> row;
        for (char c : line) {
            row.push_back(c - '0');
        }
        map.push_back(row);
    }
    
    int sum = 0;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 0) {
                unordered_set<pair<int, int>,pair_hash> peaks;
                walk(map, i, j, -1, peaks);
                sum += peaks.size();
            }
        }
    }
    
    cout << sum << endl;

    return 0;
}
/*

 */
