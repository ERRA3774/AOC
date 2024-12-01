// --------------------------------------------------------
// Author: ERRA3774
// 
// License: DWETFUW License
// --------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996) // _CTR_SECURE_NO_WARNINGS

#define INLINE inline
#define INTERNAL static
#define GLOBAL static

#define MAX_STRING_LENGTH 256
#define MAX_ARRAY_LENGTH 4096
#define NUMBER_STRING_COUNT 10

#define DEBUG_BREAK() __debugbreak()
#define ARRAY_LENGTH(arr) sizeof(arr) / sizeof(arr[0])

#define LOG(msg, ...) printf(msg"\n", ##__VA_ARGS__)

#define ASSERT(x) if (!(x)) { DEBUG_BREAK(); } 

// --------------------------------------------------------
// Constants

const char* DAY1_INPUT = "res/2024/day1-input.txt";
const char* DAY1_TEST = "res/2024/day1-test.txt";

const char* NumberStringTable[NUMBER_STRING_COUNT]{
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};
// --------------------------------------------------------


// --------------------------------------------------------
// Structs

enum ColorType {
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,

    COLOR_COUNT,
};

#define LOAD_FACTOR_THRESHOLD 1.0f
#define INIT_BUCKETS_SIZE 10

struct HashTable {

    struct Entry {
        int first;
        int second;
        Entry* next;
    };

    Entry** table;
    int buckets;
    int size;

    HashTable(int initBucketsSize = INIT_BUCKETS_SIZE) : buckets(initBucketsSize), size(0) {
        table = new Entry * [buckets];
        memset(table, 0, sizeof(Entry*) * buckets);
    }

    ~HashTable() {
        Clear();
        delete[] table;
    }

    void Insert(const int& key, int value) {
        if (_loadfactor() >= LOAD_FACTOR_THRESHOLD) {
            _rehash();
        }

        int hashValue = _hashfunc(key);
        Entry* curr = table[hashValue];
        for (; curr;) {
            if (curr->first == key) {
                curr->second = value;
                return;
            }
            curr = curr->next;
        }

        Entry* nwEntry = new Entry{ key, value, table[hashValue] };
        table[hashValue] = nwEntry;
        ++size;
    }

    int& operator[](const int& key) {
        if (_loadfactor() >= LOAD_FACTOR_THRESHOLD) {
            _rehash();
        }

        int hashValue = _hashfunc(key);
        Entry* curr = table[hashValue];
        for (; curr;) {
            if (curr->first == key) {
                return curr->second;
            }
            curr = curr->next;
        }

        Entry* nwEntry = new Entry{ key, 0, table[hashValue] };
        table[hashValue] = nwEntry;
        ++size;
        return nwEntry->second;
    }

    void Clear() {
        for (int i = 0; i < buckets; i++) {
            Entry* curr = table[i];
            for (; curr;) {
                Entry* toDelete = curr;
                curr = curr->next;
                delete toDelete;
            }
            table[i] = nullptr;
        }
        size = 0;
    }

    int _hashfunc(const int& key) const {
        return key % buckets;
    }

    float _loadfactor() const {
        return static_cast<float>(size) / buckets;
    }

    void _rehash() {
        int oldBuckets = buckets;
        Entry** oldTable = table;

        buckets *= 2;
        table = new Entry * [buckets];
        size = 0;

        memset(table, 0, sizeof(Entry*) * buckets);

        for (int i = 0; i < oldBuckets; i++) {
            Entry* curr = oldTable[i];
            for (; curr;) {
                Insert(curr->first, curr->second);
                Entry* toDelete = curr;
                curr = curr->next;
                delete toDelete;
            }
        }

        delete[] oldTable;
    }
};


// --------------------------------------------------------
// First Aid Functions

INLINE bool IsDigit(char ch) {
    return ch <= '9' && ch >= '0';
}

