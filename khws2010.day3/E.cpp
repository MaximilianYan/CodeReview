#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdint.h>

using namespace std;

#define LOCAL

#define ERRMSG (cout << "ERR LINE " << __LINE__ << endl)

#ifdef LOCAL
#define INIT                            \
    /* ios_base::sync_with_stdio(false); \
    cin.tie(NULL); */
#define INPUT cin
#define OUTPUT cout
#else
#define INIT               \
    ifstream input("e.in"); \
    ofstream output("e.out");
#define INPUT input
#define OUTPUT output
#endif

const int32_t DIM = 2;
const int32_t RDIM = 2;

class Point {
public:
    Point();
    Point(int32_t x, int32_t y);

    int32_t& operator[](size_t r);
    int32_t const& operator[](size_t r) const;

    friend istream& operator>>(istream& input, Point& r);

    // лежит ли точка по обеим координатам более
    bool operator>>(Point const& r) const;

private:
    vector<int32_t> coords;
};

class Rectangle {
public:
    Rectangle();

    Point& operator[](size_t r);
    Point const& operator[](size_t r) const;

    // прямоугольник будет задан левой нижней и правой верхней вершинами
    friend istream& operator>>(istream& input, Rectangle& r);

    // содержится ли прямоугольник внутри данного
    bool operator>>(Rectangle const& r) const;

    uint64_t size() const;

private:
    vector<Point> vertexes;
};

// ------------------------------        MAIN        ------------------------------
// ------------------------------------        ------------------------------------
// --------------------------------------    --------------------------------------
// ---------------------------------------  ---------------------------------------
// --------------------------------------------------------------------------------

int main() {
    INIT;

    int32_t n = 0;
    INPUT >> n;

    vector<Rectangle> rects(n);
    for (int32_t i = 0; i < n; ++i) {
        INPUT >> rects[i];
    }

    sort(rects.begin(), rects.end(), [](const Rectangle& l, const Rectangle& r) -> bool {
        return l.size() > r.size();
    });

    for (int32_t i = 0; i < rects.size(); ++i) {
        for (int32_t j = i + 1; j < rects.size(); ++j) {
            if (rects[i] >> rects[j]) {
                rects.erase(rects.begin() + j);
                --j;
            }
        }
    }

    cout << rects.size() << endl;

    return 0;
}


// ------------------------------       POINT        ------------------------------
// ------------------------------------        ------------------------------------
// --------------------------------------    --------------------------------------
// ---------------------------------------  ---------------------------------------
// --------------------------------------------------------------------------------

Point::Point() : coords(DIM, 0) {}

Point::Point(int32_t x, int32_t y) : coords({ x, y }) {}

int32_t& Point::operator[](size_t r) {
    return coords[r];
}

int32_t const& Point::operator[](size_t r) const {
    return coords[r];
}

istream& operator>>(istream& input, Point& r) {
    for (size_t i = 0; i < DIM; ++i)
        input >> r[i];

    return input;
}

bool Point::operator>>(Point const& r) const {
    for (size_t i = 0; i < DIM; ++i)
        if (!((*this)[i] > r[i])) return false;
    return true;
}


uint64_t Rectangle::size() const {
    return
        ((*this)[0][1] - (*this)[0][0]) *
        ((*this)[1][1] - (*this)[1][0]);
}


// ------------------------------     RECTANGLE      ------------------------------
// ------------------------------------        ------------------------------------
// --------------------------------------    --------------------------------------
// ---------------------------------------  ---------------------------------------
// --------------------------------------------------------------------------------

Rectangle::Rectangle() : vertexes(RDIM, Point()) {}

Point& Rectangle::operator[](size_t r) {
    return vertexes[r];
}

Point const& Rectangle::operator[](size_t r) const {
    return vertexes[r];
}

istream& operator>>(istream& input, Rectangle& r) {
    vector<int32_t> xs(RDIM);
    vector<int32_t> ys(RDIM);
    for (size_t i = 0; i < RDIM; ++i)
        input >> xs[i] >> ys[i];

    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());

    for (size_t i = 0; i < RDIM; ++i)
        r[i] = Point(xs[i], ys[i]);

    return input;
}

bool Rectangle::operator>>(Rectangle const& r) const {
    return
        r[0] >> (*this)[0] &&
        (*this)[1] >> r[1];
}


// ------------------------------   FREE FUNCTIONS   ------------------------------
// ------------------------------------        ------------------------------------
// --------------------------------------    --------------------------------------
// ---------------------------------------  ---------------------------------------
// --------------------------------------------------------------------------------

