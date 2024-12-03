// --------------------------------------------------------
// Author: ERRA3774
// 
// License: DWETFUW License
// --------------------------------------------------------

#pragma once

#include "lglib.h"

INTERNAL const char* DAY2_INPUT = "res/2024/day2-input.txt";
INTERNAL const char* DAY2_TEST = "res/2024/day2-test.txt";

INLINE int Abs(int x) {
    return x < 0 ? -x : x;
}

INLINE bool IsMonotonic(int x0, int x1, bool shouldAscend) {
    return (x0 < x1 && shouldAscend) || (x0 > x1 && !shouldAscend);
}

// a < x < b
INLINE bool IsInOpenInterval(int x, int a, int b) {
    return (a < x) && (x < b);
}

// a <= x <= b
INLINE bool IsInClosedInterval(int x, int a, int b) {
    return (a <= x) && (x <= b);
}

INLINE std::vector<int> StringToArray(const char* str) {
    std::vector<int> vec;

    char copy[MAX_STRING_LENGTH];
    snprintf(copy, MAX_STRING_LENGTH, str);
    for (char* tok = strtok(copy, " "); tok != nullptr; tok = strtok(nullptr, " ")) {
        vec.push_back(atoi(tok));
    }

    return vec;
}

INLINE bool IsSafeReport(const char* str) {
    char* tok;
    int curr;
    int next;
    bool shouldAscend = true;
    int diff;

    char copy[MAX_STRING_LENGTH];
    snprintf(copy, MAX_STRING_LENGTH, str);

    tok = strtok(copy, " ");
    curr = atoi(tok);

    tok = strtok(nullptr, " ");
    next = atoi(tok);

    diff = next - curr;
    if (diff < 0) {
        shouldAscend = false;
    }

    if (!IsInClosedInterval(Abs(diff), 1, 3)) {
        return false;
    }

    curr = next;

    for (; (tok = strtok(nullptr, " ")) != nullptr; ) {
        next = atoi(tok);

        diff = next - curr;
        bool inInterval = IsInClosedInterval(Abs(diff), 1, 3);
        bool monotonic = IsMonotonic(curr, next, shouldAscend);

        if (!monotonic || !inInterval) {
            return false;
        }
        curr = next;
    }

    return true;
}

INLINE bool IsSafeEnoughReport(const char* str) {

    std::vector<int> vec = StringToArray(str);

    int tolerance = 1;

    for (int i = 0; i < vec.size() - 1; i++) {

    }

    return true;
}

INLINE int SafeReportsFromFile(const char* filename, int tolerance = 0) {

    FILE* file = fopen(filename, "r");
    if (!file) {
        LOG("Could not open file from path: %s", filename);
        return -1;
    }

    int sum = 0;
    char buf[MAX_STRING_LENGTH];
    for (int i = 0; fgets(buf, MAX_STRING_LENGTH, file); i++) {

        buf[strcspn(buf, "\n")] = 0;

        if (tolerance == 0 && IsSafeReport(buf) ||
            (tolerance > 0 && IsSafeEnoughReport(buf))) {
            ++sum;
        }
    }

    fclose(file);

    return sum;
}

INLINE int TestDay2Part1_2024() {
    int result = SafeReportsFromFile(DAY2_TEST);
    LOG("DAY 2 PART 1 TEST: %d", result);
    return result;
}

INLINE void Day2Part1_2024() {
    ASSERT(TestDay2Part1_2024() == 2);

    int result = SafeReportsFromFile(DAY2_INPUT);

    LOG("DAY 2 PART 1 RESULT: %d", result);
}

INLINE int TestDay2Part2_2024() {
    int result = SafeReportsFromFile(DAY2_TEST, 1);
    LOG("DAY 2 PART 2 TEST: %d", result);
    return result;
}

INLINE void Day2Part2_2024() {
    ASSERT(TestDay2Part2_2024());

    int result = SafeReportsFromFile(DAY2_INPUT, 1);

    LOG("DAY 2 PART 2 RESULT: %d", result);
}