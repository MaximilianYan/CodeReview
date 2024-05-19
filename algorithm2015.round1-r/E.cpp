#include <iostream>
#include <vector>
#include <stdint.h>

using namespace std;

#define ERRMSG (cout << "ERR LINE " << __LINE__ << endl)

class Tree {
public:

    Tree();

    void operator+=(const int32_t& k);

    int32_t ask(const uint64_t& x, const uint64_t& y);

private:
    // vector<int32_t> kColumn;
    vector<uint64_t> sizeColumn;
};

// ------------------------------        MAIN        ------------------------------
// ------------------------------------        ------------------------------------
// --------------------------------------    --------------------------------------
// ---------------------------------------  ---------------------------------------
// --------------------------------------------------------------------------------

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int32_t m = 0;
    cin >> m;

    Tree tree;

    while (m--) {
        char in = 0;
        cin >> in;

        switch (in) {
        case '+': {
            int32_t k = 0;
            cin >> k;

            tree += k;

        } break;
        case '?': {
            uint64_t x = 0, y = 0;
            cin >> x >> y;

            cout << tree.ask(x, y) << endl;

        } break;
        default:
            ERRMSG;
        }
    }


    return 0;
}


// ------------------------------        TREE        ------------------------------
// ------------------------------------        ------------------------------------
// --------------------------------------    --------------------------------------
// ---------------------------------------  ---------------------------------------
// --------------------------------------------------------------------------------

Tree::Tree() : /*kColumn(1, 1),*/ sizeColumn(1, 1) {

}

void Tree::operator+=(const int32_t& k) {
    // kColumn.emplace_back(k);
    // sizeColumn.emplace_back(uint64_t(1) + (*sizeColumn.rbegin()) * uint64_t(k));
    sizeColumn.push_back(uint64_t(1) + (*sizeColumn.rbegin()) * uint64_t(k));
}

int32_t Tree::ask(const uint64_t& x, const uint64_t& y) {
    uint64_t xMod = x;
    uint64_t yMod = y;

    int32_t branchLevel = 0;    // уровень, на котором x и y оказались в разных поддеревьях
    bool branched = false;      // достигли ли мы уже этого уровня
    bool isParentChild = false; // флаг случая, когда одна из вершин находится в поддереве другой

    int32_t xLevel = 0; // уровень, на котором находится вершина x
    int32_t yLevel = 0; // уровень, на котором находится вершина y
    bool foundX = false; // нашли ли мы уже вершину x
    bool foundY = false; // нашли ли мы уже вершину y

    if (x == 1) {
        xLevel = sizeColumn.size() - 1;
        foundX = true;
        isParentChild = true;
    }
    if (y == 1) {
        yLevel = sizeColumn.size() - 1;
        foundY = true;
        if (isParentChild) return 0;
        isParentChild = true;
    }

    int32_t level; // текущий уровень поддерева
    for (level = sizeColumn.size() - 1; !(foundX && foundY); --level) {
        uint64_t xSubNum = 0;
        uint64_t ySubNum = 0;

        if (!foundX) xSubNum = (xMod - 2) / sizeColumn[level - 1];
        if (!foundY) ySubNum = (yMod - 2) / sizeColumn[level - 1];

        if (!foundX) xMod = xMod - 1 - xSubNum * sizeColumn[level - 1];
        if (!foundY) yMod = yMod - 1 - ySubNum * sizeColumn[level - 1];

        bool foundXNext = false;
        bool foundYNext = false;
        if (!foundX) foundXNext = (xMod == 1);
        if (!foundY) foundYNext = (yMod == 1);

        if (foundXNext) xLevel = level - 1;
        if (foundYNext) yLevel = level - 1;

        if (foundXNext && foundYNext) {
            if (!branched) {
                if (xSubNum == ySubNum) return 0;
                else return 2;
            }


        } else if (foundXNext || foundYNext) {

            if (xSubNum == ySubNum) {
                isParentChild = true;
            } else {
                branched = true;
                branchLevel = level;
            }
        } else {

            if (!branched) {
                if (xSubNum != ySubNum) {
                    branched = true;
                    branchLevel = level;
                }
            }

        }


        if (!foundX) foundX = foundXNext;
        if (!foundY) foundY = foundYNext;
    }

    if (isParentChild) return (xLevel > yLevel) ? (xLevel - yLevel) : (yLevel - xLevel);

    if (branched) return (branchLevel - xLevel + branchLevel - yLevel);

    ERRMSG;

    return 0;
}


// ------------------------------   FREE FUNCTIONS   ------------------------------
// ------------------------------------        ------------------------------------
// --------------------------------------    --------------------------------------
// ---------------------------------------  ---------------------------------------
// --------------------------------------------------------------------------------

