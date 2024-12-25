#include "util.cpp"

u64 combo(int operand, u64 a, u64 b, u64 c) {
    if (operand == 4) return a;
    if (operand == 5) return b;
    if (operand == 6) return c;
    return operand;
}

vector<int> run(vector<int>& prog, u64 a) {
    vector<int> out;
    u64 b = 0, c = 0;
    for (int ptr = 0;ptr < prog.size() - 1;) {
        int opcode = prog[ptr],
            operand = prog[ptr+1];
        if (opcode == 0) {
            a /= 1 << combo(operand, a, b, c);
        } else if (opcode == 1) {
            b ^= operand;
        } else if (opcode == 2) {
            b = combo(operand, a, b, c) % 8;
        } else if (opcode == 3) {
            if (a != 0) {
                ptr = operand;
                continue;
            }
        } else if (opcode == 4) {
            b ^= c;
        } else if (opcode == 5) {
            out.push_back(combo(operand, a, b, c) % 8);
        } else if (opcode == 6) {
            b = a / (1 << combo(operand, a, b, c));
        } else { // 7
            c = a / (1 << combo(operand, a, b, c));
        }
        ptr += 2;
    }
    return out;
}

u64 find_a(vector<int>& prog, u64 end_i, u64 a) {
    for (int i = 0;i < 8;i++) {
        u64 a1 = a*8 + i;
        vector<int> out = run(prog, a1);
        bool eq = true;
        for (int j = 0;j <= end_i;j++) {
            if (prog[prog.size()-j-1] != out[out.size()-j-1]) {
                eq = false;
                break;
            }
        }
        if (eq) {
            if (end_i == prog.size() - 1) return a1;
            a1 = find_a(prog, end_i + 1, a1);
            if (a1 != 0) return a1;
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    u64 a, b, c;
    vector<int> prog;
    string line;
    getline(file, line);
    char discard;
    stringstream ss(line);
    do {
        ss >> discard;
    } while (discard != ':');
    ss >> a;

    getline(file, line);
    ss = stringstream(line);
    do {
        ss >> discard;
    } while (discard != ':');
    ss >> b;

    getline(file, line);
    ss = stringstream(line);
    do {
        ss >> discard;
    } while (discard != ':');
    ss >> c;

    getline(file, line);
    getline(file, line);
    ss = stringstream(line);
    do {
        ss >> discard;
    } while (discard != ':');
    int n;
    while (ss >> n) {
        prog.push_back(n);
        ss >> discard;
    }

    cout << find_a(prog, 0, 0) << endl;    
    return 0;
}
