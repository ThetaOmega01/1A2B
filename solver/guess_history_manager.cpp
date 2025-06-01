/**
 * @file guess_history_manager.cpp
 * @brief Implementation of GuessHistoryManager class
 */

#include "guess_history_manager.hpp"
#include "../utils/utils.hpp"
#include <algorithm>
#include <ranges>

void GuessHistoryManager::addGuess(int32_t guess, int32_t aCount,
                                   int32_t bCount) {
  m_guessHistory.emplace_back(guess);
  m_feedbackHistory.emplace_back(aCount, bCount);
}

bool GuessHistoryManager::hasBeenGuessed(const int32_t number) const {
  return std::ranges::find(m_guessHistory, number) != m_guessHistory.end();
}

bool GuessHistoryManager::isConsistentWithHistory(const int32_t number) const {
  // Check consistency with all previous guesses and their feedback
  return std::ranges::all_of(
      // Pair each guess with its feedback
      std::views::zip(m_guessHistory, m_feedbackHistory),
      // Check if the feedback matches the expected A and B counts for the
      // number
      [number](const auto& pair) {
        const auto& [guess, feedback]{pair};
        const auto [expectedA, expectedB]{feedback};
        const auto [actualA, actualB]{utils::calculateAB(guess, number)};
        return expectedA == actualA && expectedB == actualB;
      });
}

size_t GuessHistoryManager::getGuessCount() const {
  return m_guessHistory.size();
}

const std::vector<int32_t>& GuessHistoryManager::getGuesses() const {
  return m_guessHistory;
}

const std::vector<std::pair<int32_t, int32_t>>&
GuessHistoryManager::getFeedback() const {
  return m_feedbackHistory;
}

void GuessHistoryManager::clear() {
  m_guessHistory.clear();
  m_feedbackHistory.clear();
}

bool GuessHistoryManager::isEmpty() const { return m_guessHistory.empty(); }
