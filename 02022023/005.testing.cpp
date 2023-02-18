/*
Проверка решения судоку.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <Windows.h>

using namespace std;

#define NOMAIN
#include "D:\programming\SystemProgramming\Winter23\Algths\CodeReview\02022023\005.001.cpp"

void test(string command, Table ans) {
    for (int i = 0; i < 81; i += 5) {
        for (int j = 0; j < 5; ++j) {
            do {
                int tryI = rand() % 81;
                if (!ans.isCellFilled(tryI)) continue;
                ans.clearCell(tryI);
                break;
            } while (true);
        }

        ofstream test("test.txt", ios::out);
        test << ans << endl;
        test.close();

    }
}

int main() {
    ifstream file("in.txt");
    Table ans;
    file >> ans;
    file.close();

    test("build/AlgthsInt < test.txt", ans);
    test("build/AlgthsSim < test.txt", ans);

    return 0;
}
