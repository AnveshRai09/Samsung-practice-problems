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

#define int long long

const int INF = 1e15; // Safe infinity that won't overflow long long

int rec(int i, int k, int parent, vector<int> &v)
{
    int n = v.size(); // Fixed: Added 'int'
    if (k <= 0)
        return 0; // Satisfied our k requirement
    if (i >= n)
        return INF; // Reached end but k > 0, return safe infinity
    // If we take, subtract the parent to avoid double-charging the gap
    int take = rec(i + 1, k - 1, v[i], v) + (n - i) * (v[i] - parent);
    int notTake = rec(i + 1, k, parent, v);

    return min(notTake, take);
}

int32_t main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    int k;
    cin >> k;

    sort(a.begin(), a.end());

    // Call with parent initially at 0
    cout << rec(0, k, 0, a) << "\n";
    return 0;
}