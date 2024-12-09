#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef long long u64;

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    string map;
    getline(file, map);

    vector<int> expanded;
    vector<pair<int,int>> files; // id -> start idx and len
    int id = -1;
    for (int i = 0; i < map.length(); i++) {
        int n = map[i] - '0';
        
        if (i % 2 == 0) {
            id++;
            files.push_back({expanded.size(), n});
            for (int j = 0; j < n; j++) {
                expanded.push_back(id);
            }
        } else {
            for (int j = 0; j < n; j++) {
                expanded.push_back(-1); // .
            }
        }
    }
    
    int l_start = 0;
    for (;id >= 0; id--) {
        int to_move = files[id].second, r = files[id].first;

        bool first_dot = true;
        for (int l = l_start; l < r;) {
            if (expanded[l] != -1) {
                l++;
                continue;
            }

            if (first_dot) {
                l_start = l;
                first_dot = false;
            }
            
            int to_fill = 0;
            for (int i = l; i < r && expanded[i] == -1; i++, to_fill++);
            
            if (to_move <= to_fill) {
                for (int i = 0; i < to_move; i++) {
                    expanded[l] = expanded[r];
                    expanded[r] = -1;
                    l++;
                    r++;
                }
                break;
            }
            
            l += to_fill;
        }
    }

    u64 sum = 0;
    for (int i = 0; i < expanded.size(); i++) {
        if (expanded[i] == -1) continue;
        sum += i * expanded[i];
    }
    cout << sum << endl;
    
    return 0;
}
/*

 */
