/**
 * @file entropy_strategy.hpp
 * @brief Entropy-based guess selection strategy
 */

#pragma once

#include "../interface/i_guess_strategy.hpp"
#include "cache_manager.hpp"
#include <cstdint>
#include <vector>

/**
 * @class EntropyStrategy
 * @brief Information theory-based guess selection strategy
 *
 * This strategy uses Shannon's entropy formula to select guesses that maximize
 * information gain. It calculates the entropy for each potential guess by
 * analyzing the distribution of possible feedback responses and selects the
 * guess that provides the most information to narrow down the search space.
 *
 * The entropy calculation uses the formula: H = -Σ(p * log2(p))
 * where p is the probability of each possible feedback response.
 */
class EntropyStrategy final : public IGuessStrategy {
public:
  /**
   * @brief Constructor with cache manager reference
   * @param cache Reference to the cache manager for storing entropy
   * calculations
   */
  explicit EntropyStrategy(CacheManager<double>& cache);

  /**
   * @brief Select the best guess using entropy-based analysis
   * @param possibleNumbers Vector of numbers still considered possible
   * @param history Reference to the guess history manager
   * @return The guess that maximizes information gain
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
  CacheManager<double>&
      m_cache; ///< Reference to cache manager for entropy calculations

  /**
   * @brief Calculate entropy (information gain) for a potential guess
   * @param guess The potential guess to evaluate
   * @param possibleNumbers Vector of numbers still considered possible
   * @return Entropy value (higher values indicate better information gain)
   */
  [[nodiscard]] double
  calculateEntropy(int32_t guess,
                   const std::vector<int32_t>& possibleNumbers) const;
};