INLINE int GetNumber(const char* str) {
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

INLINE void _swap(int& a, int& b) {
    int t = a;
    a = b;
    b = t;
}

INLINE int _partition(int arr[], int begin, int end, bool reverse) {
    int piv = arr[end];
    int pos = begin - 1;

    for (int i = begin; i < end; i++) {
        if ((reverse && piv <= arr[i]) || (!reverse && piv >= arr[i])) {
            _swap(arr[++pos], arr[i]);
        }
    }
    _swap(arr[pos + 1], arr[end]);
    return pos + 1;
}

INLINE void _quicksort(int arr[], int begin, int end, bool reverse) {
    if (begin < end) {
        int piv = _partition(arr, begin, end, reverse);
        _quicksort(arr, begin, piv - 1, reverse);
        _quicksort(arr, piv + 1, end, reverse);
    }
}

INLINE void Sort(int arr[], int size, bool reverse = false) {
    _quicksort(arr, 0, size - 1, reverse);
}

// --------------------------------------------------------


// --------------------------------------------------------
// Poetry 

INTERNAL void Day1TwoDigitsSum(const char* filename) {
    int sum = 0;

    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("DAY1 :: Part 1 :: Could not open file from path = '%s'", filename);
        return;
    }

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
    printf("DAY1 :: Part 1:: Expected=55477, Actual=%d\n", sum);
}

INTERNAL void Day1TwoSpelledOutNumbersSum(const char* filename) {
    int sum = 0;

    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("DAY1 :: Part 2 :: Could not open file from path = '%s'", filename);
        return;
    }

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
            d1 = GetNumber(buf + min);
            d2 = GetNumber(buf + max);

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
    printf("DAY1 :: Part 2 :: Expected=54431, Actual=%d\n", sum);
}

INTERNAL void Day2SumOfValidGames(const char* filename) {
    int sum = 0;

    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("DAY2 :: Part 1 :: Could not open file from path = '%s'", filename);
        return;
    }

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

                if (strstr(tok, "red")   != nullptr && gameCube[COLOR_RED]   < n ||
                    strstr(tok, "green") != nullptr && gameCube[COLOR_GREEN] < n ||
                    strstr(tok, "blue")  != nullptr && gameCube[COLOR_BLUE]  < n) {
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
    printf("DAY2 :: Part 1 :: Expected=2879, Actual=%d\n", sum);
}

// --------------------------------------------------------

INTERNAL void Day2SumOfMinimumCubesForValidGames(const char* filename) {
    int sum = 0;
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("DAY2 :: Part 2 :: Could not open file from path = '%s'", filename);
        return;
    }

    char buf[MAX_STRING_LENGTH];
    for (; fgets(buf, MAX_STRING_LENGTH, file) != nullptr;) {
        char* tok = strtok(buf, " :,;");
        tok = strtok(nullptr, " :,;");


    }

    fclose(file);
    printf("DAY2 :: Part 2 :: Expected= , Actual=%d\n", sum);
}


// --------------------------------------------------------
// AOC Functions

GLOBAL int IdsSize = 0;
GLOBAL int LeftIds[MAX_ARRAY_LENGTH] = { 0 };
GLOBAL int RightIds[MAX_ARRAY_LENGTH] = { 0 };

INLINE void GetLocationIdsFromFile(const char* filename) {

    FILE* file = fopen(filename, "r");
    if (!file) {
        LOG("Could not open file from filename: %s", filename);
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

        LeftIds[i] = atoi(leftTok);
        RightIds[i] = atoi(rightTok);
    }
    IdsSize = i;

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

INLINE int TestDay1Part1() {
    GetLocationIdsFromFile(DAY1_TEST);
    int actual = TotalDistance(LeftIds, RightIds, IdsSize);

    return actual;
}

INLINE int TestDay1Part2() {
    GetLocationIdsFromFile(DAY1_TEST);
    int actual = SimilarityScore(LeftIds, RightIds, IdsSize);

    return actual;
}

INLINE void Day1Part1() {
    ASSERT(TestDay1Part1() == 11);

    GetLocationIdsFromFile(DAY1_INPUT);
    int actual = TotalDistance(LeftIds, RightIds, IdsSize);

    LOG("DAY1 PART 1 RESULT: %d", actual);
}

INLINE void Day1Part2() {
    ASSERT(TestDay1Part2() == 31);

    GetLocationIdsFromFile(DAY1_INPUT);
    int actual = SimilarityScore(LeftIds, RightIds, IdsSize);

    LOG("DAY1 PART 2 RESULT: %d", actual);
}

int main() {
    Day1Part1();
    Day1Part2();
}