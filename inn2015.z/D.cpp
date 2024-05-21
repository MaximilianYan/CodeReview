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


typedef long double VecType_t;
class Vec2 {
public:
    VecType_t x, y;

    Vec2() : x(0), y(0) {}
    Vec2(VecType_t x, VecType_t y) : x(x), y(y) {}

    /// @brief Coord of Vec2 (x_1 [1] or x_2 [2])
    VecType_t& operator[](int i) {
        if (i == 1) return x;
        if (i == 2) return y;
        ASSERT_MSG(0, "incorrect Vec2[]");
        return x;
    }

    /// @brief Read Vec2 like "Point_x Point_y"
    friend istream& operator>>(istream& in, Vec2& vec);
    /// @brief Write Vec2 like "x y"
    friend ostream& operator<<(ostream& out, const Vec2& vec);
    /// @brief Scalar product
    friend VecType_t operator,(const Vec2& lo, const Vec2& ro);
    /// @brief -
    friend Vec2 operator-(const Vec2& lo, const Vec2& ro);
    /// @brief +
    friend Vec2 operator+(const Vec2& lo, const Vec2& ro);
    /// @brief a * V
    friend Vec2 operator*(const VecType_t& lo, const Vec2& ro);
    /// @brief V / a
    friend Vec2 operator/(const Vec2& lo, const VecType_t& ro);
    /// @brief Comparing
    friend bool operator==(const Vec2& lo, const Vec2& ro);

    Vec2 orthogon() const {
        return Vec2(-y, x);
    }

    /// @brief Absolute (length)
    VecType_t abs() const {
        return sqrt(x * x + y * y);
    }

    /// @brief Square of Absolute (length)
    VecType_t abssqr() const {
        return x * x + y * y;
    }
};


typedef VecType_t MatType_t;
class Mat {
public:
    MatType_t data[2][2];

    Mat() {
        data[0][0] = 0;
        data[0][1] = 0;
        data[1][0] = 0;
        data[1][1] = 0;
    }
    Mat(MatType_t a, MatType_t b, MatType_t c, MatType_t d) {
        data[0][0] = a;
        data[0][1] = b;
        data[1][0] = c;
        data[1][1] = d;
    }

    operator MatType_t() {
        return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    }
};


typedef VecType_t LineType_t;
class Line {
public:
    LineType_t a, b, c;

    Line() : a(0), b(0), c(0) {};

    /// @brief Line via two points
    Line(Vec2 x, Vec2 y) {
        // if ((x[2] - y[2]) == 0) {
            // a = 0;
            // b = 1;
            // c = -x[2];
        // }

        a = -(x[2] - y[2]);
        b = x[1] - y[1];
        c = -(a * x[1] + b * x[2]);
    }

    /// @brief Read line like "Point1_x Point1_y Point2_x Point2_y"
    friend istream& operator>>(istream& in, Line& line);
    /// @brief Write line parameters like "a b c"
    friend ostream& operator<<(ostream& out, const Line& line);

    /// @brief Are lines coincedental
    friend bool operator==(const Line& lo, const Line& ro);
    /// @brief Negative (lo == ro)
    friend bool operator!=(const Line& lo, const Line& ro);
    /// @brief Are lines parallel (lo != ro);
    friend bool operator%(const Line& lo, const Line& ro);

    /// @brief Common point of the lines (single or incorrect)
    friend Vec2 operator^(const Line& lo, const Line& ro);
};


class Segment {
public:
    Vec2 points[2];

    Line line;

    Segment() {
        points[0] = Vec2();
        points[1] = Vec2();
        line = Line(points[0], points[1]);
    };

    /// @brief Segment between two points
    Segment(Vec2 p0, Vec2 p1) {
        points[0] = p0;
        points[1] = p1;
        line = Line(points[0], points[1]);
    }

    /// @brief Read line like "Point1_x Point1_y Point2_x Point2_y"
    friend istream& operator>>(istream& in, Segment& segment);

    /// @brief Is the segment a point
    bool isTrivial();

