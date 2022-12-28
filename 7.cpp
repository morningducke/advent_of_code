#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{

    vector<string> path;
    map<vector<string>, int> dirs;
    string in;
    while (getline(cin, in))
    {
        if (in == "-1")
            break;

        istringstream is(in);
        vector<string> line(2, "");
        is >> line[0] >> line[1];
        if (line[0] == "$")
        {
            
            if (line[1] == "cd")
            {    
                is >> line[1];
                if (line[1] == "..") {
                    path.pop_back();    
                } else {
                    path.push_back(line[1]);
                }
                
            } 
        }
        else if (line[0] != "dir")
        {
            vector<string> aux = path;
            while (!aux.empty()) {
                dirs[aux] += stoi(line[0]);
                aux.pop_back();
            }
            
        }
    }


    int size = 0, total_space = 7e7, req_space = 3e7;
    for (const auto& [key, val] : dirs) {
        if (val <= 1e5) size += val;
    }
    cout << size << "\n";

    int to_delete = req_space - (total_space - dirs[{"/"}]);
    
    if (to_delete <= 0) {
        size = 0;
    } 
    else {
        int min_size = dirs[{"/"}];
        for (const auto& d : dirs) {
            min_size = d.second >= to_delete ? min(min_size, d.second) : min_size;
        }
        size = min_size;
    }

    cout << size << "\n";

    return 0;
}