/**
 * @file frequency_strategy.hpp
 * @brief Frequency-based guess selection strategy
 */

#pragma once

#include "../interface/i_guess_strategy.hpp"
#include <cstdint>
#include <string_view>
#include <vector>

/**
 * @class FrequencyStrategy
 * @brief Digit frequency analysis-based guess selection strategy
 *
 * This strategy analyzes the frequency of digits in each position across all
 * possible numbers and selects guesses that best cover the most frequent
 * digits. It's particularly effective when the search space is large, and you
 * want to make guesses that are likely to hit common digit patterns.
 *
 * The strategy calculates a score based on how well a guess covers frequent
 * digits in their respective positions across the remaining possible numbers.
 */
class FrequencyStrategy final : public IGuessStrategy {
public:
  /**
   * @brief Default constructor
   */
  FrequencyStrategy() = default;

  /**
   * @brief Select the best guess using frequency analysis
   * @param possibleNumbers Vector of numbers still considered possible
   * @param history Reference to the guess history manager
   * @return The guess that best covers frequent digit patterns
   */
  [[nodiscard]] int32_t
  selectBestGuess(const std::vector<int32_t>& possibleNumbers,
                  const GuessHistoryManager& history) const noexcept override;

  /**
   * @brief Get the name of this strategy
   * @return String identifier for this strategy
   */
  [[nodiscard]] std::string_view getStrategyName() const noexcept override;
};
