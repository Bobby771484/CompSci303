#ifndef array_manager_h
#define array_manager_h

#include <string>
#include <stdexcept>
#include <cstddef>

// Reports the value before it was changed and after it was changed
struct ChangeResult {
    int oldValue;
    int newValue;
};

// Managing the array of ints
class ArrayManager {
public:
    // Construct with a fixed initial capacity (defaults to 600)
    ArrayManager(std::size_t capacity = 600);
    ~ArrayManager();

    // File I/O
    // Reading how much whitespace their is to know how many integers their are and stopping at the end of the file
    // Returning how many integers were in the file itself.
    std::size_t loadFromFile(const std::string& filename);

    // looks thorugh the index returning a true value if found and returnin the value
    // if not then it returns a -1 value to indicate value was not found
    int findIndex(int value) const;

    // modifying the value through the index and if the value isnt a valid one then throws std::out_of_range on bad index
    //    Returns the old value then the new value 
    ChangeResult modifyAt(std::size_t index, int newValue);

    // adds to the very end of the given vector if its to full then throws a error to indicate 
    void pushBack(int value);

    // Remove the value by the index checking if the given index is valid and if not throwing a out of range error
    void removeAt(std::size_t index);

    // Debug helping 
    std::size_t size()     const { return _size; }
    std::size_t capacity() const { return _capacity; }
    int         at(std::size_t index) const; // bounds-checked access

private:
    int*        _data;
    std::size_t _size;
    std::size_t _capacity;
};

#endif // array_manager_h
