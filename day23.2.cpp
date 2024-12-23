#include "util.cpp"

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    map<string,set<string>> adj;
    string line;
    while (getline(file, line)) {
        int sep = line.find('-');
        string a = line.substr(0, sep),
            b = line.substr(sep+1);
        adj[a].insert(b);
        adj[b].insert(a);
    }

    unordered_set<vector<string>,vector_hash> groups;
    size_t res = 1;
    for (auto& [c,ns] : adj) {
        groups.insert({c});
        unordered_set<vector<string>,vector_hash> new_groups;
        for (vector<string> group : groups) {
            bool connected = true;
            for (string group_v : group) {
                if (!adj[c].contains(group_v)) {
                    connected = false;
                    break;
                }
            }
            if (connected) {
                group.push_back(c);
                sort(group.begin(), group.end());
                new_groups.insert(group);
                
                if (group.size() > res) {
                    print(group);
                    res = group.size();
                }
            }
        }
        groups.insert(new_groups.begin(), new_groups.end());
    }

    return 0;
}
/*

a -> b c d e
b -> a e
c -> a d

groups:
a b e

Tried:
13

ar cd hl iw jm ku qo rz vo xe xm xv ys
*/