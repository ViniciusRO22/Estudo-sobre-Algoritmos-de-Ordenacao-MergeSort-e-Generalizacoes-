
#include "include/benchmark.hpp"

pair<double, size_t> benchmarkFunction(function<void()> func) {
    // Medição de tempo
    auto start = high_resolution_clock::now();
    
    // Medição de memória antes da execução
    struct rusage usage_before;
    getrusage(RUSAGE_SELF, &usage_before);
    
    func();  // Executa a função
    
    // Medição de memória depois da execução
    struct rusage usage_after;
    getrusage(RUSAGE_SELF, &usage_after);
    
    auto end = high_resolution_clock::now();
    
    // Cálculo da duração em segundos
    auto duration = duration_cast<nanoseconds>(end - start).count();
    double duration_sec = duration / 1e9;
    
    // Cálculo do uso máximo de memória (em bytes)
    size_t max_memory = usage_after.ru_maxrss - usage_before.ru_maxrss;
    
    // Em sistemas Linux, ru_maxrss está em KB; no macOS está em bytes
    #ifdef __linux__
        max_memory *= 1024;  // Converte KB para bytes
    #endif
    
    return {duration_sec, max_memory};
}