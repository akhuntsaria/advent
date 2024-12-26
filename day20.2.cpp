#include "util.cpp"

vector<vector<int>> dirs = {{-1,0},{0,1},{1,0},{0,-1}};

bool valid(vector<string>& m, int i, int j) {
    return i >= 0 && j >= 0 && i < m.size() && j < m[i].size() && m[i][j] != '#';
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
    unordered_map<pair<int,int>,int,pair_hash> dists;

    queue<vector<int>> q;
    q.push({si,sj,1});

    while (!q.empty()) {
        auto curr = q.front();
        q.pop();

        int i = curr[0], j = curr[1], step = curr[2];

        if (dists.contains({i,j}) && dists[{i,j}] < step) continue;
        dists[{i,j}] = step;

        for (auto& dir : dirs) {
            int ni = i+dir[0], nj = j+dir[1];
            if (valid(m, ni, nj)) {
                q.push({ni, nj, step+1});
            }
        }
    }
    int res = 0;
    for (auto it1 = dists.begin(); it1 != dists.end(); it1++) {
        for (auto it2 = std::next(it1); it2 != dists.end(); it2++) {
            auto& [p1, dist1] = *it1;
            auto& [p2, dist2] = *it2;

            int direct_dist = abs(p1.first - p2.first) + abs(p1.second - p2.second);
            if (direct_dist > 20) continue;

            int actual_dist = abs(dist1 - dist2),
                save = actual_dist - direct_dist;
            res += save >= 100;            
        }
    }
    cout << res << endl;
    return 0;
}
