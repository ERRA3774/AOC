#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <xmmintrin.h>

#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include <fstream>
#include <sstream>

#pragma warning(disable : 4996) // _CTR_SECURE_NO_WARNINGS
#pragma warning(disable : 6053) // Prior call to strncpy might not zero-terminate string
#pragma warning(disable : 6001) // Using unitialized memory

#define INLINE inline
#define INTERNAL static
#define GLOBAL static

#define MAX_STRING_LENGTH 256
#define MAX_ARRAY_LENGTH 1024
#define NUMBER_STRING_COUNT 10
#define ARRAY_SIZE 256

#define DEBUG_BREAK() __debugbreak()
#define ARRAY_LENGTH(arr) sizeof(arr) / sizeof(arr[0])

#define LOG(msg, ...) printf(msg"\n", ##__VA_ARGS__)

#define ASSERT(x) if (!(x)) { DEBUG_BREAK(); } 