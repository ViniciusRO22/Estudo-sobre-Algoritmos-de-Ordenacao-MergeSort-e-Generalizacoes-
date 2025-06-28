#include "include/arquivo.hpp"

using namespace std;

vector<int> readCSV(const string& filePath, int maxRows) {
    vector<int> data;
    ifstream file(filePath);
    string line;
    bool firstLine = true;
    while (getline(file, line) && (int)data.size() < maxRows) {
        if (firstLine) { // pula o cabeçalho
            firstLine = false;
            continue;
        }
        stringstream ss(line);
        string userId, movieId, rating, timestamp;
        if (!getline(ss, userId, ',')) continue;
        if (!getline(ss, movieId, ',')) continue;
        // Se quiser usar userId:
        try {
            data.push_back(stoi(userId));
        } catch (const invalid_argument& e) {
            cerr << "Valor inválido: '" << userId << "'\n";
        }
        // Se quiser usar movieId, troque para:
        // data.push_back(stoi(movieId));
    }
    return data;
}

void saveCSV(const string& path, const vector<Result>& results) {
    ofstream out(path);
    out << "size,structure,representation,duration_s,mem_bytes\n";
    for (const auto& r : results) {
        out << r.size << "," << r.structure << "," << r.representation << ","
            << fixed << setprecision(6) << r.duration_s << "," << r.memory_bytes << "\n";
    }
}
