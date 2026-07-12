#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

// dp[index][count][is_less][is_started]
long long dp[20][20][2][2];
string num_str;

// Helper to check if a digit is forbidden
bool isForbidden(int d)
{
    return (d == 1 || d == 3 || d == 5);
}

long long digitDP(int index, int count, bool is_less, bool is_started)
{
    // Base Case: If forbidden digits appear 3 or more times, it's invalid
    if (count >= 3)
        return 0;

    // Base Case: Reached the end of the digit string safely
    if (index == num_str.length())
    {
        return is_started ? 1 : 0; // Return 1 if it's a valid non-zero number
    }

    // Return memoized result if already calculated
    if (dp[index][count][is_less][is_started] != -1)
    {
        return dp[index][count][is_less][is_started];
    }

    long long ans = 0;
    int limit = is_less ? 9 : (num_str[index] - '0');

    for (int d = 0; d <= limit; d++)
    {
        bool next_started = is_started || (d > 0);

        // Calculate the next count condition
        int next_count = count;
        if (next_started && isForbidden(d))
        {
            next_count++;
        }

        bool next_less = is_less || (d < limit);

        ans += digitDP(index + 1, next_count, next_less, next_started);
    }

    return dp[index][count][is_less][is_started] = ans;
}

long long solve(long long n)
{
    if (n < 0)
        return 0;
    if (n == 0)
        return 1; // 0 is technically a valid product number if allowed by range

    num_str = to_string(n);
    memset(dp, -1, sizeof(dp));

    // Include 1 extra for '0' itself if needed, but our DP handles matches starting from 1
    return digitDP(0, 0, false, false);
}

int main()
{
    long long L = 24;
    long long R = 12943;

    // Total valid numbers in range [L, R]
    long long ans = solve(R) - solve(L - 1);

    cout << "Total valid product numbers in range [" << L << ", " << R << "]: " << ans << endl;

    return 0;
}