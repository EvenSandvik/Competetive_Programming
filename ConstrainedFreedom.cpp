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

//TODO: vectors
//Example: vector<datatype> rainfall(Nsize, constant);

LL rows, columns;
LL paths;
int wall = 0;

void uniquePaths(vector<vector<bool>> &grid, LL row, LL column)
{

    //can move either up, down or right
    //Vector<vector> 2d array pretty much
    vector<vector<LL>> moveRight(row + 1, vector<LL>(column + 1));
    vector<vector<LL>> moveUp(row + 1, vector<LL>(column + 1));
    vector<vector<LL>> moveDown(row + 1, vector<LL>(column + 1));

    //Bottom left is 1
    moveUp[1][column - 1] = 1;
    for (LL c = column - 1; c >= 0; c--)
    {

        //Check all possible/legal directions to move
        for (LL r = 1; r <= row; r++)
        {
            //if it meets wall
            if (!grid[r - 1][c])
            {
                moveRight[r][c] = wall;
                moveUp[r][c] = wall;
                moveDown[r][c] = wall;
            }
        }

        //Updating values
        
        //Update 2d vectors for right with surronding values
        for (LL r = 1; r <= row; r++)
        {
            if (grid[r - 1][c])
            {
                moveRight[r][c] = moveUp[r][c + 1] + moveDown[r][c + 1] + moveRight[r][c + 1];
                //printf("%lld", moveRight[r][c])
            }
        }
        for (LL r = 2; r <= row; r++)
        {
            if (grid[r - 1][c])
            {
                moveUp[r][c] = moveUp[r - 1][c] + moveRight[r - 1][c];
                //printf("%lld", moveUp[r][c])
            }
        }
        for (LL r = row - 1; r >= 1; r--)
        {
            if (grid[r - 1][c])
            {
                moveDown[r][c] = moveDown[r + 1][c] + moveRight[r + 1][c];
                //printf("%lld", moveDown[r][c])
            }
        }
    }

    //This line might not work...
    paths = moveUp[row][0] + moveRight[row][0] + moveDown[row][0];
    //printf("%lld", paths);

    return;
}

//TODO, make ints to longs if it fails
//Translated from java to c++, scanner to slow
int main()
{
    while (1)
    {
        paths = 0;
        //TODO: Break when reaches EOF
        scanf("%lld %lld", &rows, &columns);

        //If 0 0, return nothing
        if (rows == 0 && columns == 0)
            break;

        //Read in grid. TODO change 2d array to vector thing
        vector<vector<bool>> grid(rows, vector<bool>(columns));
        for (LL r = 0; r < rows; ++r)
        {
            char line[100];

            scanf("%s", line);
            for (LL c = 0; c < columns; c++)
            {
                if (line[c] == '.')
                    grid[r][c] = true;
                else if (line[c] == '#')
                    grid[r][c] = false;
            }
        }

        //calculate number of paths that lead to finish
        uniquePaths(grid, rows, columns);

        //print. Check if printf is slow...
        printf("%lld\n", paths);
    }
}