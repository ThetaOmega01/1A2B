/**
 * @file entropy_strategy.cpp
 * @brief Implementation of EntropyStrategy class
 */

#include "entropy_strategy.hpp"

#include "../utils/utils.hpp"
#include "guess_history_manager.hpp"
#include <cmath>
#include <map>
#include <ranges>

EntropyStrategy::EntropyStrategy(CacheManager<double>& cache)
    : m_cache{cache} {}

int32_t
EntropyStrategy::selectBestGuess(const std::vector<int32_t>& possibleNumbers,
                                 const GuessHistoryManager& history) const {

  if (possibleNumbers.empty()) {
    return utils::minValidNumber; // Fallback to a known valid number
  }

  // If only one possibility remains, return it
  if (possibleNumbers.size() == 1) {
    return possibleNumbers.at(0);
  }

  int32_t bestGuess{possibleNumbers.at(0)};
  double bestEntropy{-1.0};

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

    if (const double entropy{calculateEntropy(candidate, possibleNumbers)};
        entropy > bestEntropy) {
      bestEntropy = entropy;
      bestGuess = candidate;
    }
  }

  return bestGuess;
}

std::string_view EntropyStrategy::getStrategyName() const {
  return "Entropy-based";
}

double EntropyStrategy::calculateEntropy(
    const int32_t guess, const std::vector<int32_t>& possibleNumbers) const {

  // Check cache first
  if (const auto cachedValue{m_cache.get(guess)}; cachedValue.has_value()) {
    return cachedValue.value();
  }

  if (possibleNumbers.empty()) {
    return 0.0;
  }

  // Count frequency of each possible feedback
  std::map<std::pair<int32_t, int32_t>, size_t> feedbackCounts;

  for (const int32_t target : possibleNumbers) {
    const auto [aCount, bCount]{utils::calculateAB(guess, target)};
    ++feedbackCounts[{aCount, bCount}];
  }

  // Calculate entropy using Shannon's formula: H = -Σ(p * log2(p))
  double entropy{0.0};
  const auto totalCount{static_cast<double>(possibleNumbers.size())};

  for (const auto& count : feedbackCounts | std::views::values) {
    if (count > 0) {
      const double probability{static_cast<double>(count) / totalCount};
      entropy -= probability * std::log2(probability);
    }
  }

  // Cache the result
  m_cache.cache(guess, entropy);
  return entropy;
}
