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



int main() {
    int32_t n = 0;
    cin >> n;

    // vector<uint8_t> arr(n, 0);
    // vector<uint8_t> arrX(n, 0);
    // for (uint8_t& a : arr) {
    //     char in = 0;
    //     cin >> in;
    //     a = (in == '1');
    // }
    // {
    //     uint8_t prev = 0;
    //     for (int32_t i = 0; i < n; ++i) {
    //         prev ^= arr[i];
    //         arrX[i] = prev;
    //     }
    // }

    // vector<bool> arrCompare(n, 0);
    // for (int32_t i = 0; i < n; ++i) {
    //     arrCompare[i] = !arrX[i];
    // }

    // uint32_t num = 0;
    // for (uint32_t k = 2; k <= n; ++k) {
    //     bool goodK = true;
    //     for (uint32_t ki = k; ki <= n; ki += k) {
    //         if (!arrCompare[ki - 1]) {
    //             goodK = false;
    //             break;
    //         }
    //     }

    //     num += goodK;
    // }

    vector<bool> arr(n, 0);
    {
        bool prev = 0;
        for (uint32_t i = 0; i < n; ++i) {
            char in = 0;
            cin >> in;
            arr[i] = prev ^= (in == '1');
        }
    }

    uint32_t num = 0;
    for (uint32_t k = 2; k <= n; ++k) {
        bool goodK = true;
        for (uint32_t ki = k; ki <= n; ki += k) {
            if (arr[ki - 1]) {
                goodK = false;
                break;
            }
        }

        num += goodK;
    }


    cout << num << endl;

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

