#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

struct P {
    ll x, y;
    P operator - (const P & o) const { return { x - o.x, y - o.y }; } 
    ll cross (const P & o) const { return x * o.y - y * o.x; }
    ll sqDist(const P & o) const { return (o.x - x) * (o.x - x) + (o.y - y) * (o.y - y); }
};

// FIX 1 & 3: Added 'const P &' to allow lambda usage and corrected vector orientation math
ll orientation(const P & a, const P & b, const P & c) {
    return (b - a).cross(c - a);
}

vector<P> GSpotFinder(vector<P> & v) {
    if (v.size() <= 3) return v;
    
    auto p = min_element(v.begin(), v.end(), [](const P &a, const P &b) {
        if (a.y == b.y) {
            return a.x < b.x;
        }
        return a.y < b.y; // Standard Graham Scan picks bottom-left
    });
    swap(v[0], *p);
    
    sort(v.begin() + 1, v.end(), [&](const P & a, const P & b) {
        ll o = orientation(v[0], a, b);
        if (o != 0) {
            return o > 0; // Sort by counter-clockwise order
        }
        return v[0].sqDist(a) < v[0].sqDist(b);
    }); // FIX 2: Added missing closing semicolon here

    vector<P> hull;
    for (int i = 0; i < v.size(); i++) {
        // Pop last element if the sequence makes a non-left (clockwise or straight) turn
        while (hull.size() > 1 && orientation(hull[hull.size() - 2], hull.back(), v[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(v[i]);
    }
    
    return hull;
}
