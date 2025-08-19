/**
 * @file hybrid_strategy.hpp
 * @brief Hybrid guess selection strategy combining multiple approaches
 */

#pragma once

#include "../interface/i_guess_strategy.hpp"
#include "entropy_strategy.hpp"
#include "frequency_strategy.hpp"
#include "guess_history_manager.hpp"
#include "minimax_strategy.hpp"
#include <cstdint>
#include <vector>

/**
 * @class HybridStrategy
 * @brief Multi-strategy combination
 * - Early game (< 2 guesses): Uses pure entropy for maximum information gain
 * - Mid-game (> 10 possibilities): Weighted combination (50% entropy, 30%
 * minimax, 20% frequency)
 * - End-game (≤ 10 possibilities): Uses pure minimax for optimal worst-case
 * performance
 */
class HybridStrategy : public IGuessStrategy {
public:
  /**
   * @brief Constructor with strategy references
   * @param entropyStrategy Reference to the entropy strategy
   * @param minimaxStrategy Reference to the minimax strategy
   * @param frequencyStrategy Reference to the frequency strategy
   */
  HybridStrategy(const EntropyStrategy& entropyStrategy,
                 const MinimaxStrategy& minimaxStrategy,
                 const FrequencyStrategy& frequencyStrategy);

  /**
   * @brief Select the best guess using hybrid analysis
   * @param possibleNumbers Vector of numbers still considered possible
   * @param history Reference to the guess history manager
   * @return The guess selected by the appropriate strategy for the current game
   * phase
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
  const EntropyStrategy& m_entropyStrategy; ///< Reference to entropy strategy
  const MinimaxStrategy& m_minimaxStrategy; ///< Reference to minimax strategy
  const FrequencyStrategy&
      m_frequencyStrategy; ///< Reference to frequency strategy

  /**
   * @brief Calculate hybrid score combining multiple strategies
   * @param guess The potential guess to evaluate
   * @param possibleNumbers Vector of numbers still considered possible
   * @param history Reference to the guess history manager
   * @return Combined score using weighted strategy results
   */
  [[nodiscard]] double
  calculateHybridScore(int32_t guess,
                       const std::vector<int32_t>& possibleNumbers,
                       const GuessHistoryManager& history) const;
};
