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

int main()
{
    int n;
    cin >> n;
    vector<int> v(n + 2);
    v[0] = 1;
    v[n + 1] = 1;
    for (int i = 0; i < n; i++)
        cin >> v[i + 1];
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

    for (int i = n; i >= 1; i--)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i > j)
                continue;
            int maxi = INT_MIN;
            for (int k = i; k <= j; k++)
            {
                if (i == 1 && j == n)
                    dp[i][j] = max(dp[i][j], v[k] + dp[i][k - 1] + dp[k + 1][j]);
                else
                {
                    int cost = v[i - 1] * v[j + 1] + dp[i][k - 1] + dp[k + 1][j];
                    maxi = max(maxi, cost);
                    dp[i][j] = maxi;
                }
            }
        }
    }
    cout << dp[1][n];
    return 0;
}
