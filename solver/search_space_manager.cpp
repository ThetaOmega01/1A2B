/**
 * @file search_space_manager.cpp
 * @brief Implementation of SearchSpaceManager class
 */

#include "search_space_manager.hpp"
#include "../utils/utils.hpp"

SearchSpaceManager::SearchSpaceManager() {
  m_possibleNumbers.set(); // Initialize all numbers as possible

  // Clear invalid numbers
  for (size_t i{0}; i < utils::validNumberRange; ++i) {
    if (const int32_t number{indexToNumber(i)};
        !utils::isValidGuess(number).has_value()) {
      m_possibleNumbers.reset(i);
    }
  }
}

void SearchSpaceManager::eliminateNumber(const int32_t number) {
  if (utils::isValidGuess(number).has_value()) {
    m_possibleNumbers.reset(numberToIndex(number));
  }
}

void SearchSpaceManager::applyConstraint(const int32_t guess,
                                         const int32_t aCount,
                                         const int32_t bCount) {
  // Use constraint propagation to eliminate impossible numbers
  for (size_t i{0}; i < utils::validNumberRange; ++i) {
    if (!m_possibleNumbers.test(i)) {
      continue; // Already eliminated
    }

    const int32_t candidate{indexToNumber(i)};

    // If this candidate produce different feedback, eliminate it
    if (const auto [candidateA,
                    candidateB]{utils::calculateAB(guess, candidate)};
        candidateA != aCount || candidateB != bCount) {
      m_possibleNumbers.reset(i);
    }
  }
}

std::vector<int32_t> SearchSpaceManager::getPossibleNumbers() const {
  std::vector<int32_t> result;
  result.reserve(m_possibleNumbers.count());

  for (size_t i{0}; i < utils::validNumberRange; ++i) {
    if (m_possibleNumbers.test(i)) {
      result.push_back(indexToNumber(i));
    }
  }

  return result;
}

size_t SearchSpaceManager::getRemainingCount() const {
  return m_possibleNumbers.count();
}

bool SearchSpaceManager::isEmpty() const { return m_possibleNumbers.none(); }

bool SearchSpaceManager::hasOnlyOne() const {
  return m_possibleNumbers.count() == 1;
}

std::optional<int32_t> SearchSpaceManager::getSingleRemaining() const {
  if (!hasOnlyOne()) {
    return std::nullopt;
  }

  for (size_t i{0}; i < utils::validNumberRange; ++i) {
    if (m_possibleNumbers.test(i)) {
      return indexToNumber(i);
    }
  }

  return std::nullopt; // Should never reach here if hasOnlyOne() is true
}

int32_t SearchSpaceManager::indexToNumber(const size_t index) {
  return static_cast<int32_t>(index) + utils::minValidNumber;
}

size_t SearchSpaceManager::numberToIndex(const int32_t number) {
  return static_cast<size_t>(number - utils::minValidNumber);
}
