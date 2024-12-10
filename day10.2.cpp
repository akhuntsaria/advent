#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef long long u64;

int walk(vector<vector<int>>& m, int i, int j, int prev) {
    if (i < 0 || j < 0 || i >= m.size() || j >= m[i].size()) return 0;
    
    int curr = m[i][j];
    if (curr - prev != 1) return 0;
    
    if (curr == 9) {
        return 1;
    }
    
    int s = 0;
    s += walk(m, i - 1, j, curr);
    s += walk(m, i, j + 1, curr);
    s += walk(m, i + 1, j, curr);
    s += walk(m, i, j - 1, curr);
    return s;
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
                sum += walk(map, i, j, -1);
            }
        }
    }
    
    cout << sum << endl;

    return 0;
}
/*

 */
