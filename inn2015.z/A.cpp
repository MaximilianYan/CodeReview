#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdint.h>

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

int main() {
    vector<vector<int32_t>> rsp(2, vector<int32_t>(3, 0));

    for (size_t i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j)
            cin >> rsp[i][j];

    int32_t res = 0;
    for (size_t i = 0; i < 3; ++i) {
        res += min(rsp[0][i], rsp[1][(i + 1) % 3]);
    }

    cout << res << endl;

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

