#include "src/linked_list.hh"
#include "src/util.hh"
#include <cstdint>
#include <iostream>
#include <string>

using std::cout, std::cin, std::flush;
using std::string;
LinkedList list;

int main() {
	int16_t option = 0, value = 0;
	string extraMsg = "";
	bool mainLoop = true;

	auto inputHandler = [](int16_t& v) {
		while( true ) {
			cout << "\n> " << flush; cin >> v;
			if( isCapturedValueInvalid() ) {
				cout << "Captured value is invalid!"; continue;
			} else return true;
		}
		};

	do {
		// "Clears" the screen.
		cout << "\x1B[2J\x1B[H" << flush;

		cout << "Menu:\n"
			<< "1. Insert an element\n"
			<< "2. Search for an element\n"
			<< "3. Remove an element\n"
			<< "4. Display list status\n"
			<< "0. Exit\n"
			<< extraMsg
			<< list.getInfo();

		if( !inputHandler(option) ) continue;

		switch( option ) {
		case 0: cout << "bye bye!" << flush; mainLoop = false; break;
		default: extraMsg= "Invalid option. Please try again.\n"; continue;

		case 1:
			cout << "Enter a value to insert.";
			if( inputHandler(value) ) list.insert(value); break;

		case 2:
			cout << "Enter a value to search.";
			if( inputHandler(value) ) list.search(value); break;

		case 3:
			cout << "Enter a value to remove.";
			if( inputHandler(value) ) list.remove(value); break;

		case 4: list.formatListOfElements(); break;
		}
		extraMsg = "";
	} while( mainLoop );

	return 0;
}
