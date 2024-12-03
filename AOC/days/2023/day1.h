// --------------------------------------------------------
// Author: ERRA3774
// 
// License: DWETFUW License
// --------------------------------------------------------

#pragma once

#include "lglib.h"

const char* NumberStringTable[NUMBER_STRING_COUNT]{
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

INLINE int NumberFromLiteral(const char* str) {
    int res = -1;

    if (str == nullptr || strlen(str) < 3) {
        return -1;
    }

    for (int i = 0; i < NUMBER_STRING_COUNT; i++) {
        if (str[0] == NumberStringTable[i][0] && str[1] == NumberStringTable[i][1]) {
            return i;
        }
    }

    return res;
}

INTERNAL void Day1Part1_2023() {
    const char* filename = "res/2023/day1-input.txt";
    FILE* file = fopen(filename, "r");
    if (!file) {
        LOG("Could not open file from path: '%s'", filename);
        return;
    }

    int sum = 0;
    char buf[MAX_STRING_LENGTH];
    for (; fgets(buf, MAX_STRING_LENGTH, file) != nullptr;) {
        char* l = buf;
        char* r = buf + strlen(buf) - 1;

        int d1 = -1;
        int d2 = -1;

        for (; l <= r; ) {

            if (!IsDigit(*l)) {
                l++;
            }

            if (!IsDigit(*r)) {
                r--;
            }

            if (IsDigit(*l) && IsDigit(*r)) {
                d1 = (*l - '0');
                d2 = (*r - '0');
                break;
            }
        }
        sum += (d1 * 10 + d2);
    }

    fclose(file);
    LOG("DAY 1 PART 1 RESULT = %d", sum);
}


INTERNAL void Day1Part2_2023() {
    const char* filename = "res/2023/day1-input.txt";
    FILE* file = fopen(filename, "r");
    if (!file) {
        LOG("Could not open file from path: '%s'", filename);
        return;
    }

    int sum = 0;
    char buf[MAX_STRING_LENGTH];
    for (; fgets(buf, MAX_STRING_LENGTH, file) != nullptr;) {
        char* l = buf;
        char* r = buf + strlen(buf) - 1;

        int min = (int)strlen(buf) - 1;
        int max = 0;

        int d1 = -1;
        int d2 = -1;

        bool found = false;
        for (int i = 0; i < NUMBER_STRING_COUNT; i++) {
            int pos;
            char* first = strstr(buf, NumberStringTable[i]);
            if (first != nullptr) {
                found = true;
                pos = (int)(first - buf);

                if (pos < min) {
                    min = pos;
                }
            }

            char* last = nullptr;
            while (first != nullptr) {
                last = first;
                first = strstr(first + 1, NumberStringTable[i]);
            }

            if (last != nullptr) {
                found = true;
                pos = (int)(last - buf);

                if (pos > max) {
                    max = pos;
                }
            }
        }

        if (found) {
            d1 = NumberFromLiteral(buf + min);
            d2 = NumberFromLiteral(buf + max);

            for (; l < buf + min; l++) {
                if (IsDigit(*l)) {
                    d1 = *l - '0';
                    break;
                }
            }

            for (; r > buf + max; r--) {
                if (IsDigit(*r)) {
                    d2 = *r - '0';
                    break;
                }
            }
        }
        else {
            for (; l <= r; ) {

                if (!IsDigit(*l)) {
                    l++;
                }

                if (!IsDigit(*r)) {
                    r--;
                }

                if (IsDigit(*l) && IsDigit(*r)) {
                    d1 = (*l - '0');
                    d2 = (*r - '0');
                    break;
                }
            }
        }
        sum += (d1 * 10 + d2);
    }

    fclose(file);
    LOG("DAY 1 PART 2 RESULT = %d", sum);
}
