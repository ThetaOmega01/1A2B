/**
 * @file minimax_strategy.hpp
 * @brief Minimax-based guess selection strategy
 */

#pragma once

#include "../interface/i_guess_strategy.hpp"
#include "cache_manager.hpp"
#include "guess_history_manager.hpp"
#include <vector>

/**
 * @class MinimaxStrategy
 * @brief Worst-case optimization guess selection strategy
 *
 * This strategy uses the minimax principle to select guesses that minimize
 * the worst-case scenario. It calculates the maximum number of possibilities
 * that could remain after each potential guess and selects the guess that
 * minimizes this worst-case outcome.
 *
 * This approach is particularly effective in the endgame when you want to
 * guarantee optimal performance in the worst-case scenario.
 */
class MinimaxStrategy final : public IGuessStrategy {
public:
  /**
   * @brief Constructor with cache manager reference
   * @param cache Reference to the cache manager for storing minimax calc
   */
  explicit MinimaxStrategy(CacheManager<size_t>& cache);

  /**
   * @brief Select the best guess using minimax analysis
   * @param possibleNumbers Vector of numbers still considered possible
   * @param history Reference to the guess history manager
   * @return The guess that minimizes the worst-case remaining possibilities
   */
  [[nodiscard]] int32_t
  selectBestGuess(const std::vector<int32_t>& possibleNumbers,
                  const GuessHistoryManager& history) const override;

  /**
   * @brief Get the name of this strategy
   * @return String identifier for this strategy
   */
  [[nodiscard]] std::string_view getStrategyName() const override;

private:
  CacheManager<size_t>&
      m_cache; ///< Reference to cache manager for minimax calculations

  /**
   * @brief Calculate minimax score for a potential guess
   * @param guess The potential guess to evaluate
   * @param possibleNumbers Vector of numbers still considered possible
   * @return Maximum remaining possibilities in worst case (lower values are
   * better)
   */
  [[nodiscard]] size_t
  calculateMinimax(int32_t guess,
                   const std::vector<int32_t>& possibleNumbers) const;
};
