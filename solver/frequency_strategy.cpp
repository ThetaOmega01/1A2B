/**
 * @file frequency_strategy.cpp
 * @brief Implementation of FrequencyStrategy class
 */

#include "frequency_strategy.hpp"

#include "../utils/utils.hpp"
#include "guess_history_manager.hpp"
#include <array>

int32_t FrequencyStrategy::selectBestGuess(
    const std::vector<int32_t>& possibleNumbers,
    const GuessHistoryManager& history) const noexcept {
  if (possibleNumbers.empty()) {
    return utils::minValidNumber;
  }
  if (possibleNumbers.size() <= 2) {
    return possibleNumbers.front();
  }

  std::array<std::array<int32_t, 10>, utils::numberSize> digitFreq{};
  for (const auto number : possibleNumbers) {
    auto digits = utils::getDigits(number);
    for (size_t pos{0}; pos < utils::numberSize; ++pos) {
      ++digitFreq.at(pos).at(digits.at(pos));
    }
  }

  const double invCount{1.0 / static_cast<double>(possibleNumbers.size())};
  int32_t bestGuess{possibleNumbers.front()};
  double bestScore{-1.0};

  for (size_t i{0}; i < utils::validNumberRange; ++i) {
    const int32_t candidate{static_cast<int32_t>(i) + utils::minValidNumber};
    if (!utils::isValidGuess(candidate).has_value() ||
        history.hasBeenGuessed(candidate)) {
      continue;
    }

    auto guessDigits{utils::getDigits(candidate)};
    double score{0.0};
    for (size_t pos{0}; pos < utils::numberSize; ++pos) {
      score += digitFreq.at(pos).at(guessDigits.at(pos)) * invCount;
    }

    if (score > bestScore) {
      bestScore = score;
      bestGuess = candidate;
    }
  }

  return bestGuess;
}

std::string_view FrequencyStrategy::getStrategyName() const noexcept {
  return {"Frequency-based"};
}