// --------------------------------------------------------
// Author: ERRA3774
// Status: Done
// License: DWETFUW License
// --------------------------------------------------------

#pragma once

#include "lglib.h"

INTERNAL const char* DAY3_INPUT = "res/2024/day3-input.txt";
INTERNAL const char* DAY3_TEST = "res/2024/day3-test.txt";

INLINE int Mul(int a, int b) {
    return a * b;
}

INLINE int Evaluate(const std::smatch& m) {

    if (m[1].str() == "mul") {
        return Mul(stoi(m[2].str()), stoi(m[3].str()));
    }

    return 0;
}

INLINE int RegexSumFromFile(const char* filename, bool checkIfEnabled = false) {

    std::string buffer;
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        file.open(filename);

        std::stringstream fs;
        fs << file.rdbuf();

        file.close();

        buffer = fs.str();
    }
    catch (std::ifstream::failure& e) {
        std::cerr << "FILE NOT READ SUCCESSFULLY " << e.what() << '\n';
    }

    std::string s = buffer;
    std::regex const rgx{ R"~((mul)[(](\d+)[,](\d+)[)])~" };
    std::smatch m;

    int sum = 0;

    for (; std::regex_search(s, m, rgx); ) {

        if (checkIfEnabled) {
            const char* start = s.c_str();
            const char* targetPtr = strstr(start, m[0].str().c_str());
            const char* disablePtr = strstr(start, "don't()");
            const char* enablePtr = strstr(start, "do()");

            size_t target = targetPtr ? targetPtr - start : -1;
            size_t disable = disablePtr ? disablePtr - start : -1;
            size_t enable = enablePtr ? enablePtr - start : -1;

            if (target == -1) {
                break;
            }

            if (disable != -1 && disable < target) {
                if (enable != -1) {
                    s = s.substr(enable); 
                    continue; 
                }
                else {
                    break; 
                }
            }
        }

        sum += Evaluate(m);
        s = m.suffix().str();
    }

    return sum;
}

INLINE int TestDay3Part1_2024() {
    int result = RegexSumFromFile(DAY3_TEST);
    LOG("DAY 3 PART 1 TEST: %d", result);
    return result;
}

INTERNAL void Day3Part1_2024() {
    ASSERT(TestDay3Part1_2024() == 161);
    int result = RegexSumFromFile(DAY3_INPUT);
    LOG("DAY 3 PART 1 RESULT: %d", result);
}

INLINE int TestDay3Part2_2024() {
    int result = RegexSumFromFile(DAY3_TEST, true);
    LOG("DAY 3 PART 2 TEST: %d", result);
    return result;
}

INTERNAL void Day3Part2_2024() {
    ASSERT(TestDay3Part2_2024() == 48);
    int result = RegexSumFromFile(DAY3_INPUT, true);
    LOG("DAY 3 PART 2 RESULT: %d", result);
}