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
    for (auto& [v, neighbors] : adj) {
        if (v[0] != 't') continue;

        for (auto it1 = neighbors.begin(); it1 != neighbors.end(); it1++) {
            for (auto it2 = next(it1); it2 != neighbors.end(); it2++) {
                if (adj[*it1].contains(*it2)) {
                    vector<string> group_key = {v, *it1, *it2};
                    sort(group_key.begin(), group_key.end());
                    groups.insert(group_key);
                }
            }
        }
    }
    print(groups.size());

    return 0;
}
/*

*/