#pragma once

#include <cstdint>
#include <iosfwd>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

using std::cout;
using std::shared_ptr, std::make_shared;
using std::string, std::stringstream, std::to_string;

constexpr int16_t LIMIT = 30;
constexpr auto EMPTY_VALUE = nullptr;

/**
 * @struct Node
 * @brief Represents a node in a linked list.
 *
 * Each node contains an integer value (`mainData`) and a backup array (`backupData`),
 * along with a shared pointer to the next node in the list (`next`).
 */
struct Node {
	shared_ptr<int16_t> mainData[LIMIT];     /// Array to store data elements in the node
	shared_ptr<int16_t> backupData[LIMIT];   /// Backup array to store deleted data elements in the node
	int16_t size;						     /// Number of elements currently stored in the node
	shared_ptr<Node> next;				     /// Pointer to the next node in the list

	template <class T>
	static string addrsOf(const T& data) {
		stringstream ss;
		ss << data;
		return ss.str();
	}

	Node() : size(0), next(nullptr) {
		for( int16_t i = 0; i < LIMIT; ++i ) {
			mainData[i] = make_shared<int16_t>(0);
			backupData[i] = make_shared<int16_t>(0);
		}
	}
};

/**
 * @class LinkedList
 * @brief A simple implementation of a singly linked list.
 *
 * This class provides basic operations such as insertion, searching, deletion,
 * and printing of elements in a linked list. It also manages the list's state
 * and can provide information about its status.
 */
class LinkedList {
private:
	shared_ptr<Node> head;           /// Pointer to the first node in the list
	int16_t count;                   /// Number of elements in the list
	string outputInfo;               /// String used to store output information for debugging and status reports

	/**
	 * @brief Checks if a given value exceeds the maximum allowed value for an `int16_t`.
	 *
	 * @param value The value to check.
	 * @return true if the value exceeds `INT16_MAX`, false otherwise.
	 */
	bool isMax(const int16_t& value) {
		if( value >= INT16_MAX ) {
			outputInfo = "Error: The input value is beyond limits.";
			return true;
		}
		return false;
	}

public:
	/**
	 * @brief Constructs an empty `LinkedList`.
	 *
	 * Initializes the list with `head` set to `EMPTY_VALUE` and `count` set to 0.
	 */
	LinkedList() : head(EMPTY_VALUE), count(0), outputInfo("") {}

	/**
	 * @brief Retrieves the current information stored in the `outputInfo` stream.
	 *
	 * @return A string containing the information from `outputInfo`.
	 */
	string getInfo() const {
		return outputInfo;
	}

	/**
	 * @brief Checks if the list is full.
	 *
	 * @param message Optional message to append to the error information if the list is full.
	 * @return true if the list contains the maximum number of elements, false otherwise.
	 */
	bool isFull(const string& message = "") {
		if( count >= LIMIT ) {
			outputInfo = "Error: The list is full. " + message;
			return true;
		}
		return false;
	}

	/**
	 * @brief Checks if the list is empty.
	 *
	 * @param message Optional message to append to the error information if the list is empty.
	 * @return true if the list contains no elements, false otherwise.
	 */
	bool isEmpty(const string& message = "") {
		if( head == EMPTY_VALUE ) {
			outputInfo = "Error: The list is empty. " + message;
			return true;
		}
		return false;
	}

	/**
	 * @brief Resets all values in `mainData` and `backupData` arrays.
	 *
	 * If the list is empty, this method will do nothing.
	 */
	void reset() {
		if( isEmpty() ) return;

		auto& current = head;
		while( current != EMPTY_VALUE ) {
			for( int16_t i = 0; i < LIMIT; ++i ) {
				current->mainData[i] = make_shared<int16_t>(0);
				current->backupData[i] = make_shared<int16_t>(0);
			}
			current = current->next;
		}
	}

	/**
	 * @brief Inserts a new value at the beginning of the list.
	 *
	 * @param value The value to insert into the list.
	 *
	 * If the list is full or if the value exceeds `INT16_MAX`, the insertion will not occur.
	 */
	void insert(int16_t value) {
		if( isFull("Cannot insert more elements.") ) return;
		if( isMax(value) ) return;

		if( head == EMPTY_VALUE || head->size == LIMIT ) {
			auto newNode = make_shared<Node>();
			newNode->mainData[0] = make_shared<int16_t>(value);
			newNode->size = 1;
			newNode->next = head;
			head = newNode;
		} else {
			head->mainData[head->size++] = make_shared<int16_t>(value);
		}
		count++;
	}

