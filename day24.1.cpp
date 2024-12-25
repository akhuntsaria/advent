#include "util.cpp"

struct wire {
    string name;
    int val = -1; // -1 = it should be calculated
    string w1;
    string op;
    string w2;
};

int val(map<string,wire>& m, wire& w) {
    if (w.val != -1) return w.val;
    int operand1 = val(m, m[w.w1]),
        operand2 = val(m, m[w.w2]);
    if (w.op == "AND") {
        return operand1 & operand2;
    } else if (w.op == "OR") {
        return operand1 | operand2;
    } else {// XOR
        return operand1 ^ operand2;
    }
}

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    map<string,wire> m;
    string line;
    while (getline(file, line)) {
        if (line.empty()) break;

        int sep = line.find(": ");
        string name = line.substr(0, sep);
        int val = line[sep+2] - '0';
        wire w = {name, val, "", "", ""};
        m.insert({name, w});
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string w1, op, w2, name, trash;
        ss >> w1 >> op >> w2 >> trash >> name;
        wire w = {name, -1, w1, op, w2};
        m.insert({name, w});
    }

    string bin;
    for (auto& [name, w] : m) {
        if (name[0] != 'z') continue;
        bin = (char)(val(m, w) + '0') + bin;
    }

    cout << stoull(bin, nullptr, 2) << endl;

    return 0;
}
