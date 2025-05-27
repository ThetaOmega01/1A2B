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

/**
 * @brief Integer power function
 * @param base The base number
 * @param exp The exponent (must be non-negative)
 * @return base raised to the power of exp
 */
constexpr int32_t intPow(int32_t base, int32_t exp);

/**
 * @brief Helper functions to generate min and max valid numbers
 * @param size The number of digits
 * @return A pair containing the minimum and maximum valid numbers
 *
 * The getMinValidNumber and getMaxValidNumber functions are derived from this
 */

[[nodiscard]] consteval std::pair<int32_t, int32_t>
getValidNumberRange(const int32_t size) {
  int32_t min{};
  int32_t max{};

  for (int32_t i{0}; i < size; ++i) {
    const int32_t maxDigit{9 - i % 5};
    max = max * 10 + maxDigit;
    min = min * 10 + (i == 0 ? 1 : 0);
  }

  return {min, max};
}

[[nodiscard]] consteval int32_t getMinValidNumber(const int32_t size) {
  return getValidNumberRange(size).first;
}

[[nodiscard]] consteval int32_t getMaxValidNumber(const int32_t size) {
  return getValidNumberRange(size).second;
}

// Constants for valid number range
inline constexpr int32_t minValidNumber{getMinValidNumber(numberSize)};
inline constexpr int32_t maxValidNumber{getMaxValidNumber(numberSize)};

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
