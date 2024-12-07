#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

typedef unsigned long long u64;

bool valid(u64 targ_sum, const vector<u64>& operands, u64 curr_sum, int i) {
    if (i == operands.size()) {
        return curr_sum == targ_sum;
    }
    if (curr_sum > targ_sum) return false;
    return valid(targ_sum, operands, curr_sum + operands[i], i + 1) ||
           valid(targ_sum, operands, curr_sum * operands[i], i + 1);
}

u64 process_line(const string& line) {
    istringstream iss(line);
    u64 sum;
    char colon;
    iss >> sum >> colon; 

    vector<u64> operands;
    string operand;
    while (iss >> operand) {
        if (!operand.empty()) {
            operands.push_back(stoll(operand));
        }
    }
    
    return valid(sum, operands, operands[0], 1) ? sum : 0;
}

int main() {
    ifstream file("input7.2.txt");
    if (!file.is_open()) {
        cerr << "Could not open file" << endl;
        return 1;
    }
    
    auto total = 0l;
    string line;
    while (getline(file, line)) {
        total += process_line(line);
    }
    cout << total << endl;
    return 0;
}
