/**
 * @file input_validator.hpp
 * @brief Centralized input validation
 */

#pragma once

#include "../utils/utils.hpp"
#include <array>
#include <cstdint>
#include <string_view>

/**
 * @class InputValidator
 * @brief Centralized input validation and error handling
 */
class InputValidator {
public:
  /**
   * @brief Get a valid integer input within a range
   * @param min Minimum value (inclusive)
   * @param max Maximum value (inclusive)
   * @param errorMessage Message to display on invalid input
   * @param maxAttempts Maximum number of input attempts (default: 10)
   * @return Valid integer within the specified range
   * @throws std::runtime_error if max attempts exceeded
   */
  static int32_t getIntegerInRange(int32_t min, int32_t max,
                                   std::string_view errorMessage,
                                   uint32_t maxAttempts = 10);

  /**
   * @brief Get a valid yes/no choice from user
   * @param errorMessage Message to display on invalid input
   * @param maxAttempts Maximum number of input attempts allowed (default: 5)
   * @return true for 'y', false for 'n'
   * @throws std::runtime_error if max attempts exceeded
   */
  static bool getYesNoChoice(std::string_view errorMessage,
                             uint32_t maxAttempts = 5);

  /**
   * @brief Get a valid 4-digit guess from user
   * @param errorMessage Message to display on invalid input
   * @param maxAttempts Maximum number of input attempts allowed (default: 10)
   * @return Valid 4-digit number with unique digits, first digit non-zero
   * @throws std::runtime_error if max attempts exceeded
   */
  static int32_t getValidGuess(std::string_view errorMessage,
                               uint32_t maxAttempts = 10);

  /**
   * @brief Get a valid 4-digit guess and return its digits
   * @param errorMessage Message to display on invalid input
   * @param maxAttempts Maximum number of input attempts allowed (default: 10)
   * @return Array of digits for the valid guess
   * @throws std::runtime_error if max attempts exceeded
   */
  static std::array<int32_t, utils::numberSize>
  getValidGuessDigits(std::string_view errorMessage, uint32_t maxAttempts = 10);

private:
  /**
   * @brief Clear input stream after failed input
   */
  static void clearInputStream();

  /**
   * @brief Check if input stream has failed and clear if necessary
   * @return true if stream was in failed state
   */
  static bool handleStreamFailure();
};
