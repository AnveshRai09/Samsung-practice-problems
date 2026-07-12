/*
You want to cut a piece of paper by a certain fixed rule to make some pieces of white or
blue colored square paper with various sizes.

If the size of the entire paper is N×N (N = 2^K; 1 <= K <= 7; K = natural number), the cutting rules
are as below.
‘If the entire piece of paper is not colored the same, cut the middle part horizontally and vertically
to divide it into the same sized four pieces of paper,
(N/2)×(N/2), as with I, II, III, IV in <FIG. 2>.

For each I, II, III and IV, cut and divide again in the same way if one entire piece of paper
is not colored the same, and make them into the same sized four pieces of paper. Continue until each and
every piece of paper has only one color of white or blue.’
When you finish, < FIG. 3 > shows the first division of < FIG. 1 > and < FIG. 4 >
shows the final version of 9 pieces of white paper and 7 pieces of blue paper of various sizes.
If the length of an edge of the first given piece of paper, N, and
the color information (white or blue) inside each square are given, create a calculation program
that assesses how many white/blue pieces of paper are.
Time limit: 1 second (java: 2 seconds)

[Input]
Input may include many test cases. The number of test cases, T, is given on the first line of input and then the amount of T of test cases is given in a line. (T <= 30)
The length of an edge of the first given piece of paper, N, is given for the first line of each test case.
From the next line through to the amount of N lines, the color information is given separately as blanks. 0 indicates white and 1 indicates blue.

[Output]
For each test case, you should print "Case #T" in the first line where T means the case number.
For each test case, you should output the number of white pieces of paper and blue pieces of paper separately as blanks on the first line of each test case.
*/

// optimized approach using prefix sum of matrix
// Using prefix sum, the number of blue cells (1s) inside any square can be found in O(1).
#include <iostream>
using namespace std;

const int maxm = 129;
int white = 0, blue = 0;
int arr[maxm][maxm] = {0};
void checkSame(int size, int si, int sj)
{
    if (size == 0)
        return;
    /*
    +--------+-----------+
    | DOUBLE | removed   |
    | REMOVED|   part    |
    +--------+-----------+
    | removed|  needed   |
    |  part  |   zone    |
    +--------+-----------+
    */
    int sum = arr[si + size - 1][sj + size - 1];
    if (si - 1 >= 0)
    {
        sum -= arr[si - 1][sj + size - 1];
    }
    if (sj - 1 >= 0)
    {
        sum -= arr[si + size - 1][sj - 1];
    }
    if (si - 1 >= 0 && sj - 1 >= 0)
    {
        sum += arr[si - 1][sj - 1];
    }

    if (sum == 0)
    { // if sum = 0, current square of of dim "size" contains white only
        white++;
        return;
    }
    if (sum == size * size)
    {
        blue++;
        return;
    }

    checkSame(size / 2, si, sj);
    checkSame(size / 2, si + size / 2, sj);
    checkSame(size / 2, si, sj + size / 2);
    checkSame(size / 2, si + size / 2, sj + size / 2);
}

void solve()
{
    int size;
    cin >> size;

    white = 0;
    blue = 0;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            int a;
            cin >> a;

            if (i == 0 && j == 0)
            {
                arr[i][j] = a;
            }
            else if (i == 0)
            {
                arr[i][j] = a + arr[i][j - 1];
            }
            else if (j == 0)
            {
                arr[i][j] = a + arr[i - 1][j];
            }
            else
            {
                arr[i][j] = a + arr[i - 1][j] + arr[i][j - 1] - arr[i - 1][j - 1];
                //  Because arr[i-1][j-1] gets counted twice: in arr[i-1][j] and arr[i][j-1]
            }
        }
    }

    checkSame(size, 0, 0);
    cout << white << " " << blue << '\n';
}
