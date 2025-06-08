/**
 * @file i_guess_strategy.hpp
 * @brief Interface for guess selection strategies in the 1A2B solver
 */

#pragma once

#include <string>
#include <vector>

// Forward declaration
class GuessHistoryManager;

/**
 * @interface IGuessStrategy
 * @brief Abstract interface for guess selection strategies
 *
 * This interface defines the contract that all guess selection strategies must
 * implement.
 */
class IGuessStrategy {
public:
  /**
   * @brief Virtual destructor
   */
  virtual ~IGuessStrategy() = default;

  /**
   * @brief Select the best guess based on the current possible numbers and
   * history
   * @param possibleNumbers Vector of numbers still considered possible
   * @param history Reference to the guess history manager for accessing
   * previous guesses
   * @return The best guess according to this strategy
   */
  [[nodiscard]] virtual int32_t
  selectBestGuess(const std::vector<int32_t>& possibleNumbers,
                  const GuessHistoryManager& history) const = 0;

  /**
   * @brief Get the name of this strategy
   * @return A string identifying this strategy
   */
  [[nodiscard]] virtual std::string_view getStrategyName() const = 0;

protected:
  /**
   * @brief Protected default constructor to prevent direct instantiation
   */
  IGuessStrategy() = default;

  /**
   * @brief Protected copy constructor
   */
  IGuessStrategy(const IGuessStrategy&) = default;

  /**
   * @brief Protected copy assignment operator
   */
  IGuessStrategy& operator=(const IGuessStrategy&) = default;

  /**
   * @brief Protected move constructor
   */
  IGuessStrategy(IGuessStrategy&&) = default;

  /**
   * @brief Protected move assignment operator
   */
  IGuessStrategy& operator=(IGuessStrategy&&) = default;
};
