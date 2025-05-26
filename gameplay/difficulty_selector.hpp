/**
 * @file difficulty_selector.hpp
 * @brief Handles difficulty selection and attempt count management
 */

#pragma once

#include <cstdint>

/**
 * @enum DifficultyLevel
 * @brief Enumeration of predefined difficulty levels
 */
enum class DifficultyLevel {
  Easy,   ///< Easy difficulty (15 attempts)
  Medium, ///< Medium difficulty (10 attempts)
  Hard,   ///< Hard difficulty (7 attempts)
  Expert, ///< Expert difficulty (5 attempts)
  Custom  ///< Custom difficulty (user-defined attempts)
};

/**
 * @class DifficultySelector
 * @brief Manages difficulty selection/attempt counts
 */
class DifficultySelector {
public:
  /**
   * @brief Get maximum attempts
   * @return Number of maximum attempts
   */
  static int32_t getMaxAttempts();

  /**
   * @brief Convert difficulty level to attempt count
   * @param level The difficulty level
   * @return Number of attempts
   */
  static int32_t getAttemptsForDifficulty(DifficultyLevel level);

  /**
   * @brief Get custom attempt count from user
   * @return User-specified number of attempts (1-50)
   */
  static int32_t getCustomAttempts();

  /**
   * @brief Ask user if they want to play again
   * @return true if user wants to play again, false otherwise
   */
  static bool playAgain();

private:
  /**
   * @brief Display difficulty options
   */
  static void displayDifficultyOptions();

  /**
   * @brief Get difficulty choice from user input
   * @return Difficulty level
   */
  static DifficultyLevel getDifficultyChoice();
};
