#pragma once

#include "pch.h"

INLINE bool IsDigit(char ch) {
    return ch <= '9' && ch >= '0';
}

INLINE void Println(const std::vector<int>& vec) {
    putchar('[');
    for (const int& v : vec) {
        v != vec.back() ? printf(" %d,", v) : printf(" %d ]\n", v);
    }
}

INLINE void _timeit(void(*f)(), const char* fname) {
    thread_local clock_t startTime = clock();

    f();

    thread_local clock_t endTime = clock();

    thread_local double cpuTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;

    LOG("Func %s :: CPU time %lf seconds", fname, cpuTime);
}

#define TIME_IT(f) _timeit(f, #f)

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