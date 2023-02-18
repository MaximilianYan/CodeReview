/*
Решение судоку. На затраты по времени и памяти все равно.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class TableTempl {
public:
    TableTempl();
    bool isTable;
protected:
    TableTempl(bool t);
};

class Table: public TableTempl {
public:
    Table();

    bool isCorrect() const;
    bool isCellCorrect(int i0, int j0) const;

    bool isCellFilled(int index) const;
    bool tryCell(int index, int tryNumber);
    bool clearCell(int index);

    friend istream& operator>>(istream& in, Table& table);
    friend ostream& operator<<(ostream& out, Table& table);

    void updateCaps();

    class CellRating {
    public:
        CellRating();
        void rate(const Table& table);
        int getNum(int pos) const;
    private:
        struct Score {
            int score;
            int num;
        };

        Score rating[81];
    };
private:
    int data[81];

    int rowCap[9];
    int colCap[9];
    int clasterCap[9];

    static int getIndex(int i, int j);
};

/*

    Intelligent solution:

    compl: counter:
       0 : 1
       1 : 38
       2 : 8658
       3 : 6053

    Simplified solution:

*/

int counter = 0;

bool solve(Table& table) {
    ++counter;

    Table::CellRating patternRating;
    patternRating.rate(table);

    for (int tryI = 0; tryI < 81; ++tryI) {
    // for (int k = 0; k < 81; ++k) {
        // int tryI = patternRating.getNum(k);
        if (table.isCellFilled(tryI)) continue;


        for (int num = 1; num <= 9; ++num) {
            if (table.tryCell(tryI, num)) {

                if (solve(table))
                    return true;
            }
        }

        table.clearCell(tryI);

        return false;
    }

    return true;
}

#ifndef NOMAIN

int main() {
    Table pattern;
    cin >> pattern;

    if (solve(pattern))
        // cout << pattern << endl;
        cout << endl;
    else
        cout << "Cannot solve" << endl;

    cout << "counter : " << counter << endl;
}

#endif // NOMAIN

TableTempl::TableTempl(): isTable(false) {}
TableTempl::TableTempl(bool t): isTable(t) {}

Table::Table(): TableTempl(true), data{}, rowCap{}, colCap{}, clasterCap{} {}

#define CHECK_NUM(i, j)                 \
    int num = data[getIndex(i, j)];      \
    if (num < 0 || num > 9) return false; \
    if (num && nums[num]) return false;           \
    nums[num] = true;

#define FOR(lit, lim) \
    for (int lit = 0; lit < lim; ++lit)

bool Table::isCorrect() const {
    FOR(i, 9) {
        vector<bool> nums(10, false);

        FOR(j, 9) {
            CHECK_NUM(i, j);
        }
    }

    FOR(i, 9) {
        vector<bool> nums(10, false);

        FOR(j, 9) {
            CHECK_NUM(j, i);
        }
    }

    FOR(si, 3) {
        FOR(sj, 3) {
            vector<bool> nums(10, false);

            FOR(i, 3) {
                FOR(j, 3) {
                    CHECK_NUM(3 * si + i, 3 * sj + j);
                }
            }
        }
    }

    return true;
}

bool Table::isCellCorrect(int i0, int j0) const {
    int i = i0; {
        vector<bool> nums(9, false);

        FOR(j, 9) {
            CHECK_NUM(i, j);
        }
    }

    i = j0; {
        vector<bool> nums(9, false);

        FOR(j, 9) {
            CHECK_NUM(j, i);
        }
    }

    int si = i0 / 3;
    int sj = j0 / 3; {
        vector<bool> nums(9, false);

        FOR(i, 3) {
            FOR(j, 3) {
                CHECK_NUM(3 * si + i, 3 * sj + j);
            }
        }
    }

    return true;
}

#undef CHECK_NUM
#undef FOR

bool Table::isCellFilled(int index) const {
    return data[index];
}

bool Table::tryCell(int index, int tryNumber) {
    if (tryNumber == 0)
        cout << "INCORRECT CODE" << endl;
    if (data[index] == 0) {
        int i = index / 9;
        int j = index % 9;
        rowCap[i]++;
        colCap[j]++;
        clasterCap[(i / 3) * 3 + j / 3]++;
    }

    data[index] = tryNumber;

    return isCorrect();
}

bool Table::clearCell(int index) {
    if (data[index] != 0) {
        int i = index / 9;
        int j = index % 9;
        rowCap[i]--;
        colCap[j]--;
        clasterCap[(i / 3) * 3 + j / 3]--;
    }

    data[index] = 0;

    return isCorrect();
}

istream& operator>>(istream& in, Table& table) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            in >> table.data[table.getIndex(i, j)];
        }
    }
    table.updateCaps();

    return in;
}

ostream& operator<<(ostream& out, Table& table) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            out << table.data[table.getIndex(i, j)] << " ";
        }
        out << endl;
    }

    return out;
}

#define ROWCAP rowCap[i]
#define COLCAP colCap[j]
#define CLASTERCAP clasterCap[(i / 3) * 3 + j / 3]

void Table::updateCaps() {
    for (int n = 0; n < 9; ++n) {
        rowCap[n] = 0;
        colCap[n] = 0;
        clasterCap[n] = 0;
    }

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (data[getIndex(i, j)] != 0) {
                ++ROWCAP;
                ++COLCAP;
                ++CLASTERCAP;
            }
        }
    }
}

int Table::getIndex(int i, int j) {
    return i * 9 + j;
}

Table::CellRating::CellRating(): rating{} {}

void Table::CellRating::rate(const Table& table) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int n = Table::getIndex(i, j);
            rating[n].num = n;
            rating[n].score = max(
                table.ROWCAP, max(
                    table.COLCAP,
                    table.CLASTERCAP
                ));
        }
    }

    qsort(rating, 81, sizeof(Score), [](const void* x, const void* y) -> int {
        if (((Score*)x)->score > ((Score*)y)->score) return 1;
    if (((Score*)x)->score < ((Score*)y)->score) return -1;
    return 0;
    });
}

int Table::CellRating::getNum(int pos) const {
    return rating[pos].num;
}
