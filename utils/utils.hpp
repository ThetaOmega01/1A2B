/**
 * @file utils.hpp
 * @brief Utility functions and constants
 */

#pragma once

#include <array>
#include <cstdint>
#include <optional>

/**
 * @namespace utils
 * @brief Utility functions for number manipulation and validation
 */
namespace utils {

constexpr int32_t numberSize{4}; ///< Size of numbers in the game
constexpr int32_t minValidNumber{1000}; ///< Minimum valid number in the game
constexpr int32_t maxValidNumber{9876}; ///< Maximum valid number in the game

/**
 * @brief Integer power function
 * @param base The base number
 * @param exp The exponent (must be non-negative)
 * @return base raised to the power of exp
 */
int32_t intPow(int32_t base, int32_t exp);

/**
 * @brief Converts a number into an array of its digits
 * @param number The number to convert
 * @return Array containing the digits of the number
 */
std::array<int32_t, numberSize> getDigits(int32_t number);

/**
 * @brief Converts a number into an array of its digits (in-place version)
 * @param number The number to convert
 * @param digits Output array to store the digits
 */
void getDigits(int32_t number, std::array<int32_t, numberSize>& digits);

/**
 * @brief Validates if a guess is valid
 * @param guess The number to validate
 * @return Optional array of digits if valid, nullopt if invalid
 */
std::optional<std::array<int32_t, numberSize>> isValidGuess(int32_t guess);

} // namespace utils
