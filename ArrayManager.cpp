#include "ArrayManager.h"
#include <fstream>
#include <iostream>

using namespace std;

ArrayManager::ArrayManager(size_t capacity)
    : _data(nullptr), _size(0), _capacity(capacity)
{
    if (capacity == 0) _capacity = 1;
    _data = new int[capacity];  // raw array to use as a comparsion and storage
}

ArrayManager::~ArrayManager() {
    delete[] _data;
}

size_t ArrayManager::loadFromFile(const string& filename) {
    ifstream in(filename);
    if (!in) {
        throw runtime_error("Failed to open input file: " + filename);
    }

    int x;
    while (in >> x) {
        if (_size == _capacity) {
            // Stops if the given integer exceeds capactiy that is allowed
            throw overflow_error("Array capacity reached while reading file.");
        }
        _data[_size++] = x;
    }
    return _size;
}

int ArrayManager::findIndex(int value) const {
    for (size_t i = 0; i < _size; ++i) {
        if (_data[i] == value) return static_cast<int>(i);
    }
    return -1;
}

ChangeResult ArrayManager::modifyAt(size_t index, int newValue) {
    if (index >= _size) {
        throw out_of_range("modifyAt: index out of range");
    }
    int oldVal = _data[index];
    _data[index] = newValue;
    return ChangeResult{oldVal, newValue};
}

void ArrayManager::pushBack(int value) {
    if (_size == _capacity) {
        throw overflow_error("pushBack: array is full");
    }
    _data[_size++] = value;
}

void ArrayManager::removeAt(size_t index) {
    if (index >= _size) {
        throw out_of_range("removeAt: index out of range");
    }
    // Shifts each and evrey single index by the left once to make space.
    for (size_t i = index + 1; i < _size; ++i) {
        _data[i - 1] = _data[i];
    }
    --_size;
}

int ArrayManager::at(size_t index) const {
    if (index >= _size) {
        throw out_of_range("at: index out of range");
    }
    return _data[index];
}