	/**
	 * @brief Searches for a value in the list.
	 *
	 * @param value The value to search for.
	 * @return true if the value is found, false otherwise.
	 *
	 * If the value exceeds `INT16_MAX`, the search will not occur.
	 */
	bool search(int16_t value) {
		if( isMax(value) ) return false;

		auto& current = head;
		while( current != EMPTY_VALUE ) {
			for( int16_t i = 0; i < current->size; i++ ) {
				if( *( current->mainData[i] ) == value ) {
					outputInfo = "Value found at memory address: " + Node::addrsOf(current) + " at index: " + to_string(i) + ".";
					return true;
				}
			}
			current = current->next;
		}
		outputInfo = "Value not found.\n";
		return false;
	}

	/**
	 * @brief Removes a value from the list.
	 *
	 * @param value The value to remove.
	 *
	 * If the list is empty or if the value exceeds `INT16_MAX`, the removal will not occur.
	 */
	void remove(int16_t value) {
		if( isEmpty("Cannot remove any element.") ) return;
		if( isMax(value) ) return;

		auto& current = head;
		shared_ptr<Node> previous = EMPTY_VALUE;

		while( current != EMPTY_VALUE ) {
			for( int16_t i = 0; i < current->size; i++ ) {
				if( *( current->mainData[i] ) == value ) {
					// Move the deleted value to backupData
					current->backupData[i] = current->mainData[i];

					// Shift the rest of the elements
					for( int16_t j = i; j < current->size - 1; j++ ) {
						current->mainData[j] = current->mainData[j + 1];
					}

					current->mainData[current->size - 1] = make_shared<int16_t>(0);
					current->size--;
					count--;

					// Handle empty node
					if( current->size == 0 && previous != EMPTY_VALUE ) {
						previous->next = current->next;
					} else if( current->size == 0 && previous == EMPTY_VALUE ) {
						head = current->next;
					}

					outputInfo = "Element '" + to_string(value) + "' removed and backed up.\n";
					return;
				}
			}
			previous = current;
			current = current->next;
		}
		outputInfo = "Element not found.\n";
	}

	/**
	 * @brief Removes a value from the `backupData` array at a given index.
	 *
	 * @param index The index of the value to remove from `backupData`.
	 */
	void removeBackup(int16_t index) {
		if( isEmpty("Cannot remove any backup element.") ) return;

		auto& current = head;
		while( current != EMPTY_VALUE ) {
			if( index < current->size ) {
				// Shift elements to the left to remove the backup at the index
				for( int16_t i = index; i < current->size - 1; i++ ) {
					current->backupData[i] = current->backupData[i + 1];
				}

				// Clear the last position
				current->backupData[current->size - 1] = make_shared<int16_t>(0);
				outputInfo = "Backup element removed.\n";
				return;
			}
			current = current->next;
		}
		outputInfo = "Backup element not found.\n";
	}

	/**
	 * @brief Formats the elements of the list along with their memory addresses.
	 *
	 * @param showBackup Boolean to indicate whether to include `backupData` in the output.
	 * @return A string representing the elements in the list.
	 *
	 * If the list is empty, this method will not print anything.
	 */
	__declspec( deprecated )
	string formatListOfElements(bool showBackup = false) {
		if( isEmpty() ) return outputInfo;

		auto& current = head;
		outputInfo = "List elements:\n";
		while( current != EMPTY_VALUE ) {
			for( int16_t i = 0; i < current->size; i++ ) {
				// Added debugging output to check the values before and after formatting
				int16_t currentValue = *( current->mainData[i] );
				outputInfo += "Debug: Original value: " + to_string(currentValue) + "\n";

				// Safeguard to ensure we are only reading values
				outputInfo += "Data: " + to_string(currentValue) + " | Memory address: " + Node::addrsOf(current) + " at index: " + to_string(i) + "\n";

				if( showBackup ) {
					int16_t backupValue = *( current->backupData[i] );
					outputInfo += "Backup: " + to_string(backupValue) + " | Memory address: " + Node::addrsOf(current) + " at index: " + to_string(i) + "\n";
				}
			}
			current = current->next;
		}
		return outputInfo;
	}

	/**
	 * @brief Formats the status of the list, including the head pointer and availability.
	 *
	 * @param showBackup Boolean to indicate whether to include `backupData` in the output.
	 * @return A string representing the status of the list.
	 */
	string formatStatus(bool showBackup = false) {
		outputInfo = "List status:\n";
		outputInfo += "HEAD: " + Node::addrsOf(head) + "\n";
		outputInfo += "AVAILABLE: " + string(isFull() ? "No" : "Yes") + "\n";

		if( showBackup ) {
			outputInfo += "Backup Data:\n";
			auto& current = head;
			while( current != EMPTY_VALUE ) {
				for( int16_t i = 0; i < current->size; i++ ) {
					outputInfo += "Backup: " + to_string(*( current->backupData[i] )) + " | Memory address: " + Node::addrsOf(current) + " at index: " + to_string(i) + "\n";
				}
				current = current->next;
			}
		}

		return outputInfo;
	}
};
