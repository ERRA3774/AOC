// --------------------------------------------------------
// Author: ERRA3774
// Status: Done
// License: DWETFUW License
// --------------------------------------------------------

#pragma once

#include "lglib.h"

INTERNAL const char* DAY4_INPUT = "res/2024/day4-input.txt";
INTERNAL const char* DAY4_TEST = "res/2024/day4-test.txt";

INLINE std::string GetFileStringBuffer(const char* filename) {
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

    return buffer;
}

INLINE int WordCountXMAS(const char* filename) {

    std::string s = GetFileStringBuffer(filename);

    int dimens = (int)s.find('\n');
    int sum = 0;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'X') {

            if (i > 2) {

                if (s[i - 1] == 'M' && s[i - 2] == 'A' && s[i - 3] == 'S') {
                    ++sum;
                    //LOG("ll = %c%c%c%c", s[i], s[i - 1], s[i - 2], s[i - 3]);
                }

            }

            if (i < s.size() - 3) {

                if (s[i + 1] == 'M' && s[i + 2] == 'A' && s[i + 3] == 'S') {
                    ++sum;
                    //LOG("rl = %c%c%c%c", s[i], s[i + 1], s[i + 2], s[i + 3]);
                }

            }

            if (i < s.size() - dimens * 3 - 3) {

                if (s[i + dimens] == 'M' && s[i + 2 * dimens] == 'A' && s[i + 3 * dimens] == 'S') {
                    ++sum;
                    //LOG("bld = %c%c%c%c", s[i], s[i + dimens], s[i + 2 * dimens], s[i + 3 * dimens]);
                }

                if (s[i + dimens + 1] == 'M' && s[i + 2 * dimens + 2] == 'A' && s[i + 3 * dimens + 3] == 'S') {
                    ++sum;
                    //LOG("dl = %c%c%c%c", s[i], s[i + dimens + 1], s[i + 2 * dimens + 2], s[i + 3 * dimens + 3]);
                }
            }

            if (i < s.size() - dimens * 3 - 3 - 3) {

                if (s[i + dimens + 2 * 1] == 'M' && s[i + 2 * dimens + 2 * 2] == 'A' && s[i + 3 * dimens + 2 * 3] == 'S') {
                    ++sum;
                    //LOG("brd = %c%c%c%c", s[i], s[i + dimens + 2 * 1], s[i + 2 * dimens + 2 * 2], s[i + 3 * dimens + 2 * 3]);
                }

            }

            if (i > dimens * 3) {

                if (s[i - dimens - 1] == 'M' && s[i - 2 * dimens - 2] == 'A' && s[i - 3 * dimens - 3] == 'S') {
                    ++sum;
                    //LOG("ul = %c%c%c%c", s[i], s[i - dimens - 1], s[i - 2 * dimens - 2], s[i - 3 * dimens - 3]);
                }

            }

            if (i > dimens * 3 + 3 + 2) {

                if (s[i - dimens - 2 * 1] == 'M' && s[i - 2 * dimens - 2 * 2] == 'A' && s[i - 3 * dimens - 2 * 3] == 'S') {
                    ++sum;
                    //LOG("uld = %c%c%c%c", s[i], s[i - dimens - 2 * 1], s[i - 2 * dimens - 2 * 2], s[i - 3 * dimens - 2 * 3]);
                }


                if (i < s.size() - 3) {

                    if (s[i - dimens] == 'M' && s[i - 2 * dimens] == 'A' && s[i - 3 * dimens] == 'S') {
                        ++sum;
                        //LOG("urd = %c%c%c%c", s[i], s[i - dimens], s[i - 2 * dimens], s[i - 3 * dimens]);
                    }
                }
            }
        }
    }

    return sum;
}

INLINE int ShapeCountXMAS(const char* filename) {

    std::string s = GetFileStringBuffer(filename);

    int dimens = (int)s.find('\n');
    int sum = 0;

    for (int i = dimens + 2; i < s.size() - dimens - 1; i++) {
        if (s[i] == 'A') {

            //LOG("%c.%c\n.%c.\n%c.%c", s[i - dimens - 2], s[i - dimens], s[i], s[i + dimens], s[i + dimens + 2 * 1]);

            if (s[i - dimens - 2] == 'M' && s[i - dimens] == 'S' &&s[i + dimens] == 'M' && s[i + dimens + 2] == 'S') {
                ++sum;
            }

            if (s[i - dimens - 2] == 'M' && s[i - dimens] == 'M' && s[i + dimens] == 'S' && s[i + dimens + 2] == 'S') {
                ++sum;
            }

            if (s[i - dimens - 2] == 'S' && s[i - dimens] == 'M' && s[i + dimens] == 'S' && s[i + dimens + 2] == 'M') {
                ++sum;
            }

            if (s[i - dimens - 2] == 'S' && s[i - dimens] == 'S' && s[i + dimens] == 'M' && s[i + dimens + 2] == 'M') {
                ++sum;
            }
        }
    }

    return sum;
}

INLINE int TestDay4Part1_2024() {
    int result = WordCountXMAS(DAY4_TEST);
    LOG("DAY 4 PART 1 TEST: %d", result);
    return result;
}

INTERNAL void Day4Part1_2024() {
    ASSERT(TestDay4Part1_2024() == 18);
    int result = WordCountXMAS(DAY4_INPUT);
    LOG("DAY 4 PART 1 RESULT: %d", result);
}

INLINE int TestDay4Part2_2024() {
    int result = ShapeCountXMAS(DAY4_TEST);
    LOG("DAY 4 PART 2 TEST: %d", result);
    return result;
}

INTERNAL void Day4Part2_2024() {
    ASSERT(TestDay4Part2_2024() == 9);
    int result = ShapeCountXMAS(DAY4_INPUT);
    LOG("DAY 4 PART 2 RESULT: %d", result);
}