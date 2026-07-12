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

vector<vector<vector<vector<int>>>> dp;
bool notValid(int i, int j, int n, int m)
{
    return !(i >= 0 && i <= n && j <= m && j >= 0);
}

int solve(int i, int j, int bomb, vector<vector<int>> &mat, int stepy, int n, int m)
{
    if (i < 0)
        return 0;
    if (notValid(i, j, n, m))
        return INT_MIN;
    int step_state = min(stepy, 6);
    if (dp[i][j][bomb][step_state] != -1)
        return dp[i][j][bomb][step_state];
    int bombed = 0;
    if (bomb)
    {
        bombed = solve(i, j, 0, mat, 0, n, m);
    }
    int left = INT_MIN;
    int right = INT_MIN;
    int center = INT_MIN;
    if (mat[i][j] == 2)
    {
        if (stepy <= 4)
        {
            left = solve(i - 1, j + 1, bomb, mat, stepy + 1, n, m);
            right = solve(i - 1, j - 1, bomb, mat, stepy + 1, n, m);
            center = solve(i - 1, j, bomb, mat, stepy + 1, n, m);
        }
        else
        {
            return INT_MIN;
        }
    }
    else
    {
        int val = mat[i][j];
        left = val + solve(i - 1, j + 1, bomb, mat, stepy + 1, n, m);
        right = val + solve(i - 1, j - 1, bomb, mat, stepy + 1, n, m);
        center = val + solve(i - 1, j, bomb, mat, stepy + 1, n, m);
    }
    return dp[i][j][bomb][step_state] = max({bombed, left, right, center});
}

int main()
{
    ll t;
    cin >> t;
    int test = 0;
    while (t--)
    {
        test++;
        int n, m;
        cin >> n;
        m = 5;
        vector<vector<int>> mat(n + 1, vector<int>(m + 1, 0));
        dp.assign(n + 2, vector<vector<vector<int>>>(m + 2, vector<vector<int>>(2, vector<int>(7, -1))));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin >> mat[i][j];
            }
        }
        mat.push_back({0, 0, 0, 0, 0});
        cout << "#" << test << " " << solve(n, 2, 1, mat, 6, n, m) << endl;
    }
}
