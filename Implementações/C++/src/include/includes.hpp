#ifndef INCLUDES_HPP
#define INCLUDES_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <functional>
#include <iomanip>
#include <sys/resource.h>

using namespace std;
using namespace std::chrono;

struct Result {
    int size;
    string structure;
    string representation;
    double duration_s;
    size_t memory_bytes;
};

#endif