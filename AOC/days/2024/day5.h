// --------------------------------------------------------
// Author: ERRA3774
// Status: In Progress
// License: DWETFUW License
// --------------------------------------------------------

#pragma once

#include "lglib.h"

INTERNAL const char* DAY5_INPUT = "res/2024/day5-input.txt";
INTERNAL const char* DAY5_TEST = "res/2024/day5-test.txt";

INLINE std::tuple<std::vector<std::pair<int, int>>, std::vector<std::vector<int>>> ParsePageOrderingRulesAndUpdatesFileV1(const char* filename) {

    FILE* file = fopen(filename, "r");
    if (!file) {
        LOG("Could not open file from path: '%s'", filename);
        return {};
    }

    std::vector<std::pair<int, int>> rules;
    std::vector<std::vector<int>> updates;
    bool parsingRules = true;
    char buf[MAX_STRING_LENGTH];
    for (; fgets(buf, MAX_STRING_LENGTH, file); ) {

        buf[strcspn(buf, "\n")] = 0;

        if (strlen(buf) == 0) {
            parsingRules = false;
            continue;
        }

        if (parsingRules) {
            int l, r;
            char* tok = strtok(buf, "|");
            l = atoi(tok);
            tok = strtok(nullptr, "");
            r = atoi(tok);
            rules.emplace_back(l, r);
        }
        else {
            std::vector<int> update;
            int p;
            char* tok = strtok(buf, ",");
            while (tok != nullptr) {
                p = atoi(tok);
                update.emplace_back(p);
                tok = strtok(nullptr, ",");
            }
            updates.emplace_back(update);
        }
    }

    return {rules, updates};
}

INLINE std::tuple<std::vector<std::pair<int, int>>, std::vector<std::vector<int>>> ParsePageOrderingRulesAndUpdatesFileV2(const char* filename) {
    std::string buffer = GetFileStringBuffer(filename);
    std::istringstream stream(buffer);
    std::string line;
    std::vector<std::pair<int, int>> rules;
    std::vector<std::vector<int>> updates;
    bool parsingRules = true;

    while (std::getline(stream, line)) {
        if (line.empty()) {
            parsingRules = false;
            continue;
        }

        if (parsingRules) {
            std::istringstream ruleStream(line);
            int left, right;
            char discard;
            ruleStream >> left >> discard >> right;
            rules.emplace_back(left, right);
        }
        else {
            std::istringstream updateStream(line);
            std::vector<int> update;
            int page;
            char discard;
            while (updateStream >> page) {
                update.emplace_back(page);
                updateStream >> discard;
            }
            updates.emplace_back(update);
        }
    }
    
    return { rules, updates };
}

TIMEABLE CSTYLE() {
    const auto& o1 = ParsePageOrderingRulesAndUpdatesFileV1(DAY5_TEST);
    const auto& rules = std::get<0>(o1);
    const auto& updates = std::get<1>(o1);
    std::cout << "C Rules:" << std::endl; for (const auto& rule : rules) { std::cout << rule.first << " | " << rule.second << std::endl; }
    std::cout << "C Updates:" << std::endl; for (const auto& update : updates) { for (const auto& page : update) { std::cout << page << " "; } std::cout << std::endl; }
}

TIMEABLE CXXSTYLE() {
    const auto& o2 = ParsePageOrderingRulesAndUpdatesFileV2(DAY5_TEST);
    const auto& rules = std::get<0>(o2);
    const auto& updates = std::get<1>(o2);
    std::cout << "C++ Rules:" << std::endl; for (const auto& rule : rules) { std::cout << rule.first << " | " << rule.second << std::endl; }
    std::cout << "C++ Updates:" << std::endl; for (const auto& update : updates) { for (const auto& page : update) { std::cout << page << " "; } std::cout << std::endl; }
}

void ImplCheck() {
    TIME_IT(CSTYLE);
    TIME_IT(CXXSTYLE);
}

int FuncStub(const char* f) {
    return 1;
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