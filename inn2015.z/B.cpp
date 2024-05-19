#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <stdint.h>

#define ERRMSG (cout << "ERR LINE " << __LINE__ << endl)

using namespace std;

class Rectangle {
public:
    Rectangle();


private:
};

// ------------------------------        MAIN        ------------------------------
// ------------------------------------        ------------------------------------
// --------------------------------------    --------------------------------------
// ---------------------------------------  ---------------------------------------
// --------------------------------------------------------------------------------

void no() {
    cout << "NO" << endl;
}

void yes() {
    cout << "YES" << endl;
}

void prX(int32_t num) {
    for (int i = 0; i < num; ++i) cout << "G";
}

void prY(int32_t num) {
    for (int i = 0; i < num; ++i) cout << "B";
}

void out(int32_t x, int32_t y, int32_t limitX, int32_t limitY, int32_t xClusterNum, int32_t yClusterNum,
    function<void(int32_t)> prX, function<void(int32_t)> prY, int32_t h) {
    if (x < (yClusterNum - 1)) no();
    else {
        yes();
        if (h) {
            for (int i = 0; i < yClusterNum - 1; ++i) {
                prY(limitY);
                prX(x / (yClusterNum - 1));
            }
            prY(y - limitY * (yClusterNum - 1));
            prX(x - x / (yClusterNum - 1) * (yClusterNum - 1));
        }
    }
}

void outEq(int32_t x, int32_t y, int32_t limitX, int32_t limitY, int32_t xClusterNum, int32_t yClusterNum,
    function<void(int32_t)> prX, function<void(int32_t)> prY, int32_t h) {

    if (xClusterNum != yClusterNum) ERRMSG;

    if (x < (yClusterNum - 1)) no();
    else {
        yes();
        if (h) {
            for (int i = 0; i < yClusterNum - 1; ++i) {
                prY(limitY);
                prX(limitX);
            }
            prY(y - limitY * (yClusterNum - 1));
            prX(x - limitX * (xClusterNum - 1));
        }
    }
}

int main() {
    int32_t h = 0;
    int32_t x, y, limitX, limitY;
    cin >> h >> x >> y >> limitX >> limitY;

    int32_t xClusterNum = (x / limitX) + ((x % limitX) != 0);
    int32_t yClusterNum = (y / limitY) + ((y % limitY) != 0);

    if (xClusterNum < yClusterNum)
        out(x, y, limitX, limitY, xClusterNum, yClusterNum, prX, prY, h);
    else if (xClusterNum > yClusterNum)
        out(y, x, limitY, limitX, yClusterNum, xClusterNum, prY, prX, h);
    else
        outEq(y, x, limitY, limitX, yClusterNum, xClusterNum, prY, prX, h);

    return 0;
}


// ------------------------------     RECTANGLE      ------------------------------
// ------------------------------------        ------------------------------------
// --------------------------------------    --------------------------------------
// ---------------------------------------  ---------------------------------------
// --------------------------------------------------------------------------------


// ------------------------------   FREE FUNCTIONS   ------------------------------
// ------------------------------------        ------------------------------------
// --------------------------------------    --------------------------------------
// ---------------------------------------  ---------------------------------------
// --------------------------------------------------------------------------------

