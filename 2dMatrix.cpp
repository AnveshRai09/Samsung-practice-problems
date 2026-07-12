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

void solve() {}

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
using pill = pair<int, long long>;
const ll M = 1e9 + 7;
inline pill &operator+=(pill &a, const pill &b)
{
    a.first += b.first;
    a.second = (a.second % M + b.second % M) % M;
    return a;
}
class Solution
{
public:
    // inline pill operator + (const pill )

    pill max(vector<pill> &v)
    {
        sort(v.begin(), v.end(), [](const pill &a, const pill &b)
             {
            if (a.first == b.first) {
                return a.second < b.second ;
            }
            return a.first < b.first ; });
        int n = v.size();
        ll paths = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            if (v[i].first == v[n - 1].first)
            {
                paths += v[i].second;
            }
            else
                break;
        }
        return {v[n - 1].first, paths};
    }
    vector<int> pathsWithMaxScore(vector<string> &board)
    {
        int n = board.size();
        board[0][0] = '0';
        board[n - 1][n - 1] = '0';
        vector<vector<pill>> dp(n, vector<pill>(n));
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = n - 1; j >= 0; j--)
            {
                dp[i][j] = {(board[i][j] == 'X' ? -(1e9) : board[i][j] - '0'), 0};
                // cout << /*i << "," << j << " :*/" {" << dp[i][j].first << "," << dp[i][j].second << "} | ";
            }
            dp[n - 1][n - 1].second = 1;
            // cout << endl;
        }
        cout << "after" << endl;
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = n - 1; j >= 0; j--)
            {
                vector<pill> options = {
                    ((i < n - 1) ? dp[i + 1][j] : pill{0, 0LL}),
                    ((j < n - 1) ? dp[i][j + 1] : pill{0, 0LL}),
                    (((i < n - 1) * (j < n - 1)) ? dp[i + 1][j + 1] : pill{0, 0LL}),
                };
                if (board[i][j] != 'X')
                    dp[i][j] += max(options);

                // cout << /*i << "," << j << " :*/" {" << dp[i][j].first << "," << dp[i][j].second << "} | ";
            }
            // cout << endl;
        }
        return {(int)(dp[0][0].second != 0) * dp[0][0].first, (int)dp[0][0].second};
    }
};
