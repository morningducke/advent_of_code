#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;


vector<deque<char>> parse_structure(string& structure, int col_size) {
    vector<deque<char>> stacks(col_size, deque<char>());
    istringstream is(structure);
    string in;
    while (getline(is, in, '\n')) {
        if (in[1] == '1') break;
        for (int i = 1; i < in.size(); i += 4) {
            if (in[i] != ' ') stacks[(i / 4)].push_front(in[i]);
        }
    }

    return stacks;
}

void print_structure(vector<deque<char>>& stacks) {
        for (const auto& st : stacks) {
        for (const auto& i : st) {
            cout << i;
        }
        cout << '\n';
    }
}
int main() {

    vector<deque<char>> stacks;
    string in;
    string structure = "";
    int col_size = 0;
    
    while (getline(cin, in)) {       
        if (in[1] == '1') break;
        

        istringstream is(in);
        structure.append(in + "\n");
        
    }
    col_size = (in.size() + 1) / 4; 
    stacks = parse_structure(structure, col_size);
    
  //  print_structure(stacks);

    while (getline(cin, in)) {
        if (in.empty()) continue;
        if (in == "-1") break;

        istringstream is(in);
        string s;
        vector<int> command(3, 0);
        int j = 0;
        while(getline(is, s, ' ')) {
            if (s[0] < '0' || s[0] > '9') continue;
            command[j++] = stoi(s);

        }
        deque<char> crates;
        for (int i = 0; i < command[0]; ++i) {
            char tmp = stacks[command[1] - 1].back();
            stacks[command[1] - 1].pop_back();
            crates.push_front(tmp);
            
            
        }
        for (const auto& i : crates) {
            stacks[command[2] - 1].push_back(i);
        }
      
        
    }
    
    
    for (int i = 0; i < stacks.size(); ++i) {
        cout << stacks[i].back();
    }
    return 0;
}