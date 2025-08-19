/**
 * @file hybrid_strategy.cpp
 * @brief Implementation of HybridStrategy class
 */

#include "hybrid_strategy.hpp"
#include "../utils/utils.hpp"

HybridStrategy::HybridStrategy(const EntropyStrategy& entropyStrategy,
                               const MinimaxStrategy& minimaxStrategy,
                               const FrequencyStrategy& frequencyStrategy)
    : m_entropyStrategy{entropyStrategy}, m_minimaxStrategy{minimaxStrategy},
      m_frequencyStrategy{frequencyStrategy} {}

int32_t
HybridStrategy::selectBestGuess(const std::vector<int32_t>& possibleNumbers,
                                const GuessHistoryManager& history) const {

  if (possibleNumbers.empty()) {
    return utils::minValidNumber; // Fallback to a known valid number
  }

  // Early game: use entropy for maximum information gain
  if (history.getGuessCount() < 2) {
    return m_entropyStrategy.selectBestGuess(possibleNumbers, history);
  }

  // Mid-game: balance entropy and minimax
  if (possibleNumbers.size() > 10) {
    int32_t bestGuess{possibleNumbers.at(0)};
    double bestScore{-1.0};

    for (size_t i{0}; i < utils::validNumberRange; ++i) {
      const int32_t candidate{static_cast<int32_t>(i) + utils::minValidNumber};
      if (!utils::isValidGuess(candidate).has_value()) {
        continue;
      }

      // Skip if we've already guessed this number
      if (history.hasBeenGuessed(candidate)) {
        continue;
      }

      if (const double score{
              calculateHybridScore(candidate, possibleNumbers, history)};
          score > bestScore) {
        bestScore = score;
        bestGuess = candidate;
      }
    }

    return bestGuess;
  }

  // End game: use minimax for guaranteed optimal worst-case
  return m_minimaxStrategy.selectBestGuess(possibleNumbers, history);
}

std::string_view HybridStrategy::getStrategyName() const { return "Hybrid"; }

double HybridStrategy::calculateHybridScore(
    int32_t guess, const std::vector<int32_t>& possibleNumbers,
    [[maybe_unused]] const GuessHistoryManager& history) const {

  // Calculate individual strategy scores using their respective methods
  
  // Entropy calculation using EntropyStrategy's calculateEntropy method
  const double entropy = m_entropyStrategy.calculateEntropy(guess, possibleNumbers);

  // Minimax calculation using MinimaxStrategy's calculateMinimax method
  const size_t minimaxValue = m_minimaxStrategy.calculateMinimax(guess, possibleNumbers);

  // Frequency calculation using FrequencyStrategy's calculateFrequency method
  const double frequency = m_frequencyStrategy.calculateFrequency(guess, possibleNumbers);

  // Weighted combination of strategies (matching original implementation)
  const double score = 0.5 * entropy +
                       0.3 * (1.0 / (1.0 + static_cast<double>(minimaxValue))) +
                       0.2 * frequency;

  return score;
}
