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

int combo(int operand, int a, int b, int c) {
    if (operand == 4) return a;
    if (operand == 5) return b;
    if (operand == 6) return c;
    return operand;
}

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    int a, b, c;
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

    string out = "";

    for (int ptr = 0;ptr < prog.size() - 1;) {
        int opcode = prog[ptr],
            operand = prog[ptr+1];
        if (opcode == 0) {
            int res = a / (int)pow(2, combo(operand, a, b, c));
            a = res;
            ptr += 2;
        } else if (opcode == 1) {
            int res = b ^ operand;
            b = res;
            ptr += 2;
        } else if (opcode == 2) {
            int res = combo(operand, a, b, c) % 8;
            b = res;
            ptr += 2;
        } else if (opcode == 3) {
            if (a != 0) {
                ptr = operand;
            } else {
                ptr += 2;
            }
        } else if (opcode == 4) {
            b ^= c;
            ptr += 2;
        } else if (opcode == 5) {
            out += to_string(combo(operand, a, b, c) % 8);
            out += ',';
            ptr += 2;
        } else if (opcode == 6) {
            b = a / (int)pow(2, combo(operand, a, b, c));
            ptr += 2;
        } else { // 7
            c = a / (int)pow(2, combo(operand, a, b, c));
            ptr += 2;
        }
    }
    cout << out << endl;
    return 0;
}
/*
a: 2024
prog: 0,1,5,4,3,0
out: 4,2,5,6,7,7,7,7,3,1,0

 0 1
 2024 / 2^1
 a: 1012

 5 4
 1012 % 8
 4

 out: 4

 3 0
 ptr = 0

 0 1
 1012 / 2
 506

 5 4
 506 % 8
 2

 506 / 2 = 253
*/