#include "src/linked_list.hh"
#include <iostream>

#define NEXT cout << "\n\n\n"

using std::cout, std::flush;

int main() {
    int option;
    int16_t value;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert an element\n";
        cout << "2. Search for an element\n";
        cout << "3. Remove an element\n";
        cout << "4. Display list status\n";
        cout << "5. Exit\n";
        cout << "Enter your option: ";
        std::cin >> option;

        switch (option) {
            case 1:
                cout << "Enter a value to insert: ";
                std::cin >> value;
                list.insert(value);
                cout << list.getInfo();
                break;

            case 2:
                cout << "Enter a value to search: ";
                std::cin >> value;
                if (list.search(value)) {
                    cout << list.getInfo();
                } else {
                    cout << list.getInfo();
                }
                break;

            case 3:
                cout << "Enter a value to remove: ";
                std::cin >> value;
                list.remove(value);
                cout << list.getInfo();
                break;

            case 4:
                cout << list.formatStatus();
                break;

            case 5:
                cout << "Exiting the program.\n";
                break;

            default:
                cout << "Invalid option. Please try again.\n";
                break;
        }
    } while (option != 5);

    return 0;
}

