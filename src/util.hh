// https://github.com/at-sso/StringTools/blob/master/src/strutil.hh#L268 blobl
#pragma once

#include <iosfwd>
#include <iostream>
#include <limits>

using std::cin;

/**
 * @brief Checks if the captured value from standard input is invalid.
 *
 * This function checks if the last input operation on `cin` failed
 * (e.g., due to non-numeric input). If it fails, it performs the following:
 *   - Clears the error flags from `cin` to allow further input.
 *   - Ignores the remaining invalid input in the stream up to the next newline.
 *
 * @param value An optional character to ignore. Default is an escape character (`\n`).
 * @param force Force ignoring input (discards valid input).
 * @return `true` if the captured value was invalid, `false` otherwise.
 */
bool isCapturedValueInvalid(char value = '\n', bool force = false) {
	// If `force` is enabled, ignore the captured value.
	if( force || cin.fail() ) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), value);
		return true;
	}
	return false;
}
