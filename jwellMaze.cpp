#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>
#include <cstring>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template <class T>
using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vpii = vector<pair<int, int>>;

#include <iostream>
#include <vector>

using namespace std;

int N;
vector<vector<int>> grid;
vector<vector<bool>> visited;
vector<pair<int, int>> best_path;
int max_jewels;

// Direction vectors for moving Up, Down, Left, Right
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

void dfs(int r, int c, int current_jewels, vector<pair<int, int>> &current_path)
{
    // If we reached the exit (bottom-right)
    if (r == N - 1 && c == N - 1)
    {
        if (current_jewels > max_jewels)
        {
            max_jewels = current_jewels;
            best_path = current_path;
        }
        return;
    }

    // Explore neighbors
    for (int i = 0; i < 4; ++i)
    {
        int nr = r + dr[i];
        int nc = c + dc[i];

        // Check bounds and if the cell is a passage/jewel and not visited
        if (nr >= 0 && nr < N && nc >= 0 && nc < N)
        {
            if (grid[nr][nc] != 1 && !visited[nr][nc])
            {

                visited[nr][nc] = true;
                current_path.push_back({nr, nc});

                int jewel_found = (grid[nr][nc] == 2) ? 1 : 0;

                dfs(nr, nc, current_jewels + jewel_found, current_path);

                // Backtrack
                current_path.pop_back();
                visited[nr][nc] = false;
            }
        }
    }
}

void solve()
{
    cin >> N;
    grid.assign(N, vector<int>(N));
    visited.assign(N, vector<bool>(N, false));
    best_path.clear();
    max_jewels = -1;

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cin >> grid[i][j];
        }
    }

    // Start DFS from entrance (0, 0)
    vector<pair<int, int>> start_path;
    start_path.push_back({0, 0});
    visited[0][0] = true;
    int start_jewel = (grid[0][0] == 2) ? 1 : 0;

    dfs(0, 0, start_jewel, start_path);

    // Mark the optimal path with 3
    // We create a copy of the grid to modify for output
    vector<vector<int>> output_grid = grid;
    for (auto const &coord : best_path)
    {
        output_grid[coord.first][coord.second] = 3;
    }

    // Print the marked maze grid
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cout << output_grid[i][j] << " ";
        }
        cout << "\n";
    }
    // Print the maximum number of jewels picked up
    cout << max_jewels << "\n\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T)
    {
        while (T--)
        {
            solve();
        }
    }
    return 0;
}