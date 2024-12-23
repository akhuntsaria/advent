#include "util.cpp"

vector<vector<int>> dirs = {{-1,0},{0,1},{1,0},{0,-1}};

bool valid(vector<string>& map, int i, int j) {
    return i >= 0 && j >= 0 && i < map.size() && j < map[i].size() && map[i][j] != '#';
}

int dist(vector<string>& map, int si, int sj) {
    queue<vector<int>> q;
    q.push({si,sj,1});

    unordered_set<pair<int,int>,pair_hash> v;
    int dist = INT_MAX;

    while (!q.empty()) {
        auto curr = q.front();
        q.pop();

        int i = curr[0], j = curr[1], step = curr[2];

        if (v.contains({i,j})) continue;
        v.insert({i,j});

        if (map[i][j] == 'E') {
            dist = step;
            break;
        }

        for (auto& dir : dirs) {
            int ni = i+dir[0], nj = j+dir[1];
            if (valid(map, ni, nj)) {
                q.push({ni, nj, step+1});
            }
        }
    }
    return dist;
}

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    vector<string> m;
    string line;
    int si = -1, sj = -1, ej = -1, row = 0;
    while (getline(file, line)) {
        m.push_back(line);
        if (si == -1) {
            int col = line.find('S');
            if (col != string::npos) {
                si = row;
                sj = col;
            }
            row++;
        }
    }
    int regular_dist = dist(m, si, sj);
    int res = 0;
    for (int i = 0;i < m.size();i++) {
        for (int j = 0;j < m[i].size();j++) {
            if (m[i][j] != '#') continue;
            char prev = m[i][j];
            m[i][j] = prev == '#' ? 'X' : prev;
            if (regular_dist - dist(m, si, sj) >= 100) {
                res++;
            }
            m[i][j] = prev;
        }
    }
    cout << res << endl;
    return 0;
}
