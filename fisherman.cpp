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

int N;
int minCost;
struct gate
{
    int pos, men;
};
vector<gate> G;
vector<bool> vis;
vector<int> order;

void solve(int gate, int menLeft, int cost, int orderId)
{

    if (menLeft == 0)
    {
        if (orderId + 1 < 3)
        {
            int nextGate = order[orderId + 1];
            solve(nextGate, G[nextGate].men, cost, orderId + 1);
        }
        else
        {
            minCost = min(minCost, cost);
        }
        return;
    }

    for (int i = 1; i <= N; i++)
    {
        if (!vis[i])
        {
            vis[i] = true;
            int c = abs(i - G[gate].pos) + 1;
            if (cost + c < minCost)
            {
                solve(gate, menLeft - 1, cost + c, orderId);
            }
            vis[i] = false;
        }
    }
}

int main()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    cin >> N;
    G.resize(3);
    minCost = INT_MAX;
    for (int i = 0; i < 3; i++)
        cin >> G[i].pos;
    for (int i = 0; i < 3; i++)
        cin >> G[i].men;
    vis.resize(N + 1, false);
    order = {0, 1, 2};

    do
    {
        solve(order[0], G[order[0]].men, 0, 0);
    } while (next_permutation(order.begin(), order.end()));
    cout << minCost;
    return 0;
}
