#pragma once

#include <cstdint>
#include <iosfwd>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

using std::cout;
using std::shared_ptr, std::make_shared;
using std::string, std::stringstream;

constexpr int16_t LIST_LIMIT = 30;
constexpr auto EMPTY_VALUE = nullptr;

struct Node {
	int16_t data = 0;
	shared_ptr<Node> next;
};

class LinkedList {
private:
	shared_ptr<Node> head;
	int16_t count;
	stringstream outputInfo;

	void clearStream() {
		outputInfo.str("");
		outputInfo.clear();
	}

	bool isMax(const int16_t& value) {
		this->clearStream();
		if( value >= INT16_MAX ) {
			outputInfo << "Error: The input value is beyond limits.";
			return true;
		}
		return false;
	}

public:
	LinkedList() : head(EMPTY_VALUE), count(0) {}

	bool isFull() const {
		return count >= LIST_LIMIT;
	}

	bool isEmpty() const {
		return head == EMPTY_VALUE;
	}

	string getInfo() const {
		return outputInfo.str();
	}

	void insert(int16_t value) {
		if( isFull() ) {
			outputInfo << "Error: The list is full. Cannot insert more elements.\n";
			return;
		}

		if( isMax(value) ) return;

		auto newNode = make_shared<Node>();
		newNode->data = value;
		newNode->next = head;
		head = newNode;
		count++;
	}

	bool search(int16_t value) {
		if( isMax(value) ) return;

		auto& current = head;
		while( current != EMPTY_VALUE ) {
			if( current->data == value ) {
				outputInfo << "Value found at memory address: " << current << ".";
				return true;
			}
			current = current->next;
		}
		outputInfo << "Value not found.\n";
		return false;
	}

	void remove(int16_t value) {
		if( isEmpty() ) {
			outputInfo << "Error: The list is empty. Cannot remove any element.\n";
			return;
		}

		if( isMax(value) ) return;

		auto& current = head;
		shared_ptr<Node> previous = EMPTY_VALUE;

		while( current != EMPTY_VALUE ) {
			if( current->data == value ) {
				// The node to be deleted is the first one
				if( previous == EMPTY_VALUE )
					head = current->next;
				// The node to be deleted is not the first one
				else
					previous->next = current->next;
				outputInfo << "Element removed.\n";
				count--;
				return;
			}
			previous = current;
			current = current->next;
		}

		outputInfo << "Element not found.\n";
	}

	void print() {
		if( isEmpty() ) {
			outputInfo << "The list is empty.\n";
			return;
		}

		auto& current = head;
		outputInfo << "List elements:\n";
		while( current != EMPTY_VALUE ) {
			outputInfo << "Data: " + current->data << " | Memory address: " << current << "\n";
			current = current->next;
		}
	}

	void printStatus() {
		outputInfo << "List status:\n";
		outputInfo << "HEAD: " << head << "\n";
		outputInfo << "AVAILABLE: " << ( isFull() ? "No" : "Yes" ) << "\n";
	}
};
