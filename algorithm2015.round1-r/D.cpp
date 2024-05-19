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

    void operator=(int32_t newPos);

    int32_t const& getPos();
    uint64_t const& getMask();

    void operator++();
    void operator--();

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


    PositionMask pos; // текущая позиция в числе n

    bool commonLR = true; // true, пока мы на общей части l и r

    uint64_t numCurCarryLR = 1;   // количество возможных решений,    требующих перенос в левый от текущего бит
    uint64_t numCurNoCarryLR = 1; // количество возможных решений, не требующих перенос в левый от текущего бит

    //                                       // [0] - идущих по нижней грани
    //                                       // [1] - идущих свободно между гранями
    //                                       // [2] - идущих по верхней грани
    uint64_t numCurCarry[3] = { 0, 0, 0 };   // количество возможных решений,    требующих перенос в левый от текущего бит
    uint64_t numCurNoCarry[3] = { 0, 0, 0 }; // количество возможных решений, не требующих перенос в левый от текущего бит

    for (pos = 63; !pos.isOverflowed(); --pos) {
        uint64_t curBitN = n & pos.getMask(); // оставляем только рассматриваемый бит в n
        uint64_t curBitL = l & pos.getMask(); // оставляем только рассматриваемый бит в l
        uint64_t curBitR = r & pos.getMask(); // оставляем только рассматриваемый бит в r

        uint64_t numNextCarryLR = 0;   // количество возможных решений,    требующих перенос в текущий бит
        uint64_t numNextNoCarryLR = 0; // количество возможных решений, не требующих перенос в текущий бит

        uint64_t numNextCarry[3] = { 0, 0, 0 };   // количество возможных решений,    требующих перенос в левый от текущего бит
        uint64_t numNextNoCarry[3] = { 0, 0, 0 }; // количество возможных решений, не требующих перенос в левый от текущего бит

        if (commonLR) {
            if (curBitL == curBitR) {
                if (curBitN == curBitL) {
                    // нам не нужен перенос в текущий бит

                    numNextCarryLR = 0;

                    if (curBitN) {
                        // можем запустить каскад переносов налево
                        numNextNoCarryLR = numCurCarryLR + numCurNoCarryLR;
                    } else {
                        // не можем запустить каскад переносов налево
                        numNextNoCarryLR = numCurNoCarryLR;
                    }


                } else {
                    // нам нужен перенос в текущий бит

                    numNextNoCarryLR = 0;

                    if (curBitN) {
                        // не можем остановить каскад переносов налево
                        numNextCarryLR = numCurCarryLR;
                    } else {
                        // можем остановить каскад переносов налево
                        numNextCarryLR = numCurCarryLR + numCurNoCarryLR;
                    }


                }

                numCurCarryLR = numNextCarryLR;
                numCurNoCarryLR = numNextNoCarryLR;
                continue;


            } else {
                if (curBitL != 0) ERRMSG;
                if (curBitR == 0) ERRMSG;

                commonLR = false;

                if (curBitN) {
                    // можем запустить каскад переносов налево
                    // не можем остановить каскад переносов налево

                    // инвертируя прижимаемся к нижней грани
                    numNextCarry[0] = numCurCarryLR;

                    // не инвертируя прижимаемся к верхней грани
                    numNextNoCarry[2] = numCurCarryLR + numCurNoCarryLR;


                } else {
                    // не можем запустить каскад переносов налево
                    // можем остановить каскад переносов налево

                    // не инвертируя прижимаемся к нижней грани
                    numNextNoCarry[0] = numCurNoCarryLR;

                    // инвертируя прижимаемся к верхней грани
                    numNextCarry[2] = numCurCarryLR + numCurNoCarryLR;
                }


                numCurCarry[0] = numNextCarry[0];
                numCurCarry[1] = numNextCarry[1];
                numCurCarry[2] = numNextCarry[2];
                numCurNoCarry[0] = numNextNoCarry[0];
                numCurNoCarry[1] = numNextNoCarry[1];
                numCurNoCarry[2] = numNextNoCarry[2];
                continue;


            }
        } else {
            // commonLR == false


            if (curBitN) {
                // можем запустить каскад переносов налево
                // не можем остановить каскад переносов налево

                if (curBitL) {
                    // не инвертируя прижимаемся к нижней грани
                    numNextNoCarry[0] = numCurCarry[0] + numCurNoCarry[0];
                } else {
                    // инвертируя прижимаемся к нижней грани
                    numNextCarry[0] = numCurCarry[0];

                    // не инвертируя уходим от граней
                    numNextNoCarry[1] += numCurCarry[0] + numCurNoCarry[0];
                }

                if (curBitR) {
                    // не инвертируя прижимаемся к верхней грани
                    numNextNoCarry[2] = numCurCarry[2] + numCurNoCarry[2];

                    // инвертируя уходим от граней
                    numNextCarry[1] += numCurCarry[2];
                } else {
                    // инвертируя прижимаемся к верхней грани
                    numNextCarry[2] = numCurCarry[2];
                }

                numNextCarry[1] += numCurCarry[1];
                numNextNoCarry[1] += numCurCarry[1] + numCurNoCarry[1];



            } else {
                // не можем запустить каскад переносов налево
                // можем остановить каскад переносов налево


                if (curBitL) {
                    // не инвертируя прижимаемся к нижней грани
                    numNextNoCarry[0] = numCurNoCarry[0];

                    // инвертируя уходим от граней
                    numNextCarry[1] += numCurCarry[0] + numCurNoCarry[0];
                } else {
                    // инвертируя прижимаемся к нижней грани
                    numNextCarry[0] = numCurCarry[0] + numCurNoCarry[0];
                }

                if (curBitR) {
                    // не инвертируя прижимаемся к верхней грани
                    numNextNoCarry[2] = numCurNoCarry[2];

                    // инвертируя уходим от граней
                    numNextCarry[1] += numCurCarry[2] + numCurNoCarry[2];
                } else {
                    // инвертируя прижимаемся к верхней грани
                    numNextCarry[2] = numCurCarry[2] + numCurNoCarry[2];
                }

                numNextCarry[1] += numCurCarry[1] + numCurNoCarry[1];
                numNextNoCarry[1] += numCurNoCarry[1];


            }





            numCurCarry[0] = numNextCarry[0];
            numCurCarry[1] = numNextCarry[1];
            numCurCarry[2] = numNextCarry[2];
            numCurNoCarry[0] = numNextNoCarry[0];
            numCurNoCarry[1] = numNextNoCarry[1];
            numCurNoCarry[2] = numNextNoCarry[2];
            continue;
        }
    }


    uint64_t answer = numCurNoCarry[0] + numCurNoCarry[1] + numCurNoCarry[2];
    cout << answer << endl;

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

void PositionMask::operator=(int32_t newPos) {
    if (newPos >= 64 || newPos < 0) ERRMSG;

    pos = newPos;
    mask = uint64_t(1) << newPos;
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

    if (pos >= 64) overflowed = true;
}

void PositionMask::operator--() {
    checkOverflow();

    --pos;
    mask >>= 1;

    if (pos < 0) overflowed = true;
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
