#include <sys/resource.h>
#include <utility>
#include <chrono>
#include <functional>

using namespace std;
using namespace std::chrono;

pair<double, size_t> benchmarkFunction(function<void()> func);