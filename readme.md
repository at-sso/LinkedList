# LinkedList

This repository contains a simple implementation of a singly linked list in C++. The linked list supports basic operations like insertion, searching, deletion, and status display, with built-in error handling for edge cases.

# Index

- [LinkedList](#linkedlist)
- [Index](#index)
  - [Features](#features)
  - [How to Use](#how-to-use)
    - [Compilation](#compilation)
    - [Running the Application](#running-the-application)
    - [Menu Options](#menu-options)
    - [Example Usage](#example-usage)
    - [Error Handling](#error-handling)
    - [Extra: Input Validation](#extra-input-validation)
  - [File Structure](#file-structure)
  - [License](#license)

## Features

- **Insert:** Add a new element to the list.
- **Search:** Find an element in the list.
- **Remove:** Delete an element from the list and store it in a backup array.
- **Display:** Format and display the list and its status.
- **Error Handling:** The list handles cases like exceeding limits and dealing with empty or full lists gracefully.

## How to Use

### Compilation

To compile the project, ensure you have a C++ compiler installed. You can compile the program using the following command:

```bash
g++ -std=c++17 -I src main.cpp -o main.exe && ./main.exe
```

### Running the Application

After compiling, you can run the application:

```bash
./linked_list_app
```

### Menu Options

When you run the application, you will be presented with a menu with the following options:

1. **Insert an element:** Allows you to insert a new integer into the list.
2. **Search for an element:** Search for an element in the list by its value.
3. **Remove an element:** Remove an element from the list.
4. **Display list status:** Display the current status of the list, including the elements and their memory addresses.
5. **Exit:** Exit the application.

### Example Usage

```bash
Menu:
1. Insert an element
2. Search for an element
3. Remove an element
4. Display list status
0. Exit

> 1
Enter a value to insert.
> 25
Inserted value: '25'.

> 2
Enter a value to search.
> 25
Value found at memory address: 0x55f647e003f0 at index: 0 in node 0.

> 3
Enter a value to remove.
> 25
Element '25' removed and backed up.

> 4
List elements:
```

### Error Handling

The program has built-in error handling for invalid input, full lists, and values exceeding the `int16_t` limits. For example, if the input is invalid or non-numeric, the program will prompt you to try again.

### Extra: Input Validation

There's an additional function `isCapturedValueInvalid` that checks whether the input captured from `cin` is valid. If the input is invalid (e.g., non-numeric), it clears the error flags and ignores the invalid input. This function helps in ensuring that the program only processes valid numeric input.

**Usage Example:**

```cpp
bool isCapturedValueInvalid(char value = '\n', bool force = false) {
    if (force || cin.fail()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), value);
        return true;
    }
    return false;
}
```

This function is used in the `main.cpp` file to handle input errors smoothly.

## File Structure

```
.LinkedList/
├── main.cpp           # The main program that implements a simple user interface to interact with the linked list.
└── src/
    ├── linked_list.hh # Contains the `Node` struct and `LinkedList` class definitions.
    └── util.hh        # Input validation handler.
```

## License

This project is open-source and available under the [MIT License](./license).
