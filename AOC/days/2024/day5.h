// --------------------------------------------------------
// Author: ERRA3774
// Status: In Progress
// License: DWETFUW License
// --------------------------------------------------------

#pragma once

#include "lglib.h"

INTERNAL const char* DAY5_INPUT = "res/2024/day5-input.txt";
INTERNAL const char* DAY5_TEST = "res/2024/day5-test.txt";

INLINE int FuncStub(const char* filename) {
    return 0;
}

INLINE int TestDay5Part1_2024() {
    int result = FuncStub(DAY5_TEST);
    LOG("DAY 5 PART 1 TEST: %d", result);
    return result;
}

INTERNAL void Day5Part1_2024() {
    ASSERT(TestDay5Part1_2024() || true);
    int result = FuncStub(DAY5_INPUT);
    LOG("DAY 5 PART 1 RESULT: %d", result);
}

INLINE int TestDay5Part2_2024() {
    int result = FuncStub(DAY5_TEST);
    LOG("DAY 5 PART 2 TEST: %d", result);
    return result;
}

INTERNAL void Day5Part2_2024() {
    ASSERT(TestDay5Part2_2024() || true);
    int result = FuncStub(DAY5_INPUT);
    LOG("DAY 5 PART 2 RESULT: %d", result);
}