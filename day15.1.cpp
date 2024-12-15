#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

unordered_map<char, pair<int,int>> dirs = {{'^', {-1,0}},{'>', {0,1}},{'v', {1,0}},{'<', {0,-1}}};

bool move(vector<string>& m, int i, int j, char dir) {
    char c = m[i][j];
    int ni = i + dirs[dir].first, nj = j + dirs[dir].second;
    if (m[ni][nj] == 'O') {
        move(m, ni, nj, dir);
    }
    if (m[ni][nj] == '.') {
        m[i][j] = '.';
        m[ni][nj] = c;
        return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    vector<string> m;
    string moves = "";
    string line;
    int ri = -1, rj = -1;
    int row = 0;
    while (getline(file, line) && !line.empty()) {
        m.push_back(line);
        if (ri == -1) {
            int idx = line.find('@');
            if (idx != string::npos) {
                ri = row;
                rj = idx;
            }
        }
        row++;
    }
    while (getline(file, line)) {
        moves += line;
    }

    for (char dir : moves) {
        int ni = ri + dirs[dir].first, nj = rj + dirs[dir].second;
        if (m[ni][nj] == 'O') {
            move(m, ni, nj, dir);
        }
        if (move(m, ri, rj, dir)) {
            ri = ni;
            rj = nj;
        }
    }

    int sum = 0;
    for (int i = 0;i < m.size();i++) {
        for (int j = 0;j < m[i].size();j++) {
            if (m[i][j] == 'O') {
                sum += 100 * i + j;
            }
        }
    }
    cout << sum << endl;
    
    return 0;
}
