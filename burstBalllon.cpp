#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
#include <climits>
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
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vpii = vector<pair<int, int>>;

#define pb push_back
#define eb emplace_back
#define f first
#define s second
#define left(x) 2 * (x) + 1
#define right(x) 2 * (x) + 2
#define all(x) (x).begin(), (x).end()
#define rev_all(x) (x).rbegin(), (x).rend()
#define rep(i, n) for (int i = 0; i < (n); i++)

void solve()
{
}

int32_t main()
{
    ios_base::sync_with_stdio(NULL);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}

using ll = long long;
class Solution
{
public:
    int maxCoins(vector<int> &v1)
    {
        int n = v1.size();
        v1.push_back(1);
        v1.insert(v1.begin(), 1);
        vector<ll> v(v1.begin(), v1.end());
        vector<vector<ll>> dp(n + 2, vector<ll>(n + 2, 0));

        for (int i = n; i >= 1; i--)
        {
            for (int j = 1; j <= n; j++)
            {
                ll maxi = INT_MIN;
                if (i > j)
                    continue;
                for (int k = i; k <= j; k++)
                {
                    ll cost = v[i - 1] * v[k] * v[j + 1] + dp[i][k - 1] + dp[k + 1][j];
                    maxi = max(maxi, cost);
                }
                dp[i][j] = maxi;
            }
        }
        return dp[1][n];
    }
};