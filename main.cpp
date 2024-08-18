#include "src/linked_list.hh"
#include <iostream>

#define NEXT cout << "\n\n\n"

using std::cout, std::flush;

int main() {
	LinkedList list;

	cout << "Inserting values: '10', '20'.\n";
	list.insert(10);
	list.insert(20);
	cout << list.formatStatus() << '\n';
	NEXT;

	cout << "Searching value '10'.\n";
	list.search(10);
	cout << list.getInfo() << '\n';
	cout << "Searching value '20'.\n";
	list.search(20);
	cout << list.getInfo() << '\n';
	NEXT;

	//cout << list.formatListOfElements();
	NEXT;

	cout << "Removing value '20'\n";
	list.remove(20);
	cout << list.getInfo() << '\n';
	NEXT;

	cout << list.formatListOfElements(true);
	NEXT;

	cout << list.formatStatus(true) << flush;
	NEXT;

	return 0;
}
