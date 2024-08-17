#include "src/linked_list.hh"


int main() {
	LinkedList list;
	int option, value;

	switch( option ) {
	case 1:
		std::cout << "Enter a value to insert: ";
		std::cin >> value;
		list.insert(value);
		break;
	case 2:
		std::cout << "Enter a value to search: ";
		std::cin >> value;
		list.search(value);
		break;
	case 3:
		std::cout << "Enter a value to remove: ";
		std::cin >> value;
		list.remove(value);
		break;
	case 4:
		list.print();
		break;
	case 5:
		list.printStatus();
		break;
	case 6:
		std::cout << "Exiting...\n";
		break;
	default:
		std::cout << "Invalid option. Please try again.\n";
		break;
	}

	return 0;
}