    /// @brief Checks if the point belongs segment's bounding rectangle 
    bool isInRect(const Vec2& point);
    /*
    /// @brief Checks if the segment belongs segment's bounding rectangle
    bool isInRect(const Segment& segment);
    /*
    /// @brief Write line parameters like "a b c"
    friend ostream& operator<<(ostream& out, const Line& line);

    /// @brief Are lines coincedental
    friend bool operator==(const Line& lo, const Line& ro);
    /// @brief Negative (lo == ro)
    friend bool operator!=(const Line& lo, const Line& ro);
    /// @brief Are lines parallel (lo != ro);
    friend bool operator%(const Line& lo, const Line& ro);

    /// @brief Common point of the lines (single or incorrect)
    friend Vec2 operator^(const Line& lo, const Line& ro);
    */
};


// ------------------------------        MAIN        ------------------------------
// ------------------------------------        ------------------------------------
// --------------------------------------    --------------------------------------
// ---------------------------------------  ---------------------------------------
// --------------------------------------------------------------------------------

double calc(double n, Vec2 point) {
    point = Vec2(n, n) - point; // складываем за левый нижний угол

    Vec2 center = point / 2;

    if (center.abs() == 0) return n * n;

    Vec2 direction = center.orthogon();

    Line fold(center, center + direction);

    const Vec2 LW(0, 0); // left lower
    const Vec2 LU(0, n); // left upper
    const Vec2 RW(n, 0); // right upper
    const Vec2 RU(n, n); // right upper

    Vec2 pointL = fold ^ Line(LW, LU); // левая сторона
    Vec2 pointW = fold ^ Line(LW, RW); // нижняя сторона

    if (Segment(LW, RU).isInRect(pointL)) {
        if (Segment(LW, RU).isInRect(pointW)) {
            return n * n - pointL.y * pointW.x / 2.;
        } else {

            Vec2 pointR = fold ^ Line(RW, RU); // правая сторона
            Vec2 mid = (pointL + pointR) / 2;
            return n * n - n * mid.y;
        }
    } else {
        if (Segment(LW, RU).isInRect(pointW)) {

            Vec2 pointU = fold ^ Line(LU, RU); // верхняя сторона
            Vec2 mid = (pointW + pointU) / 2;
            return n * n - n * mid.x;

        } else {
            ERRMSG;
            return -1.;
        }
    }
}

int main() {
    int32_t n = 0;
    Vec2 point;
    cin >> n >> point;

    cout << setprecision(6) << calc(n, point) << endl;

    return 0;
}


// ------------------------------        VEC2        ------------------------------
// ------------------------------------        ------------------------------------
// --------------------------------------    --------------------------------------
// ---------------------------------------  ---------------------------------------
// --------------------------------------------------------------------------------

istream& operator>>(istream& in, Vec2& vec) {
    in >> vec.x >> vec.y;

    return in;
}

ostream& operator<<(ostream& out, const Vec2& vec) {
    out << fixed << setprecision(6) << vec.x << " " << vec.y;

    return out;
}

VecType_t operator,(const Vec2& lo, const Vec2& ro) {
    return lo.x * ro.x + lo.y * ro.y;
}

Vec2 operator-(const Vec2& lo, const Vec2& ro) {
    return Vec2(lo.x - ro.x, lo.y - ro.y);
}

Vec2 operator+(const Vec2& lo, const Vec2& ro) {
    return Vec2(lo.x + ro.x, lo.y + ro.y);
}

Vec2 operator*(const VecType_t& lo, const Vec2& ro) {
    return Vec2(lo * ro.x, lo * ro.y);
}

Vec2 operator/(const Vec2& lo, const VecType_t& ro) {
    return Vec2(lo.x / ro, lo.y / ro);
}

bool operator==(const Vec2& lo, const Vec2& ro) {
    return
        lo.x == ro.x &&
        lo.y == ro.y
        ;
}


// ------------------------------        LINE        ------------------------------
// ------------------------------------        ------------------------------------
// --------------------------------------    --------------------------------------
// ---------------------------------------  ---------------------------------------
// --------------------------------------------------------------------------------


istream& operator>>(istream& in, Line& line) {
    Vec2 point1, point2;
    cin >> point1 >> point2;

    line = Line(point1, point2);

    return in;
}

ostream& operator<<(ostream& out, const Line& line) {
    cout << line.a << " ";
    cout << line.b << " ";
    cout << line.c;

    return out;
}

