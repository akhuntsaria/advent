#include <cmath>
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

bool back(string& want, unordered_set<string>& avail, unordered_set<int>& v, int i) {
    if (v.contains(i)) return false;
    v.insert(i);
    if (i == want.size()) return true;
    for (int len = 1;len <= want.size() - i;len++) {
        string part = want.substr(i, len);
        if (!avail.contains(part)) continue;
        if (back(want, avail, v, i + len)) return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    unordered_set<string> avail;

    string line;
    getline(file, line);
    for (int i = 0;i < line.size();) {
        int next = line.find(", ", i);
        string design = line.substr(i, next-i);
        avail.insert(design);

        if (next == string::npos) break;
        i = next + 2;
    }

    int res = 0;
    getline(file, line); // Empty line
    while (getline(file, line)) {
        unordered_set<int> v;
        res += back(line, avail, v, 0);
    }
    cout << res << endl;
    
    return 0;
}
/*

*/