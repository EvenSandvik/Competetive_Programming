#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <cmath>
#include <tuple>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <climits>
#include <cfloat>
#include <set>
#include <map>
#include <queue>
#include <stdexcept>
#include <iomanip>

using namespace std;

// Shortcuts for common data types
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef pair<int, int> pii;
typedef vector<pii> vii;
typedef vector<int> vi;

// Various
#define rep(i, n) for (int i = 0; i < (n); i++)
#define foreach(i, a) for (__typeof(a.begin()) i = a.begin(); i != a.end(); i++)
#define feq(x, y) (fabs(x - y) <= DBL_EPSILON)
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

// Bit operations
#define set_bit(x, i) (x) |= (1 << (i))
#define clr_bit(x, i) (x) & ~(1 << (i))
#define tog_bit(x, i) (x) ^= (1 << (i))
#define chk_bit(x, i) (((x) >> (i)) & 1)

// Quick scanning
#define sf(n) scanf("%d", &n)
#define sff(a, b) scanf("%d %d", &a, &b)
#define sfff(a, b, c) scanf("%d %d %d", &a, &b, &c)

// Useful constants
#define MOD 1000000007
#define INF ((int)1e9)
#define EPS 1e-9

// Shortcuts for pair
#define x first
#define y second

// Debugging
#define DBUG(x) std::cout << #x << " is " << x << "\n"

LL nCars;

// Calculates numbers of cars, return integer
template <class T>
int longestIncreasingSubsequence(deque<T> &deck)
{
    LL longestSub = 1;
    LL deckSize = deck.size();
    if (deckSize == 0)
        return 0;

    //Automatically initialized to 0's
    deque<LL> q2(deckSize);
    //q1 is the deck with small values. Set to really small
    deque<LL> q1(deckSize, -999);
    deque<LL> maxCars;
    for (LL index = 1; index < deckSize; index++)
    {
        LL right = longestSub - 1;
        LL left = -1;

        //printf("v[i]: %lld \n", v[i]);
        //printf("v[t[0]]): %lld \n", v[t[0]]);
        if (deck[q2[0]] >= deck[index])
        {
            //printf("max1\n");
            q2[0] = index;
        }
        else if (deck[q2[longestSub - 1]] < deck[index])
        {
            //update deque1 with value in q2
            q1[index] = q2[longestSub - 1];
            //printf("max2\n");

            q2[longestSub++] = index;
        }
        else
        {
            //printf("max3\n");
            while (1 < right - left)
            {
                LL max = left + ((right - left) / 2);
                if (deck[index] > deck[q2[max]])
                    left = max;
                else
                    right = max;
            }
            //update deque1
            q1[index] = q2[right - 1];
            //update deque2
            q2[right] = index;
        }
    }

    //Push cars to maxCars
    for (LL i = q2[longestSub - 1]; i >= 0; i = q1[i])
    {
        maxCars.push_back(i);
    }
    reverse(maxCars.begin(), maxCars.end());
    return maxCars.size();
}

int main()
{
    LL temp = scanf("%lld", &nCars);

    //Double ended queue. Cars from both sides.
    deque<LL> deckQueue(nCars);

    /*LL val;
    for (int i = 0; i < nCars; i++)
    {
        scanf("%lld", &val);
        //TODO: shouldnt matter if front or back
        deckQueue.push_front(val);
    }*/
    for (LL &val : deckQueue)
    {
        temp = scanf("%lld", &val);
    }

    LL maxCars = 0;
    while (deckQueue.size() > 0)
    {
        deque<pair<LL, LL>> deckAscending;
        deque<pair<LL, LL>> deckDescending;

        LL center = deckQueue.front();
        //printf("%lld", center);
        deckQueue.pop_front();

        //Because can fill from both ends need ascending and descending
        //Normal LIS gives error
        for (LL deckIndex : deckQueue)
        {
            if (deckIndex < center)
            {
                LL deckSize = deckDescending.size();
                deckDescending.push_back({-deckIndex, -deckSize});
            }
        }
        for (LL deckIndex2 : deckQueue)
        {
            if (deckIndex2 > center)
            {
                LL deckSize = deckAscending.size();
                deckAscending.push_back({deckIndex2, deckSize});
            }
        }

        if (maxCars < 1 + longestIncreasingSubsequence(deckDescending) + longestIncreasingSubsequence(deckAscending))
        {
            maxCars = 1 + longestIncreasingSubsequence(deckDescending) + longestIncreasingSubsequence(deckAscending);
        }
    }
    printf("%lld", maxCars);
}