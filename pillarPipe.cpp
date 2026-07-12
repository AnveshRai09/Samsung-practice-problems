#include <iostream>
#include <vector>
#include <map>
#include <set>
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
int tallestBillboard(vector<int> &rods)
{
    int n = rods.size();
    ll sum = accumulate(rods.begin(), rods.end(), 0);
    vector<ll> dp(sum + 1, -1);
    // dp[diff] = max len of shorter pole if diff is the difference between the taller and shorter pole
    dp[0] = 0;
    for (auto h : rods)
    {
        vector<ll> tempDp = dp;
        for (int diff = 0; diff <= sum; diff++)
        {
            if (tempDp[diff] == -1)
                continue;

            // if we add h to taller pole
            if (diff + h < sum)
                dp[diff + h] = max(dp[diff + h], tempDp[diff]);

            // if we add h to smaller pole
            // case 1 : h < diff then len of smaller pole becomes dp[diff]+h
            // case 2 : h > diff them smaller becomes the taller pole and len of smaller pole will be dp[diff]+d
            // basically len of smaller pole will be dp[diff] + min(diff ,h)
            ll newDiff = abs(h - diff);
            dp[newDiff] = max(dp[newDiff], tempDp[diff] + min(diff, h));
        }
    }
    return dp[0] == -1 ? 0 : dp[0];
}