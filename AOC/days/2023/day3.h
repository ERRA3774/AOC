// --------------------------------------------------------
// Author: ERRA3774
// 
// License: DWETFUW License
// --------------------------------------------------------

#pragma once

#include "lglib.h"

#define MAX_SYMBOLS_LENGTH 14
const char SymbolsTable[MAX_SYMBOLS_LENGTH] = "!@#$%^&*-+_=/";

INLINE bool IsSymbol(char ch) {
    for (int i = 0; i < MAX_SYMBOLS_LENGTH; i++) {
        if (ch == SymbolsTable[i]) {
            return true;
        }
    }
    return false;
}

INLINE bool TokenContainsSymbol(const char* str) {
    if (str == nullptr) {
        return false;
    }

    for (int i = 0; i < strlen(str); i++) {
        if (IsSymbol(str[i])) {
            return true;
        }
    }

    return false;
}

INLINE int GetNeighborNumber(size_t l, size_t r, const char* line) {
    int number = 0;

    while (l > 0 && IsDigit(line[l - 1])) {
        --l;
    }

    while (r < MAX_STRING_LENGTH && IsDigit(line[r])) {
        ++r;
    }

    if (l < r) {
        char buf[MAX_STRING_LENGTH] = { 0 };
        strncpy(buf, line + l, r - l);
        number = atoi(buf);
    }

    return number;
}

inline int ExtractNumber(const char* line, size_t pos) {
    if (!IsDigit(line[pos]) && !IsDigit(line[pos - 1]) && !IsDigit(line[pos + 1])) {
        return 0;
    }

    if (IsDigit(line[pos]) && (!IsDigit(line[pos - 1]) && !IsDigit(line[pos + 1]))) {
        return line[pos] - '0';
    }

    size_t l;
    size_t r;
    int number;
    bool addTwo = false;

    if (IsDigit(line[pos])) {
        l = r = pos;
    }
    else if (IsDigit(line[pos + 1]) && (!IsDigit(line[pos - 1]))) {
        l = r = pos + 1;
    }
    else if (IsDigit(line[pos - 1])) {
        l = r = pos - 1;
        if (IsDigit(line[pos + 1])) {
            addTwo = true;
        }
    }

    number = GetNeighborNumber(l, r, line);

    if (addTwo) {
        l = r = pos + 1;
        number += GetNeighborNumber(l, r, line);
    }

    return number;
}

INTERNAL void Day3Part1_2023() {
    const char* filename = "res/2023/day3-input.txt";
    FILE* file = fopen(filename, "r");
    if (!file) {
        LOG("Could not open file from path: '%s'", filename);
        return;
    }

    int sum = 0;
    char prevLine[MAX_STRING_LENGTH] = { 0 };
    char currLine[MAX_STRING_LENGTH] = { 0 };
    char nextLine[MAX_STRING_LENGTH] = { 0 };
    for (; fgets(nextLine, MAX_STRING_LENGTH, file) != nullptr;) {
        char copy[MAX_STRING_LENGTH] = { 0 };
        strncpy(copy, currLine, MAX_STRING_LENGTH);

        for (char* tok = strtok(copy, "."); tok != nullptr && *tok != '\n'; tok = strtok(nullptr, ".")) {
            if (TokenContainsSymbol(tok)) {
                size_t tokPos = tok - copy;
                while (!IsSymbol(copy[tokPos])) {
                    ++tokPos;
                }

                int prevLineNumber = ExtractNumber(prevLine, tokPos);
                int currLineNumber = ExtractNumber(currLine, tokPos);
                int nextLineNumber = ExtractNumber(nextLine, tokPos);
                sum += prevLineNumber + currLineNumber + nextLineNumber;
            }
        }
        strncpy(prevLine, currLine, MAX_STRING_LENGTH);
        strncpy(currLine, nextLine, MAX_STRING_LENGTH);
    }
    fclose(file);

    LOG("DAY 3 PART 1 RESULT = %d", sum);
}

INLINE int TestDay3Part2_2023() {
    const char* filename = "res/2023/day3-test.txt";
    FILE* file = fopen(filename, "r");
    if (!file) {
        LOG("Could not open file from path: '%s'", filename);
        return 0;
    }

    int sum = 0;
    char prevLine[MAX_STRING_LENGTH] = { 0 };
    char currLine[MAX_STRING_LENGTH] = { 0 };
    char nextLine[MAX_STRING_LENGTH] = { 0 };

    for (; fgets(nextLine, MAX_STRING_LENGTH, file) != nullptr;) {
        nextLine[strcspn(nextLine, "\n")] = 0;
        char copy[MAX_STRING_LENGTH];
        strncpy(copy, currLine, MAX_STRING_LENGTH);

        LOG("prevLine: %s", prevLine);
        LOG("currLine: %s", currLine);
        LOG("nextLine: %s", nextLine);
        LOG("-----------------------------");

        strncpy(prevLine, currLine, MAX_STRING_LENGTH);
        strncpy(currLine, nextLine, MAX_STRING_LENGTH);

    }
    fclose(file);

    LOG("DAY 3 PART 2 TEST = %d", sum);

    return sum;
}

INTERNAL void Day3Part2_2023() {

}