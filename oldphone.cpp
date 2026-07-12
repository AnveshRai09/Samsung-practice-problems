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
void genNum(const vector<int> &num, int o, unordered_map<ll, int> &mp, string curr)
{
    if (!curr.empty())
    {
        ll val = stoll(curr);
        if (val > 10000)
            return;
        int touch = curr.length();
        if (mp.find(val) == mp.end() || touch < mp[val])
        {
            mp[val] = touch;
        }
    }
    if (curr.length() >= o)
        return;

    for (auto it : num)
    {
        if (curr == "0")
            continue;

        genNum(num, o, mp, curr + to_string(it));
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {

        int n, m, o;
        cin >> n >> m >> o;
        vector<int> dials(n);
        vector<int> op(m);
        for (int i = 0; i < n; i++)
            cin >> dials[i];
        for (int i = 0; i < m; i++)
            cin >> op[i];

        ll tar;
        cin >> tar;

        priority_queue<pair<int, ll>, vector<pair<int, ll>>, greater<pair<int, ll>>> pq;
        unordered_map<ll, int> mp;
        for (int i = 0; i < n; i++)
        {
            mp[dials[i]] = 1;
        }
        genNum(dials, o, mp, "");
        if (mp.find(tar) != mp.end())
        {
            cout << mp[tar] << endl;
            continue;
        }
        unordered_map<ll, int> vis;
        for (auto it : mp)
        {
            pq.push({it.second, it.first});
            vis[it.first] = it.second;
        }
        ll ans = -1;
        while (!pq.empty())
        {
            ll curr = pq.top().second;
            int steps = pq.top().first;
            pq.pop();
            if (steps > o)
                continue;
            if (curr == tar)
            {
                ans = steps + 1;
                break;
            }
            ll next;

            for (auto it : mp)
            {
                int next_steps = steps + 1 + it.second;

                // If touches + 1 (for the '=' sign) exceeds limit, skip it completely!
                if (next_steps >= o)
                {
                    continue;
                }
                for (int j = 0; j < m; j++)
                {
                    bool valid = false;
                    if (op[j] == 1)
                    {
                        next = curr + it.first;
                        valid = true;
                    }
                    if (op[j] == 2)
                    {
                        next = curr - it.first;
                        valid = true;
                    }
                    if (op[j] == 3)
                    {
                        next = curr * it.first;
                        valid = true;
                    }
                    if (op[j] == 4)
                    {
                        if (it.first == 0 || curr % it.first != 0)
                        {
                            valid = false;
                            continue;
                        }
                        next = curr / it.first;
                        valid = true;
                    }
                    if (valid && (vis.find(next) == vis.end() || vis[next] > steps + 1 + it.second))
                    {
                        pq.push({steps + 1 + it.second, next});
                        vis[next] = steps + 1 + it.second;
                    }
                }
            }
        }
        cout << ans << endl;
    }
}