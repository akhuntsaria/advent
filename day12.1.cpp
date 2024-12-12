#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

typedef unsigned long long u64;

using namespace std;

vector<vector<int>> dirs = {{-1,0},{0,1},{1,0},{0,-1}};
int n, m;

int per(vector<string>& map, int i, int j, char c) {
    if (i < 0 || j < 0 || i >= n || j >= m) return 1;
    if (map[i][j] != c) return 1;
    return 0;
}

// Returns area and perimeter
pair<int, int> walk(vector<string>& map, int i, int j, vector<vector<bool>>& v, char prev) {
    if (i < 0 || j < 0 || i >= n || j >= m || v[i][j] || map[i][j] != prev) return {0, 0};
    
    v[i][j] = true;
    char c = map[i][j];
    pair<int, int> res = {1, 0};
    
    for (auto& dir : dirs) {
        res.second += per(map, i + dir[0], j + dir[1], c);

        auto next = walk(map, i + dir[0], j + dir[1], v, c);
        res.first += next.first;
        res.second += next.second;
    }
    
    return res;
}

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    vector<string> map;
    string line;
    while (getline(file, line)) {
        map.push_back(line);
    }

    n = map.size();
    m = map[0].size();
    vector<vector<bool>> v(n, vector<bool>(m));
    u64 sum = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            auto res = walk(map, i, j, v, map[i][j]);
            sum += res.first * res.second;
        }
    }
    
    cout << sum << endl;
    return 0;
}
/*
Perimeter = touches an edge or another region
*/