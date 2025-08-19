/**
 * @file strategy_selector.cpp
 * @brief Implementation of StrategySelector class
 */

#include "strategy_selector.hpp"
#include <stdexcept>

StrategySelector::StrategySelector(const StrategyType defaultStrategy)
    : m_currentStrategy{defaultStrategy} {
  initializeStrategies();
}

int32_t
StrategySelector::selectGuess(const std::vector<int32_t>& possibleNumbers,
                              const GuessHistoryManager& history) const {

  return getCurrentStrategy().selectBestGuess(possibleNumbers, history);
}

void StrategySelector::setStrategy(const StrategyType strategy) {
  m_currentStrategy = strategy;
}

StrategySelector::StrategyType StrategySelector::getStrategy() const {
  return m_currentStrategy;
}

std::string_view StrategySelector::getCurrentStrategyName() const {
  return getStrategyName(m_currentStrategy);
}

std::string_view StrategySelector::getStrategyName(const StrategyType strategy) {
  switch (strategy) {
  case StrategyType::entropyBased:
    return "Entropy-based";
  case StrategyType::miniMax:
    return "Minimax";
  case StrategyType::frequencyBased:
    return "Frequency-based";
  case StrategyType::hybrid:
    return "Hybrid";
  default:
    return "Unknown";
  }
}

void StrategySelector::clearCaches() {
  m_entropyCache.clear();
  m_minimaxCache.clear();
}

void StrategySelector::initializeStrategies() {
  // Create strategy instances with their dependencies
  m_entropyStrategy = std::make_unique<EntropyStrategy>(m_entropyCache);
  m_minimaxStrategy = std::make_unique<MinimaxStrategy>(m_minimaxCache);
  m_frequencyStrategy = std::make_unique<FrequencyStrategy>();

  // Hybrid strategy depends on the other three strategies
  m_hybridStrategy = std::make_unique<HybridStrategy>(
      *m_entropyStrategy, *m_minimaxStrategy, *m_frequencyStrategy);
}

const IGuessStrategy& StrategySelector::getCurrentStrategy() const {
  switch (m_currentStrategy) {
  case StrategyType::entropyBased:
    return *m_entropyStrategy;
  case StrategyType::miniMax:
    return *m_minimaxStrategy;
  case StrategyType::frequencyBased:
    return *m_frequencyStrategy;
  case StrategyType::hybrid:
    return *m_hybridStrategy;
  default:
    throw std::runtime_error("Invalid strategy type");
  }
}
