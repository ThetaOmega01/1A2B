/**
 * @file minimax_strategy.cpp
 * @brief Implementation of MinimaxStrategy class
 */

#include "minimax_strategy.hpp"
#include "../utils/utils.hpp"
#include <algorithm>
#include <map>
#include <ranges>

MinimaxStrategy::MinimaxStrategy(CacheManager<size_t>& cache)
    : m_cache{cache} {}

int32_t
MinimaxStrategy::selectBestGuess(const std::vector<int32_t>& possibleNumbers,
                                 const GuessHistoryManager& history) const {

  if (possibleNumbers.empty()) {
    return utils::minValidNumber; // Fallback to a known valid number
  }

  // If only one possibility remains, return it
  if (possibleNumbers.size() == 1) {
    return possibleNumbers.at(0);
  }

  int32_t bestGuess{possibleNumbers.at(0)};
  size_t bestWorstCase{SIZE_MAX};

  // Consider all possible numbers as potential guesses
  for (size_t i{0}; i < utils::validNumberRange; ++i) {
    const int32_t candidate{static_cast<int32_t>(i) + utils::minValidNumber};
    if (!utils::isValidGuess(candidate).has_value()) {
      continue;
    }

    // Skip if we've already guessed this number
    if (history.hasBeenGuessed(candidate)) {
      continue;
    }

    if (const size_t worstCase{calculateMinimax(candidate, possibleNumbers)};
        worstCase < bestWorstCase) {
      bestWorstCase = worstCase;
      bestGuess = candidate;
    }
  }

  return bestGuess;
}

std::string_view MinimaxStrategy::getStrategyName() const { return "Minimax"; }

size_t MinimaxStrategy::calculateMinimax(
    const int32_t guess, const std::vector<int32_t>& possibleNumbers) const {

  // Check cache first
  if (const auto cachedValue{m_cache.get(guess)}; cachedValue.has_value()) {
    return cachedValue.value();
  }

  if (possibleNumbers.empty()) {
    return 0;
  }

  // Count frequency of each possible feedback
  std::map<std::pair<int32_t, int32_t>, size_t> feedbackCounts;

  for (const int32_t target : possibleNumbers) {
    const auto [aCount, bCount]{utils::calculateAB(guess, target)};
    ++feedbackCounts[{aCount, bCount}];
  }

  // Find the maximum count (worst case)
  size_t maxCount{0};
  for (const auto& count : feedbackCounts | std::views::values) {
    maxCount = std::max(maxCount, count);
  }

  // Cache the result
  m_cache.cache(guess, maxCount);
  return maxCount;
}
