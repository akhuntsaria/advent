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
    for (int i = 0,id = 0; i < map.length(); i++) {
        int n = map[i] - '0';
        
        if (i % 2 == 0) {
            for (int j = 0; j < n; j++) {
                expanded.push_back(id);
            }
            id++;
        } else {
            for (int j = 0; j < n; j++) {
                expanded.push_back(-1); // .
            }
        }
    }
    
    int l = 0, r = expanded.size() - 1;
    while (l < r) {
        if (expanded[l] != -1) {
            l++;
            continue;
        }
        if (expanded[r] == -1) {
            r--;
            continue;
        }

        expanded[l] = expanded[r];
        expanded[r] = -1;
        l++;
        r--;
    }
    
    u64 sum = 0;
    for (int i = 0; i < expanded.size(); i++) {
        if (expanded[i] == -1) break;
        sum += i * expanded[i];
    }
    cout << sum << endl;
    
    return 0;
}
/*
5534919759
89425419840
5646753349

id 10
count 5
all options
00000
10101
1010101010

6307275788409
 */
