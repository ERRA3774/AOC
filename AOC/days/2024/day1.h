// --------------------------------------------------------
// Author: ERRA3774
// 
// License: DWETFUW License
// --------------------------------------------------------

#pragma once

#include "../../lglib.h"

INTERNAL const char* DAY1_INPUT = "res/2024/day1-input.txt";
INTERNAL const char* DAY1_TEST = "res/2024/day1-test.txt";

GLOBAL int IdsSize = 0;
GLOBAL int LeftIds[MAX_ARRAY_LENGTH] = { 0 };
GLOBAL int RightIds[MAX_ARRAY_LENGTH] = { 0 };

INLINE void InitLocationIdsFromFile(const char* filename, int leftIds[], int rightIds[], int& idsSize) {

    FILE* file = fopen(filename, "r");
    if (!file) {
        LOG("Could not open file from path: '%s'", filename);
        return;
    }

    int i;
    char buf[MAX_STRING_LENGTH];
    for (i = 0; fgets(buf, MAX_STRING_LENGTH, file); i++) {

        buf[strcspn(buf, "\n")] = 0;

        char* tok = strtok(buf, " ");
        const char* leftTok = tok;
        tok = strtok(nullptr, " ");
        const char* rightTok = tok;

        leftIds[i] = atoi(leftTok);
        rightIds[i] = atoi(rightTok);
    }
    idsSize = i;

    fclose(file);
}

INLINE int TotalDistance(int leftArray[], int rightArray[], int size) {
    int distance = 0;

    Sort(leftArray, size);
    Sort(rightArray, size);

    for (int i = 0; i < size; i++) {
        distance += leftArray[i] > rightArray[i] ? leftArray[i] - rightArray[i] : rightArray[i] - leftArray[i];
    }

    return distance;
}

INLINE int SimilarityScore(int leftArray[], int rightArray[], int size) {
    int similarity = 0;

    HashTable scoremap;

    for (int i = 0; i < size; i++) {
        scoremap[rightArray[i]]++;
    }

    for (int i = 0; i < size; i++) {
        similarity += leftArray[i] * scoremap[leftArray[i]];
    }

    return similarity;
}

INLINE int TestDay1Part1_2024() {
    InitLocationIdsFromFile(DAY1_TEST, LeftIds, RightIds, IdsSize);
    int result = TotalDistance(LeftIds, RightIds, IdsSize);
    LOG("DAY 1 PART 1 TEST: %d", result);
    return result;
}

INTERNAL void Day1Part1_2024() {
    ASSERT(TestDay1Part1_2024() == 11);

    InitLocationIdsFromFile(DAY1_INPUT, LeftIds, RightIds, IdsSize);
    int result = TotalDistance(LeftIds, RightIds, IdsSize);

    LOG("DAY 1 PART 1 RESULT: %d", result);
}

INLINE int TestDay1Part2_2024() {
    InitLocationIdsFromFile(DAY1_TEST, LeftIds, RightIds, IdsSize);
    int result = SimilarityScore(LeftIds, RightIds, IdsSize);
    LOG("DAY 1 PART 2 TEST: %d", result);
    return result;
}

INTERNAL void Day1Part2_2024() {
    ASSERT(TestDay1Part2_2024() == 31);

    InitLocationIdsFromFile(DAY1_INPUT, LeftIds, RightIds, IdsSize);
    int result = SimilarityScore(LeftIds, RightIds, IdsSize);

    LOG("DAY 1 PART 2 RESULT: %d", result);
}
