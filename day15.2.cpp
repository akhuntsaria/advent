#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

unordered_map<char, pair<int,int>> dirs = {{'^', {-1,0}},{'>', {0,1}},{'v', {1,0}},{'<', {0,-1}}};

// Only for up and down
bool can_move(vector<string>& m, int i, int j, char dir) {
    int ni = i + dirs[dir].first;
    if (m[ni][j] == '#' || m[ni][j+1] == '#') return false;
    if (m[ni][j] == ']' && !can_move(m, ni, j-1, dir)) {
        return false;
    }
    if (m[ni][j] == '[' && !can_move(m, ni, j, dir)) {
        return false;
    }
    if (m[ni][j+1] == '[' && !can_move(m, ni, j+1, dir)) {
        return false;
    }
    return true;
}

void move(vector<string>& m, int i, int j, char dir) {
    if (m[i][j] == ']') j--;
    else if (m[i][j] != '[') return;

    if (dir == '<') {
        if (m[i][j-1] == ']') {
            move(m, i, j-1, dir);
        }
        if (m[i][j-1] == '.') {
            m[i][j+1] = '.';
            m[i][j-1] = '[';
            m[i][j] = ']';
        }
    } else if (dir == '>') {
        if (m[i][j+2] == '[') {
            move(m, i, j+2, dir);
        }
        if (m[i][j+2] == '.') {
            m[i][j] = '.';
            m[i][j+1] = '[';
            m[i][j+2] = ']';
        }
    }
    
    if (dir == '^' || dir == 'v') {
        if (!can_move(m, i, j, dir)) return;
        int ni = i + dirs[dir].first;
        if (m[ni][j] == ']') {
            move(m, ni, j-1, dir);
        }
        if (m[ni][j] == '[') {
            move(m, ni, j, dir);
        }
        if (m[ni][j+1] == '[') {
            move(m, ni, j+1, dir);
        }
        if (m[ni][j] == '.' && m[ni][j+1] == '.') {
            m[i][j] = '.';
            m[i][j+1] = '.';
            m[ni][j] = '[';
            m[ni][j+1] = ']';
        }
    }
}

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    vector<string> m;
    string moves = "";
    string line;
    int ri = -1, rj = -1;
    int row = 0;
    while (getline(file, line) && !line.empty()) {
        string new_line = "";
        for (int i = 0;i < line.size();i++) {
            char c = line[i];
            if (line[i] == '#' || line[i] == '.') {
                new_line += line[i];
                new_line += line[i];
            } else if (line[i] == 'O') {
                new_line += "[]";
            } else if (line[i] == '@') {
                new_line += "@.";
                if (ri == -1) {
                    ri = row;
                    rj = new_line.size()-2;
                }
            }
        }
        m.push_back(new_line);
        if (ri == -1) row++;
    }
    while (getline(file, line)) {
        moves += line;
    }

    for (char dir : moves) {
        int ni = ri + dirs[dir].first, nj = rj + dirs[dir].second;
        move(m, ni, nj, dir);
        if (m[ni][nj] == '.') {
            m[ri][rj] = '.';
            m[ni][nj] = '@';
            ri = ni;
            rj = nj;
        }
    }

    int sum = 0;
    for (int i = 0;i < m.size();i++) {
        for (int j = 0;j < m[i].size();j++) {
            if (m[i][j] == '[') {
                sum += 100 * i + j;
            }
        }
    }
    cout << sum << endl;
    
    return 0;
}
