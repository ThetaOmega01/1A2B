/**
 * @file guess_history_manager.hpp
 * @brief Guess history management for the 1A2B solver
 */

#pragma once

#include <utility>
#include <vector>

/**
 * @class GuessHistoryManager
 * @brief Manages the history of guesses and feedback for the solver
 */
class GuessHistoryManager {
public:
  /**
   * @brief Default constructor
   */
  GuessHistoryManager() = default;

  /**
   * @brief Add a guess and its feedback to the history
   * @param guess The number that was guessed
   * @param aCount Number of correct digits in correct positions
   * @param bCount Number of correct digits in wrong positions
   */
  void addGuess(int32_t guess, int32_t aCount, int32_t bCount);

  /**
   * @brief Check if a number has already been guessed
   * @param number The number to check
   * @return true if the number has been guessed before, false otherwise
   */
  [[nodiscard]] bool hasBeenGuessed(int32_t number) const;

  /**
   * @brief Check if a number is consistent with all previous feedback
   * @param number The number to check for consistency
   * @return true if the number is consistent with all feedback, false otherwise
   */
  [[nodiscard]] bool isConsistentWithHistory(int32_t number) const;

  /**
   * @brief Get the total number of guesses made
   * @return Number of guesses in the history
   */
  [[nodiscard]] size_t getGuessCount() const;

  /**
   * @brief Get the list of all guesses made
   * @return Const reference to the vector of guesses
   */
  [[nodiscard]] const std::vector<int32_t>& getGuesses() const;

  /**
   * @brief Get the list of all feedback received
   * @return Const reference to the vector of feedback pairs (A count, B count)
   */
  [[nodiscard]] const std::vector<std::pair<int32_t, int32_t>>&
  getFeedback() const;

  /**
   * @brief Clear all history data
   */
  void clear();

  /**
   * @brief Check if the history is empty
   * @return true if no guesses have been made, false otherwise
   */
  [[nodiscard]] bool isEmpty() const;

private:
  std::vector<int32_t> m_guessHistory; ///< History of all guesses made
  std::vector<std::pair<int32_t, int32_t>>
      m_feedbackHistory; ///< History of feedback (A, B) pairs
};
