#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <stdint.h>
#include <cmath>
#include <iomanip>
#include <complex>

#define ERRMSG (cout << "ERR LINE " << __LINE__ << endl)
#define ERRMSG_MSG(msg) (cout << "ERR LINE " << __LINE__ << " : " << msg << endl)
#define ASSERT(condition) { if (!condition) { ERRMSG; } }
#define ASSERT_MSG(condition, msg) { if (!condition) { ERRMSG_MSG(msg); } }

using namespace std;


using Num = complex<double>;
class FFT {
public:

    FFT(int logLimit);

    vector<Num> operator()(const vector<Num>& a0, bool inv = false);

private:
    int logLimit;
    int limit;
    vector<int> rev; /// Сопостовление индексов при перегруппировке
    void calcRev();  /// Сопостовление индексов при перегруппировке
    double const Pi = acos(-1.0);
    vector<Num> z; /// первообразные корни степени limit
    void calcZ();  /// первообразные корни степени limit
};


// ------------------------------        MAIN        ------------------------------
// ------------------------------------        ------------------------------------
// --------------------------------------    --------------------------------------
// ---------------------------------------  ---------------------------------------
// --------------------------------------------------------------------------------

int32_t calcLogLimit(int32_t n) {
    int32_t logLimit = 0;
    for (int32_t sum = 1; sum < n; sum <<= 1, ++logLimit);
    return logLimit;
}

void read(vector<Num>& arr, int32_t n) {
    for (int i = 0; i < (n - 1); ++i) {
        char in = 0;
        cin >> in;
        arr[i] = Num(int(in == '1'));
    }
}

int main() {
    int32_t n = 0;
    cin >> n;

    int32_t logLimit = calcLogLimit(n);
    int32_t limit = 2 << (logLimit + 1);
    FFT fft(logLimit + 1);

    /// [0][0] - барабан после вращения
    /// [1][0] - удвоенный дополненный нулём барабан до вращения
    /// [1][1] - удвоенный дополненный единицей барабан до вращения
    vector<vector<vector<Num>>> ss(2, vector<vector<Num>>(2, vector<Num>(limit)));

    read(ss[1][0], n);
    read(ss[0][0], n);
    copy(ss[1][0].begin(), ss[1][0].begin() + n - 1, ss[1][0].begin() + n);
    copy(ss[1][0].begin(), ss[1][0].end(), ss[1][1].begin());
    ss[1][0][n - 1] = 0;
    ss[1][1][n - 1] = 1;


    reverse(ss[0][0].begin(), ss[0][0].end());


    /// Преобразования Фурье для:
    /// [0][0] - барабан после вращения
    /// [1][0] - удвоенный дополненный нулём барабан до вращения
    /// [1][1] - удвоенный дополненный единицей барабан до вращения
    vector<vector<vector<Num>>> fas(2, vector<vector<Num>>(2));
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j <= i; ++j)
            fas[i][j] = fft(ss[i][j]);


    /// Вычисленное преобразование Фурье для:
    /// [0] совмещения дополненного нулём
    /// [1] совмещения дополненного единицей
    vector<vector<Num>> fc(2, vector<Num>(limit));
    for (int way = 0; way < 2; ++way)
        for (int i = 0; i < limit; ++i)
            fc[way][i] = fas[0][0][i] * fas[1][way][i];


    /// Обратно репреобразованные функции суммы совпадений для
    /// [0] совмещения дополненного нулём
    /// [1] совмещения дополненного единицей
    vector<vector<Num>> c(2, vector<Num>(limit));
    for (int way = 0; way < 2; ++way)
        c[way] = fft(fc[way], true);


    /// максимум, найдённый для совмещения дополненного:
    /// [0] нулём
    /// [1] единицей
    vector<int32_t> maxS(2, 0);
    for (int i = 0; i < limit; ++i)
        for (int way = 0; way < 2; ++way)
            maxS[way] = max(int(c[way][i].real() + 0.5), maxS[way]);


    if (maxS[0] == maxS[1])
        cout << "Random" << endl;
    else if (maxS[0] > maxS[1])
        cout << "No" << endl;
    else
        cout << "Yes" << endl;


    return 0;
}


// ------------------------------        FFT         ------------------------------
// ------------------------------------        ------------------------------------
// --------------------------------------    --------------------------------------
// ---------------------------------------  ---------------------------------------
// --------------------------------------------------------------------------------

FFT::FFT(int logLimit) : logLimit(logLimit), limit(2 << logLimit) {
    calcRev();
    calcZ();
}

vector<Num> FFT::operator()(const vector<Num>& a0, bool inv) {
    vector<Num> a = a0;
    for (int i = 0; i < limit; i++)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    if (inv)
        reverse(z.begin() + 1, z.end());
    for (int k = 0, span = 1, step = limit / 2; k < logLimit;
        k++, span *= 2, step /= 2) {
        for (int i = 0; i < limit; i += 2 * span)
            for (int j = 0; j < span; j++) {
                int u = i + j;
                int v = i + j + span;
                Num x = a[u] + a[v] * z[j * step];
                Num y = a[u] + a[v] * z[j * step + limit / 2];
                a[u] = x;
                a[v] = y;
            }
    }
    if (inv) {
        reverse(z.begin() + 1, z.end());
        for (int i = 0; i < limit; i++)
            a[i] /= limit;
    }
    return a;
}

void FFT::calcRev() {
    rev = vector<int>(limit, 0);
    for (int i = 0; i < limit; i++)
        for (int k = 0; k < logLimit; k++)
            if (i & (1 << k))
                rev[i] ^= 1 << (logLimit - k - 1);
}

void FFT::calcZ() {
    z = vector<Num>(limit);
    for (int i = 0; i < limit; i++)
        z[i] = Num(cos(i * 2 * Pi / limit),
            sin(i * 2 * Pi / limit));
}

// ------------------------------   FREE FUNCTIONS   ------------------------------
// ------------------------------------        ------------------------------------
// --------------------------------------    --------------------------------------
// ---------------------------------------  ---------------------------------------
// --------------------------------------------------------------------------------