bool operator==(const Line& lo, const Line& ro) {
    Mat mat_bc, mat_ac, mat_ab;

    mat_bc = Mat(
        lo.b, lo.c,
        ro.b, ro.c
    );
    mat_ac = Mat(
        lo.a, lo.c,
        ro.a, ro.c
    );
    mat_ab = Mat(
        lo.a, lo.b,
        ro.a, ro.b
    );

    MatType_t det_bc = mat_bc;
    MatType_t det_ac = mat_ac;
    MatType_t det_ab = mat_ab;

    if (det_ab == 0) {
        if (det_bc == 0 && det_ac == 0) {
            // coincedental
            return true;
        } else {
            // parallel
        }
    }
    return false;
    // if (lo.a == 0 || ro.a == 0) {
    //     return (lo.a == ro.a) && (lo.c * ro.b == ro.c * lo.b);
    // }
    // return (lo.b * ro.a == ro.b * lo.a) && (lo.c * ro.a == ro.c * lo.a);
}

bool operator!=(const Line& lo, const Line& ro) {
    return !(lo == ro);
}

bool operator%(const Line& lo, const Line& ro) {
    Mat mat_bc, mat_ac, mat_ab;

    mat_bc = Mat(
        lo.b, lo.c,
        ro.b, ro.c
    );
    mat_ac = Mat(
        lo.a, lo.c,
        ro.a, ro.c
    );
    mat_ab = Mat(
        lo.a, lo.b,
        ro.a, ro.b
    );

    MatType_t det_bc = mat_bc;
    MatType_t det_ac = mat_ac;
    MatType_t det_ab = mat_ab;

    if (det_ab == 0) {
        if (det_bc == 0 && det_ac == 0) {
            // coincedental
        } else {
            return true;
            // parallel
        }
    }
    return false;
    // if (lo == ro) {
    //     return false;
    // }
    // if (lo.a == 0 || ro.a == 0) {
    //     return (lo.a == ro.a);
    // }
    // return (lo.b * ro.a == ro.b * lo.a);
}

Vec2 operator^(const Line& lo, const Line& ro) {
    Mat mat_bc, mat_ac, mat_ab;

    mat_bc = Mat(
        lo.b, lo.c,
        ro.b, ro.c
    );
    mat_ac = Mat(
        lo.a, lo.c,
        ro.a, ro.c
    );
    mat_ab = Mat(
        lo.a, lo.b,
        ro.a, ro.b
    );

    MatType_t det_bc = mat_bc;
    MatType_t det_ac = mat_ac;
    MatType_t det_ab = mat_ab;

    if (det_ab == 0) {
        if (det_bc == 0 && det_ac == 0) {
            // coincedental
            return Vec2(239000, 239000);
        } else {
            // parallel
            return Vec2(-239000, -239000);
        }
    }

    return Vec2(det_bc / det_ab, -det_ac / det_ab);

    // if (lo.a == 0) {
    //     Vec2 res(0, 0);
    //     res[2] = -lo.c / lo.b;
    //     res[1] = -(res[2] * ro.b + ro.c) / ro.a;

    //     return res;
    // }

    // if (ro.a == 0) {
    //     Vec2 res(0, 0);
    //     res[2] = -ro.c / ro.b;
    //     res[1] = -(res[2] * lo.b + lo.c) / lo.a;

    //     return res;
    // }


    // Vec2 res(0, 0);
    // res[2] = -(ro.a * lo.c - lo.a * ro.c) / (ro.a * lo.b - lo.a * ro.b);
    // res[1] = -(ro.a * lo.b * res[2] + ro.a * lo.c) / (ro.a * lo.a);

    // return res;
}


// ------------------------------      SEGMENT       ------------------------------
// ------------------------------------        ------------------------------------
// --------------------------------------    --------------------------------------
// ---------------------------------------  ---------------------------------------
// --------------------------------------------------------------------------------

istream& operator>>(istream& in, Segment& segment) {
    Vec2 point1, point2;
    cin >> point1 >> point2;

    segment = Segment(point1, point2);

    return in;
}

bool Segment::isTrivial() {
    return points[0] == points[1];
}

bool Segment::isInRect(const Vec2& point) {
    return
        point.x >= min(points[0].x, points[1].x) &&
        point.x <= max(points[0].x, points[1].x) &&
        point.y >= min(points[0].y, points[1].y) &&
        point.y <= max(points[0].y, points[1].y)
        ;
}


// ------------------------------   FREE FUNCTIONS   ------------------------------
// ------------------------------------        ------------------------------------
// --------------------------------------    --------------------------------------
// ---------------------------------------  ---------------------------------------
// --------------------------------------------------------------------------------

