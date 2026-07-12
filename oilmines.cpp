#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <string>
#include <climits>
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

int solve(int i, int k, int min_e, int max_e, int end, int sum, vector<int> &v)
{
    if (k < 0)
        return INT_MAX;
    if (i == end)
    {
        if (k == 0)
        {
            // cout<<"hi"<<endl;
            return max(max_e, sum + v[i]) - min(min_e, sum + v[i]);
        }
        else
            return INT_MAX;
    }

    int cur_sum = sum + v[i];
    int next = i + 1;
    if (next == v.size())
        next = 0;
    int end_part = solve(next, k - 1, min(min_e, cur_sum), max(max_e, cur_sum), end, 0, v);
    int continue_part = solve(next, k, min_e, max_e, end, cur_sum, v);
    return min(end_part, continue_part);
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, k;
        cin >> k >> n;
        vector<int> v(n);
        for (int &i : v)
            cin >> i;
        int ans = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            int end = i - 1;
            if (i == 0)
                end = n - 1;
            int cur = solve(i, k - 1, INT_MAX, INT_MIN, end, 0, v);
            ans = min(ans, cur);
        }
        cout << ans << endl;
    }
}