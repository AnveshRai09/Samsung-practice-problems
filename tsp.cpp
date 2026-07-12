#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <climits>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
#include <cmath>
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

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> dist(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            cin >> dist[i][j];
        }
    vector<vector<int>> dp((1 << n) + 1, vector<int>(n + 1, 1e9));
    dp[1][0] = 0; // starting from 0
    for (int mask = 1; mask < (1 << n); mask++)
    {
        for (int u = 0; u < n; u++)
        {
            if (!(mask & (1 << u)))
                continue;

            for (int v = 0; v < n; v++)
            {
                if (u != v && (mask & (1 << v)))
                {
                    int prev = mask ^ (1 << u);
                    dp[mask][u] = min(dp[mask][u], dp[prev][v] + dist[v][u]);
                }
            }
        }
    }

    int ans = INT_MAX;
    int allVis = (1 << n) - 1;
    for (int i = 1; i < n; i++)
    {
        ans = min(ans, dp[allVis][i] + dist[i][0]);
    }

    cout << ans << endl;
}

int main()
{
    int t;
    if (cin >> t)
    {
        while (t--)
        {
            solve();
        }
    }
    else
        solve();
    return 0;
}
