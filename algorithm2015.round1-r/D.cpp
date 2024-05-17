#include <iostream>
#include <stdint.h>

using namespace std;

#define ERRMSG (cout << "ERR LINE " << __LINE__ << endl)

// x∊S <=> ∃k : (n+k)^k = x

// ((n+k)^k)[i] = n[i],  если при суммировании не было переноса в позицию i
//              = ~n[i], если при суммировании    был  перенос  в позицию i

// Т.о. x - это n с некоторыми инвертированными битыми

// Если n[i] = 0, то этот бит может продолжать каскад переносов из-под себя налево и может останавливать каскад переносов налево
// Если n[i] = 1, то этот бит может продолжать каскад переносов из-под себя налево и может начинать каскад переносов налево

/// Объект для отсчёта позиции и соответствующей ей битовой маски
class PositionMask {
public:

    /// pos = 0, mask = 0..01 
    PositionMask();

    /// only allows = 0 instruction (pos = 0, mask = 0..01) 
    void operator=(int32_t zero);

    int32_t const& getPos();
    uint64_t const& getMask();

    void operator++();

    bool isOverflowed();

private:
    int32_t pos;
    uint64_t mask;
    bool overflowed;

    bool checkOverflow();
};

/// позиция+1 старшего бита, в котором различаются l и r (0, если l == r)
int32_t calcMajDiffPos(uint64_t const& l, uint64_t const& r);


// ------------------------------        MAIN        ------------------------------
// ------------------------------------        ------------------------------------
// --------------------------------------    --------------------------------------
// ---------------------------------------  ---------------------------------------
// --------------------------------------------------------------------------------

int main() {
    uint64_t n = 0, l = 0, r = 0;
    cin >> n >> l >> r;

    //                                         // l, r <= 1e18, поэтому не выйдет за последний бит
    int32_t majDiffPos = calcMajDiffPos(l, r); // позиция+1 старшего бита, в котором различаются l и r (0, если l == r)


    // изучаем, можно ли удовлетворить общему префиксу l и r и что для этого нужно
    bool canSetCommonPrefix = true;     // можно ли удовлетворить общему префиксу l и r
    bool mustStartCarryCascade = false; // нужно ли для этого заранее начинать каскад переносов налево
    uint64_t startCarryCascade = 0;     // если нужно, то с какой позиции
    {
        PositionMask pos;   // текущая позиция в числе n
        int32_t last1 = -1; // позиция последней встреченной в n 1-ы

        for (pos = 0; pos.getPos() < majDiffPos; ++pos)
            if (n && pos.getMask())
                last1 = pos.getPos();

        // pos.getPos() == majDiffPos


        bool hasNew1 = false; // есть ли единицы левее общей границы

        // pos.getPos() == majDiffPos
        for (; !pos.isOverflowed(); ++pos) {
            
            
            if (n && pos.getMask())
                last1 = pos.getPos();
                hasNew1 = true;
            ;
        }

    }

    uint64_t numOn = 0;  // количество чисел, которые можно получить, если в есть перенос в текущую позицию
    uint64_t numOff = 0; // количество чисел, которые можно получить, если в нет переноса в текущую позицию
    int32_t pos = 0;     // текущая позиция в числе n

    for (pos = 0; pos < 64; ++pos) {

    }


    return 0;
}


// ------------------------------    POSITIONMASK    ------------------------------
// ------------------------------------        ------------------------------------
// --------------------------------------    --------------------------------------
// ---------------------------------------  ---------------------------------------
// --------------------------------------------------------------------------------

PositionMask::PositionMask() {
    *this = 0;
}

void PositionMask::operator=(int32_t zero) {
    if (zero != 0) ERRMSG;

    pos = 0;
    mask = 1;
    overflowed = false;
}

int32_t const& PositionMask::getPos() {
    checkOverflow();
    return pos;
};
uint64_t const& PositionMask::getMask() {
    checkOverflow();
    return mask;
};

void PositionMask::operator++() {
    checkOverflow();

    ++pos;
    mask <<= 1;

    if (pos >= 65) overflowed = true;
}

bool PositionMask::isOverflowed() {
    return overflowed;
}

bool PositionMask::checkOverflow() {
    if (overflowed) ERRMSG;
    return isOverflowed();
}


// ------------------------------   FREE FUNCTIONS   ------------------------------
// ------------------------------------        ------------------------------------
// --------------------------------------    --------------------------------------
// ---------------------------------------  ---------------------------------------
// --------------------------------------------------------------------------------

int32_t calcMajDiffPos(uint64_t const& l, uint64_t const& r) {
    uint64_t xorLR = l ^ r;
    int32_t res = 0;

    if (xorLR == 0) {
        return 0;
    }

    // l, r <= 1e18, поэтому res станет больше, не выйдя за последний бит

    for (res = 0;
        (1 << (res)) <= xorLR;
        ++res);

    return res;
}
