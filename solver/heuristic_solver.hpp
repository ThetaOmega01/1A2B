#pragma once

#include "../interface/interface.hpp"
#include "guess_history_manager.hpp"
#include "search_space_manager.hpp"
#include "strategy_selector.hpp"
#include <optional>
#include <string_view>

/**
 * @class HeuristicSolver
 * @brief Heuristic solver
 */
class HeuristicSolver final : public ISolver {
public:
  /**
   * @brief Strategy for selecting the next guess
   */
  enum class GuessStrategy {
    entropyBased,
    miniMax,
    frequencyBased,
    hybrid
  };

  /**
   * @brief Constructor with strategy selection
   * @param strategy The initial strategy to use (default: hybrid)
   */
  explicit HeuristicSolver(GuessStrategy strategy = GuessStrategy::hybrid);

  // ISolver interface implementation
  std::optional<int32_t> nextGuess() override;
  void updateGuess(int32_t guess, int32_t aCount, int32_t bCount) override;
  [[nodiscard]] bool isSolved() const override;

  /**
   * @brief Get the number of remaining possible numbers
   * @return Count of numbers considered possible
   */
  [[nodiscard]] size_t getRemainingCount() const;

  /**
   * @brief Set the strategy
   * @param strategy The strategy to switch to
   */
  void setStrategy(GuessStrategy strategy);

  /**
   * @brief Get the current strategy
   * @return Current strategy type
   */
  [[nodiscard]] GuessStrategy getStrategy() const;

  /**
   * @brief Get the name of the current strategy
   * @return Name of the current strategy
   */
  [[nodiscard]] std::string_view getCurrentStrategyName() const;

  /**
   * @brief Get the name of a specific strategy type
   * @param strategy The strategy type to get the name for
   * @return Name of the specified strategy
   */
  [[nodiscard]] static std::string_view getStrategyName(GuessStrategy strategy);

private:
  SearchSpaceManager m_searchSpace; ///< Manages the set of possible numbers
  GuessHistoryManager m_history;    ///< Tracks guess history and feedback
  StrategySelector
      m_strategySelector; ///< Coordinates strategy selection and execution

  /**
   * @brief Convert GuessStrategy enum to StrategySelector::StrategyType
   * @param strategy The GuessStrategy enum value
   * @return Corresponding StrategySelector::StrategyType
   */
  [[nodiscard]] static StrategySelector::StrategyType
  convertStrategy(GuessStrategy strategy);

  /**
   * @brief Convert StrategySelector::StrategyType to GuessStrategy enum
   * @param strategy The StrategySelector::StrategyType value
   * @return Corresponding GuessStrategy enum
   */
  [[nodiscard]] static GuessStrategy
  convertStrategy(StrategySelector::StrategyType strategy);
};
