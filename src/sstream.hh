#pragma once

#include <iosfwd>
#include <sstream>
#include <string>

using std::string, std::stringstream;

class StrStream {
private:
	stringstream ss;  // Underlying stringstream

public:
	/**
	 * @brief Overloaded '<<' operator.
	 * It first clears the stream and then appends new data to the
	 * existing content the stream.
	 *
	 * @param data Any
	 */
	template <class T>
	StrStream& operator<<(const T& data) {
		this->clear(); // Clears the stream
		ss << data;    // Append the new data
		return *this;  // Return the current object for chaining
	}

	/**
	 * @brief The actual overloaded '<<' operator.
	 * Appends new data to the existing content of the stream as normal.
	 *
	 * @param data Any
	 */
	template <class T>
	StrStream& operator+(const T& data) {
		ss << data;
		return *this;
	}

	// Get the string from the stream
	string str() const {
		return ss.str();
	}

	// Clear the stream (optional, might be needed).
	void clear() {
		ss.str("");
		ss.clear();
	}
};
