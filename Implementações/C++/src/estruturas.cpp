#include "include/estruturas.hpp"

using namespace std;

// ==================== LISTA LINEAR ====================
ListaLinear::ListaLinear(int cap) : size(0), capacity(cap) {
    data.resize(capacity);
}

void ListaLinear::insert(int value) {
    if (size < capacity) {
        data[size++] = value;
    }
}

int ListaLinear::get(int index) const {
    if (index >= 0 && index < size) {
        return data[index];
    }
    return -1;
}

int ListaLinear::getSize() const {
    return size;
}

void ListaLinear::clear() {
    size = 0;
}

vector<int> ListaLinear::toVector() const {
    return vector<int>(data.begin(), data.begin() + size);
}

void ListaLinear::fromVector(const vector<int>& vec) {
    clear();
    for (int val : vec) {
        insert(val);
    }
}

// ==================== LISTA DINÂMICA ====================
ListaDinamica::ListaDinamica() : head(nullptr), size(0) {}

ListaDinamica::~ListaDinamica() {
    clear();
}

void ListaDinamica::insert(int value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    size++;
}

int ListaDinamica::get(int index) const {
    if (index >= 0 && index < size) {
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }
    return -1;
}

int ListaDinamica::getSize() const {
    return size;
}

void ListaDinamica::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    size = 0;
}

vector<int> ListaDinamica::toVector() const {
    vector<int> result;
    Node* current = head;
    while (current != nullptr) {
        result.push_back(current->data);
        current = current->next;
    }
    return result;
}

void ListaDinamica::fromVector(const vector<int>& vec) {
    clear();
    for (int val : vec) {
        insert(val);
    }
}

// ==================== PILHA LINEAR ====================
PilhaLinear::PilhaLinear(int cap) : top(-1), capacity(cap) {
    data.resize(capacity);
}

void PilhaLinear::push(int value) {
    if (top < capacity - 1) {
        data[++top] = value;
    }
}

int PilhaLinear::pop() {
    if (top >= 0) {
        return data[top--];
    }
    return -1;
}

int PilhaLinear::peek() const {
    if (top >= 0) {
        return data[top];
    }
    return -1;
}

bool PilhaLinear::isEmpty() const {
    return top == -1;
}

int PilhaLinear::getSize() const {
    return top + 1;
}

void PilhaLinear::clear() {
    top = -1;
}

vector<int> PilhaLinear::toVector() const {
    vector<int> result;
    for (int i = 0; i <= top; i++) {
        result.push_back(data[i]);
    }
    return result;
}

void PilhaLinear::fromVector(const vector<int>& vec) {
    clear();
    for (int val : vec) {
        push(val);
    }
}

// ==================== PILHA DINÂMICA ====================
PilhaDinamica::PilhaDinamica() : top(nullptr), size(0) {}

PilhaDinamica::~PilhaDinamica() {
    clear();
}

void PilhaDinamica::push(int value) {
    Node* newNode = new Node(value);
    newNode->next = top;
    top = newNode;
    size++;
}

int PilhaDinamica::pop() {
    if (top != nullptr) {
        Node* temp = top;
        int value = temp->data;
        top = top->next;
        delete temp;
        size--;
        return value;
    }
    return -1;
}

int PilhaDinamica::peek() const {
    if (top != nullptr) {
        return top->data;
    }
    return -1;
}

bool PilhaDinamica::isEmpty() const {
    return top == nullptr;
}

int PilhaDinamica::getSize() const {
    return size;
}

void PilhaDinamica::clear() {
    while (top != nullptr) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
    size = 0;
}

std::vector<int> PilhaDinamica::toVector() const {
    std::vector<int> temp;
    Node* current = top;
    while (current != nullptr) {
        temp.push_back(current->data);
        current = current->next;
    }
    // Agora inverta para obter do fundo para o topo
    std::reverse(temp.begin(), temp.end());
    return temp;
}

void PilhaDinamica::fromVector(const vector<int>& vec) {
    clear();
    for (int val : vec) {
        push(val);
    }
}

// ==================== FILA LINEAR ====================
FilaLinear::FilaLinear(int cap) : front(0), rear(-1), size(0), capacity(cap) {
    data.resize(capacity);
}

void FilaLinear::enqueue(int value) {
    if (size < capacity) {
        rear = (rear + 1) % capacity;
        data[rear] = value;
        size++;
    }
}

int FilaLinear::dequeue() {
    if (size > 0) {
        int value = data[front];
        front = (front + 1) % capacity;
        size--;
        return value;
    }
    return -1;
}

int FilaLinear::getFront() const {
    if (size > 0) {
        return data[front];
    }
    return -1;
}

bool FilaLinear::isEmpty() const {
    return size == 0;
}

int FilaLinear::getSize() const {
    return size;
}

void FilaLinear::clear() {
    front = 0;
    rear = -1;
    size = 0;
}

vector<int> FilaLinear::toVector() const {
    vector<int> result;
    for (int i = 0; i < size; i++) {
        result.push_back(data[(front + i) % capacity]);
    }
    return result;
}

void FilaLinear::fromVector(const vector<int>& vec) {
    clear();
    for (int val : vec) {
        enqueue(val);
    }
}

// ==================== FILA DINÂMICA ====================
FilaDinamica::FilaDinamica() : front(nullptr), rear(nullptr), size(0) {}

FilaDinamica::~FilaDinamica() {
    clear();
}

void FilaDinamica::enqueue(int value) {
    Node* newNode = new Node(value);
    if (rear == nullptr) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    size++;
}

int FilaDinamica::dequeue() {
    if (front != nullptr) {
        Node* temp = front;
        int value = temp->data;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        size--;
        return value;
    }
    return -1;
}

int FilaDinamica::getFront() const {
    if (front != nullptr) {
        return front->data;
    }
    return -1;
}

bool FilaDinamica::isEmpty() const {
    return front == nullptr;
}

int FilaDinamica::getSize() const {
    return size;
}

void FilaDinamica::clear() {
    while (front != nullptr) {
        Node* temp = front;
        front = front->next;
        delete temp;
    }
    rear = nullptr;
    size = 0;
}

vector<int> FilaDinamica::toVector() const {
    vector<int> result;
    Node* current = front;
    while (current != nullptr) {
        result.push_back(current->data);
        current = current->next;
    }
    return result;
}

void FilaDinamica::fromVector(const vector<int>& vec) {
    clear();
    for (int val : vec) {
        enqueue(val);
    }
}