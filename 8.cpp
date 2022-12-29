#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// 1 - visible
// -1 - not visible
// 0 - not visited yet
bool dfs(vector<vector<int>>& graph, int i, int j, int i_prev, int j_prev, vector<vector<int>>& marked) {
    if (i < 0 || j < 0 || i >= graph.size() || j >= graph[0].size()) {
        return true;
    }
    if (marked[i][j] != 0) {
        return marked[i][j] == 1 ? true : false;    
    }
    if (i_prev != -1 && graph[i][j] <= graph[i_prev][j_prev]) {
        return false;
    }

    marked[i][j] = dfs(graph, i + 1, j, i, j, marked) || dfs(graph, i, j + 1, i, j, marked) ||
                   dfs(graph, i - 1, j, i, j, marked) || dfs(graph, i, j - 1, i, j, marked);

    return marked[i][j];
}
int main()  {

    
    vector<vector<int>> g;
    string in;
    int visible_count = 0, best_view = 0;
    while (getline(cin, in))
    {
        if (in == "-1")
            break;

        vector<int> row(in.size(), 0);
        for (int i = 0; i < in.size(); ++i) {
            row[i] = in[i];
        }
        g.push_back(row);

    }

    vector<vector<bool>> marked(g.size(), vector<bool>(g[0].size(), false));
    vector<int> col_maxes(g.size(), -1);
    vector<vector<int>> direction = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

// part 1
    for (int i = 0; i < g.size(); ++i) {
        for (int j = 0; j < g[0].size(); ++j) {
            if (i == 0 || j == 0 || i == g.size() - 1 || j == g[0].size() - 1) {
                marked[i][j] = true;
                visible_count++;
                continue;
            }
            
            for (const auto& d : direction) {
                int i_next = i + d[0];
                int j_next = j + d[1];
                bool is_visible = true;
                while (i_next >= 0 && i_next < g.size() && j_next >= 0 && j_next < g[0].size()) {
                    if (g[i][j] <= g[i_next][j_next]) {
                        is_visible = false;
                        break;
                    } 
                    i_next += d[0];
                    j_next += d[1];
                }
                marked[i][j] = marked[i][j] || is_visible;
                if (is_visible) break;
            }
            visible_count += marked[i][j];
        }
        
    }
// part2

    for (int i = 0; i < g.size(); ++i) {
        for (int j = 0; j < g[0].size(); ++j) {
            int total_view_dist = 1;
            if (i == 0 || j == 0 || i == g.size() - 1 || j == g[0].size() - 1) {
                continue;
            }
            for (const auto& d : direction) {
                int view_dist = 0;
                int i_next = i + d[0];
                int j_next = j + d[1];
                while (i_next >= 0 && i_next < g.size() && j_next >= 0 && j_next < g[0].size()) {
                    view_dist++;
                    if (g[i][j] <= g[i_next][j_next]) {
                        break;
                    } 
                    i_next += d[0];
                    j_next += d[1];
                }
                total_view_dist *= view_dist;
            }
            best_view = max(best_view, total_view_dist);
        }
        
    }

    cout << "Part 1: " << visible_count << "\n";
    cout << "Part 2: " << best_view << "\n";

    return 0;
}