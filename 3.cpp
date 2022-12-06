#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
using namespace std;

enum class Outcomes {
    LOST = 0,
    DRAW = 3,
    WON = 6
};

int main() {


    string in;
    int rolling_sum = 0;
    int count = 0;
    unordered_map<char, int> items;
    while (getline(cin, in)) {       
        if (in == "-1") break;
        count++;

        unordered_set<char> elf;
        int n = in.size();
        for (int i = 0; i < n; ++i) {
            elf.insert(in[i]);
            // items[in[i]]++;
        }

        for (const auto& c : elf) {
            items[c]++;
        }

        if (count == 3) {
            count = 0;
            for (const auto& [key, val] : items) {
                if (val == 3) {
                    rolling_sum += key >= 'a' ? int(key - 'a') + 1 : int(key - 'A' + 27); 
                    // cout << key << endl;   
                    break;
                }
            }
            items.clear();
        }
    }

    cout << rolling_sum;
    
    return 0;
}