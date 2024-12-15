#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct pair_hash {
    inline size_t operator()(const pair<int,int>& v) const {
        return v.first * 31 + v.second;
    }
};

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    int n = 101,m = 103;
    vector<pair<int,int>> pos, vel;
    string line;
    unordered_set<pair<int,int>,pair_hash> s;
    while (getline(file, line)) {
        char discard;

        stringstream ss(line);
        do {
            ss >> discard;
        } while (discard != '=');
        int x, y, vx, vy;
        ss >> x >> discard >> y;

        do {
            ss >> discard;
        } while (discard != '=');
        ss >> vx >> discard >> vy;

        pos.push_back({x, y});
        vel.push_back({vx, vy});
        s.insert({x, y});
    }

    for (int t = 1;t <= 10000;t++) {
        for (int i = 0;i < pos.size();i++) {
            s.erase(pos[i]);
            pos[i].first += vel[i].first;
            pos[i].second += vel[i].second;

            if (pos[i].first < 0) {
                pos[i].first = n + pos[i].first;
            }
            if (pos[i].second < 0) {
                pos[i].second = m + pos[i].second;
            }
            if (pos[i].first >= n) {
                pos[i].first = pos[i].first % n;
            }
            if (pos[i].second >= m) {
                pos[i].second = pos[i].second % m;
            }
            s.insert(pos[i]);
        }
        for (const auto& p : pos) {
            // Find a triangle
            if (s.contains({p.first+1,p.second-1})
                && s.contains({p.first+1,p.second})
                && s.contains({p.first+2,p.second-2})
                && s.contains({p.first+2,p.second-1})
                && s.contains({p.first+2,p.second})
                && s.contains({p.first+3,p.second})) {
                cout << t << endl;
                return 0;
            }
        }
        
    }

    return 0;
}
