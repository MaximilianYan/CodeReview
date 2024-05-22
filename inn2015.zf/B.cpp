#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <stdint.h>
#include <cmath>
#include <iomanip>

#define ERRMSG (cout << "ERR LINE " << __LINE__ << endl)
#define ERRMSG_MSG(msg) (cout << "ERR LINE " << __LINE__ << " : " << msg << endl)
#define ASSERT(condition) { if (!condition) { ERRMSG; } }
#define ASSERT_MSG(condition, msg) { if (!condition) { ERRMSG_MSG(msg); } }

using namespace std;

class Info {
public:

    Info() {}

    friend istream& operator>>(istream& l, Info& r);

    void calcMaxPref(int32_t n);

    uint32_t operator[](int32_t i);

    uint32_t size();

private:
    uint32_t a, b, mod, first;
    vector<uint32_t> data;
    vector<uint32_t> maxpref;
};

// ------------------------------        MAIN        ------------------------------
// ------------------------------------        ------------------------------------
// --------------------------------------    --------------------------------------
// ---------------------------------------  ---------------------------------------
// --------------------------------------------------------------------------------

int32_t calc(vector<Info>& infos) {
    for (int i = infos[0].size() - 1; i >= 0; --i)
        if (infos[0][i] == infos[1][i]) return i + 1;
    return 0;
}

int main() {
    int32_t n = 0;
    vector<Info> infos(2);

    cin >> n;

    for (Info& info : infos)
        cin >> info;

    cout << calc(infos) << endl;

    return 0;
}


// ------------------------------        INFO        ------------------------------
// ------------------------------------        ------------------------------------
// --------------------------------------    --------------------------------------
// ---------------------------------------  ---------------------------------------
// --------------------------------------------------------------------------------

istream& operator>>(istream& l, Info& r) {
    l >> r.a >> r.b >> r.mod >> r.first;
    r.a %= r.mod;
    r.b %= r.mod;
    return l;
}

void Info::calcMaxPref(int32_t n) {
    maxpref.resize(n);
    maxpref[0] = first;
    data.resize(n);
    data[0] = first;

    for (int32_t i = 1; i < maxpref.size(); ++i) {
        maxpref[i] = (maxpref[i - 1] * a + b) % mod;
        data[i] = max(maxpref[i], maxpref[i - 1]);
    }
}

uint32_t Info::operator[](int32_t i) {
    return maxpref[i];
}

uint32_t Info::size() {
    return maxpref.size();
}


// ------------------------------   FREE FUNCTIONS   ------------------------------
// ------------------------------------        ------------------------------------
// --------------------------------------    --------------------------------------
// ---------------------------------------  ---------------------------------------
// --------------------------------------------------------------------------------

