/**
 * @file search_space_manager.hpp
 * @brief Search space management for solver
 */

#pragma once

#include "../utils/utils.hpp"
#include <bitset>
#include <optional>
#include <vector>

/**
 * @class SearchSpaceManager
 * @brief Manages the set of possible numbers and constraint propagation
 *
 * This class encapsulates all operations related to maintaining and updating
 * the search space of possible secret numbers based on game constraints and
 * feedback from previous guesses.
 */
class SearchSpaceManager {
public:
  /**
   * @brief Constructor that initializes the search space with all valid numbers
   */
  explicit SearchSpaceManager();

  /**
   * @brief Eliminate a specific number from the search space
   * @param number The number to eliminate
   */
  void eliminateNumber(int32_t number);

  /**
   * @brief Apply constraint based on guess feedback to eliminate impossible
   * numbers
   * @param guess The guess that was made
   * @param aCount Number of correct digits in correct positions
   * @param bCount Number of correct digits in wrong positions
   */
  void applyConstraint(int32_t guess, int32_t aCount, int32_t bCount);

  /**
   * @brief Get all currently possible numbers as a vector
   * @return Vector containing all numbers still considered possible
   */
  [[nodiscard]] std::vector<int32_t> getPossibleNumbers() const;

  /**
   * @brief Get the count of remaining possible numbers
   * @return Number of possibilities still in the search space
   */
  [[nodiscard]] size_t getRemainingCount() const;

  /**
   * @brief Check if the search space is empty
   * @return true if no numbers remain possible, false otherwise
   */
  [[nodiscard]] bool isEmpty() const;

  /**
   * @brief Check if only one number remains possible
   * @return true if exactly one number remains, false otherwise
   */
  [[nodiscard]] bool hasOnlyOne() const;

  /**
   * @brief Get the single remaining number if only one exists
   * @return The remaining number if exactly one exists, nullopt otherwise
   */
  [[nodiscard]] std::optional<int32_t> getSingleRemaining() const;

private:
  std::bitset<utils::validNumberRange>
      m_possibleNumbers; ///< Bitset tracking possible numbers

  /**
   * @brief Convert bitset index to actual number
   * @param index Index in the bitset
   * @return Corresponding number
   */
  [[nodiscard]] static int32_t indexToNumber(size_t index);

  /**
   * @brief Convert number to bitset index
   * @param number The number to convert
   * @return Corresponding index in bitset
   */
  [[nodiscard]] static size_t numberToIndex(int32_t number);
};
