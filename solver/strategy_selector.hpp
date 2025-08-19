/**
 * @file strategy_selector.hpp
 * @brief Strategy selection and coordination for the 1A2B solver
 */

#pragma once

#include "../interface/i_guess_strategy.hpp"
#include "cache_manager.hpp"
#include "entropy_strategy.hpp"
#include "frequency_strategy.hpp"
#include "hybrid_strategy.hpp"
#include "minimax_strategy.hpp"
#include <cstdint>
#include <memory>
#include <string_view>
#include <vector>

/**
 * @class StrategySelector
 * @brief Factory and coordinator for guess selection strategies
 *
 * This class manages the creation, selection, and coordination of different
 * guess selection strategies. It provides a unified interface for strategy
 * management and handles the lifecycle of strategy instances and their
 * associated cache managers.
 *
 * The StrategySelector supports dynamic strategy switching and maintains
 * compatibility with the existing GuessStrategy enum for backward
 * compatibility.
 */
class StrategySelector {
public:
  /**
   * @brief Strategy types supported by the selector
   *
   * This enum maintains compatibility with HeuristicSolver::GuessStrategy
   * for seamless integration with existing code.
   */
  enum class StrategyType {
    entropyBased,   ///< Maximize information gain using entropy
    miniMax,        ///< Minimize worst-case remaining possibilities
    frequencyBased, ///< Use digit frequency analysis
    hybrid          ///< Combine multiple strategies adaptively
  };

  /**
   * @brief Constructor with default strategy selection
   * @param defaultStrategy The initial strategy to use (default: hybrid)
   */
  explicit StrategySelector(
      StrategyType defaultStrategy = StrategyType::hybrid);

  /**
   * @brief Select the best guess using the current strategy
   * @param possibleNumbers Vector of numbers still considered possible
   * @param history Reference to the guess history manager
   * @return The best guess according to the current strategy
   */
  [[nodiscard]] int32_t selectGuess(const std::vector<int32_t>& possibleNumbers,
                                    const GuessHistoryManager& history) const;

  /**
   * @brief Set the current strategy
   * @param strategy The strategy type to switch to
   */
  void setStrategy(StrategyType strategy);

  /**
   * @brief Get the current strategy type
   * @return The currently selected strategy type
   */
  [[nodiscard]] StrategyType getStrategy() const;

  /**
   * @brief Get the name of the current strategy
   * @return Human-readable name of the current strategy
   */
  [[nodiscard]] std::string_view getCurrentStrategyName() const;

  /**
   * @brief Get the name of a specific strategy type
   * @param strategy The strategy type to get the name for
   * @return Human-readable name of the specified strategy
   */
  [[nodiscard]] static std::string_view getStrategyName(StrategyType strategy);

  /**
   * @brief Clear all strategy caches
   *
   * This should be called when the search space changes significantly
   * to ensure cache consistency.
   */
  void clearCaches();

private:
  StrategyType m_currentStrategy; ///< Currently selected strategy type

  // Cache managers for performance optimization
  CacheManager<double> m_entropyCache; ///< Cache for entropy calculations
  CacheManager<size_t> m_minimaxCache; ///< Cache for minimax calculations

  // Strategy instances
  std::unique_ptr<EntropyStrategy>
      m_entropyStrategy; ///< Entropy-based strategy
  std::unique_ptr<MinimaxStrategy> m_minimaxStrategy; ///< Minimax strategy
  std::unique_ptr<FrequencyStrategy>
      m_frequencyStrategy; ///< Frequency-based strategy
  std::unique_ptr<HybridStrategy> m_hybridStrategy; ///< Hybrid strategy

  /**
   * @brief Initialize all strategy instances
   *
   * Creates and configures all strategy objects with their dependencies.
   */
  void initializeStrategies();

  /**
   * @brief Get the current strategy instance
   * @return Reference to the currently selected strategy
   */
  [[nodiscard]] const IGuessStrategy& getCurrentStrategy() const;
};
