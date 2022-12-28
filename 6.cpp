#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

bool check_marker(string& window, unordered_map<char, int>& freq) {    
    for (const auto& c : window) {
        auto it = freq.find(c);
        if (it != freq.end() && it->second > 1) return false;
    }
    return true;
}

int main() {

    string in;
    int marker = 0;
    int sw_size = 14;
    while (getline(cin, in)) {       
        if (in[1] == '1' || in.size() < sw_size) break;

        unordered_map<char, int> freq;
        //init sliding window
        string window = in.substr(0, 4);
        for (int i = 0; i < sw_size; ++i) {
               freq[in[i]]++;               
        }
        if (check_marker(window, freq)) {
            marker = sw_size + 1;
            break;
        }

        for (int i = sw_size; i < in.size(); ++i) {
            
            freq[in[i - sw_size]]--;
            freq[in[i]]++;
            window = in.substr(i - (sw_size - 1), sw_size);
            if (check_marker(window, freq)) {
                marker = i + 1;
                break;
            }

        }    
        
    }
    
    cout << marker;
    return 0;
}