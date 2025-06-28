#ifndef ESTRUTURAS_HPP
#define ESTRUTURAS_HPP

#include <iostream>
#include <vector>
#include <algorithm>

// ==================== LISTA LINEAR ====================
class ListaLinear {
private:
    std::vector<int> data;
    int size;
    int capacity;

public:
    ListaLinear(int cap = 1000);
    void insert(int value);
    int get(int index) const;
    int getSize() const;
    void clear();
    std::vector<int> toVector() const;
    void fromVector(const std::vector<int>& vec);
};

// ==================== LISTA DINÂMICA ====================
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class ListaDinamica {
private:
    Node* head;
    int size;

public:
    ListaDinamica();
    ~ListaDinamica();
    void insert(int value);
    int get(int index) const;
    int getSize() const;
    void clear();
    std::vector<int> toVector() const;
    void fromVector(const std::vector<int>& vec);
};

// ==================== PILHA LINEAR ====================
class PilhaLinear {
private:
    std::vector<int> data;
    int top;
    int capacity;

public:
    PilhaLinear(int cap = 1000);
    void push(int value);
    int pop();
    int peek() const;
    bool isEmpty() const;
    int getSize() const;
    void clear();
    std::vector<int> toVector() const;
    void fromVector(const std::vector<int>& vec);
};

// ==================== PILHA DINÂMICA ====================
class PilhaDinamica {
private:
    Node* top;
    int size;

public:
    PilhaDinamica();
    ~PilhaDinamica();
    void push(int value);
    int pop();
    int peek() const;
    bool isEmpty() const;
    int getSize() const;
    void clear();
    std::vector<int> toVector() const;
    void fromVector(const std::vector<int>& vec);
};

// ==================== FILA LINEAR ====================
class FilaLinear {
private:
    std::vector<int> data;
    int front;
    int rear;
    int size;
    int capacity;

public:
    FilaLinear(int cap = 1000);
    void enqueue(int value);
    int dequeue();
    int getFront() const;
    bool isEmpty() const;
    int getSize() const;
    void clear();
    std::vector<int> toVector() const;
    void fromVector(const std::vector<int>& vec);
};

// ==================== FILA DINÂMICA ====================
class FilaDinamica {
private:
    Node* front;
    Node* rear;
    int size;

public:
    FilaDinamica();
    ~FilaDinamica();
    void enqueue(int value);
    int dequeue();
    int getFront() const;
    bool isEmpty() const;
    int getSize() const;
    void clear();
    std::vector<int> toVector() const;
    void fromVector(const std::vector<int>& vec);
};

#endif