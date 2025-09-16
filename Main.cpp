#include <iostream>
#include <string>
#include "ArrayManager.h"

using namespace std;

static void printMenu() {
    cout << "menu \n";
    cout << "1) Find value \n";
    cout << "2) Modify value at given index\n";
    cout << "3) Add value to end of the array\n";
    cout << "4) Remove value at index\n";
    cout << "5) Print array\n";
    cout << "0) Exit\n";
    cout << "Choice: ";
}

static void Arraysize(const ArrayManager& rawarray) {
    cout << "Array size is " << rawarray.size();
    for (size_t i = 0; i < rawarray.size(); ++i) {
        cout << rawarray.at(i);
        if(i+1 != rawarray.size()) {
            cout << " ";
        }
    }
    cout << "\n";
}

int main() {
    //CS-303 Assignment 1
    //Comparing the given int array to a raw int array to make sure no errors

    string filename;
    cout << "Enter the filename: ";
    getline(cin, filename);

    ArrayManager rawarray(600);

    try {
        size_t n = rawarray.loadFromFile(filename);
        cout << "Amount of " << n << " integers that are in " << filename << "'.\n";
    } catch (const exception& ex) {
        cerr << "File was unable to be used: " << ex.what() << "\n";
        return 1;
    }

    int choice = -1;
    while (true) {
        printMenu();
        if (!(cin >> choice)) {
            cerr << "Invalid menu input. Exiting.\n";
            return 0;
        }
        if (choice == 0) break;

        switch (choice) {
        case 1: { // find
            cout << "Enter value to find: ";
            int a;
            cin >> a;
            int Index_location = rawarray.findIndex(a);
            if (Index_location >= 0) cout << "Found at index " << Index_location << "\n";
            else cout << "The number you are looking for is not in the index\n";
            break;
        }
        case 2: { // modify (with try/catch around user input path)
            try {
                cout << "Enter index to modify: ";
                long Temp_index_storage; // accept wide range before casting
                cin >> Temp_index_storage;
                if (!cin) throw invalid_argument("Non-numeric index.");
                if (Temp_index_storage < 0) throw out_of_range("Index must be non-negative.");

                size_t Index_location = static_cast<size_t>(Temp_index_storage);

                cout << "Enter new value: ";
                int number_value;
                cin >> number_value;
                if (!cin) throw invalid_argument("Non-numeric value.");

                ChangeResult res = rawarray.modifyAt(Index_location, number_value); // may throw out_of_range
                cout << "Modified index " << Index_location
                     << " old value was " << res.oldValue << ", new value is " << res.newValue << ")\n";
            } catch (const out_of_range& ex) {
                cerr << "The index isnt in the range " << ex.what() << "\n";
            } catch (const exception& ex) {
                cerr << "That input you are trying to modify cant be modified " << ex.what() << "\n";
            }
            break;
        }
        case 3: { // add (with try/catch around user input path)
            try {
                cout << "Enter value to append: ";
                int a;
                cin >> a;
                if (!cin) throw invalid_argument("Non-numeric value.");
                rawarray.pushBack(a); // may throw overflow_error if full
                cout << "Appended.\n";
            } catch (const overflow_error& ex) {
                cerr << "Array full: " << ex.what() << "\n";
            } catch (const exception& ex) {
                cerr << "unable to add that input: " << ex.what() << "\n";
            }
            break;
        }
        case 4: { // remove
            try {
                cout << "Enter index to remove: ";
                long Temp_index_storage;
                cin >> Temp_index_storage;
                if (!cin) throw invalid_argument("Non-numeric index.");
                if (Temp_index_storage < 0) throw out_of_range("Index must be positive.");
                size_t Index_location = static_cast<size_t>(Temp_index_storage);
                rawarray.removeAt(Index_location); // may throw out_of_range
                cout << "Removed index " << Index_location << ".\n";
            } catch (const exception& ex) {
                cerr << "Remove error: " << ex.what() << "\n";
            }
            break;
        }
        case 5: { // print
            try {
                Arraysize(rawarray); // at() is bounds-checked
            } catch (const exception& ex) {
                cerr << "unable to print " << ex.what() << "\n";
            }
            break;
        }
        default:
            cout << "Unknown choice.\n";
            break;
        }
    }

    cout << "Goodbye!\n";
    return 0;
}
