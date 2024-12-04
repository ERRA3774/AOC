// --------------------------------------------------------
// Author: ERRA3774
// Status: Done
// License: DWETFUW License
// --------------------------------------------------------

#pragma once

#include "lglib.h"

enum ColorType {
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,

    COLOR_COUNT,
};

INTERNAL void Day2Part1_2023() {
    const char* filename = "res/2023/day2-input.txt";
    FILE* file = fopen(filename, "r");
    if (!file) {
        LOG("Could not open file from path: '%s'", filename);
        return;
    }

    int sum = 0;

    char buf[MAX_STRING_LENGTH];
    for (; fgets(buf, MAX_STRING_LENGTH, file) != nullptr; ) {
        bool valid = true;
        int gameCube[COLOR_COUNT] = {
            12, // RED 
            13, // GREEN
            14, // BLUE
        };
        char* tok = strtok(buf, " :,;");
        tok = strtok(nullptr, " :,;");
        int id = atoi(tok);

        while ((tok = strtok(nullptr, " ,;")) != nullptr) {
            int n = atoi(tok);
            tok = strtok(nullptr, " ,");

            char* r = nullptr;
            if (tok) {
                r = tok + strlen(tok) - 1;

                if (strstr(tok, "red") != nullptr && gameCube[COLOR_RED] < n ||
                    strstr(tok, "green") != nullptr && gameCube[COLOR_GREEN] < n ||
                    strstr(tok, "blue") != nullptr && gameCube[COLOR_BLUE] < n) {
                    valid = false;
                }

                if (r && *r == ';') {
                    // Finished the set in a game
                    continue;
                }
            }
        }

        if (!valid) {
            continue;
        }

        sum += id;
    }

    fclose(file);
    printf("DAY 2 PART 1 RESULT = %d\n", sum);
}

INTERNAL void Day2Part2_2023() {
    const char* filename = "res/2023/day2-input.txt";
    FILE* file = fopen(filename, "r");
    if (!file) {
        LOG("Could not open file from path: '%s'", filename);
        return;
    }

    int sum = 0;

    char buf[MAX_STRING_LENGTH];
    for (; fgets(buf, MAX_STRING_LENGTH, file) != nullptr;) {
        int minMax[COLOR_COUNT] = { 0 };
        char* tok = strtok(buf, " :,;");
        tok = strtok(nullptr, " :,;");
        int id = atoi(tok);

        for (; (tok = strtok(nullptr, " ,;")) != nullptr;) {
            int n = atoi(tok);
            tok = strtok(nullptr, " ,");

            char* r = nullptr;
            if (tok) {
                r = tok + strlen(tok) - 1;

                if (strstr(tok, "red") != nullptr) {
                    if (n > minMax[COLOR_RED]) {
                        minMax[COLOR_RED] = n;
                    }
                }

                if (strstr(tok, "green") != nullptr) {
                    if (n > minMax[COLOR_GREEN]) {
                        minMax[COLOR_GREEN] = n;
                    }
                }

                if (strstr(tok, "blue") != nullptr) {
                    if (n > minMax[COLOR_BLUE]) {
                        minMax[COLOR_BLUE] = n;
                    }
                }

                if (r && (*r == ';' || *r == '\n')) {
                    // We don't care if a set or game ends
                }
            }
        }

        int power = 1;
        for (int i = 0; i < COLOR_COUNT; i++) {
            if (minMax[i] == 0) {
                minMax[i] = 1;
            }
            power *= minMax[i];
        }

        sum += power;
    }

    fclose(file);
    LOG("DAY 2 PART 2 RESULT = %d", sum);
}