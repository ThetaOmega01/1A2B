#include "heuristic_solver.hpp"

HeuristicSolver::HeuristicSolver(const GuessStrategy strategy)
    : m_strategySelector{convertStrategy(strategy)} {}

std::optional<int32_t> HeuristicSolver::nextGuess() {
  if (m_searchSpace.isEmpty()) {
    return std::nullopt; // No valid guesses left
  }

  // If only one possibility remains, return it
  if (m_searchSpace.hasOnlyOne()) {
    return m_searchSpace.getSingleRemaining();
  }

  // Get possible numbers and use strategy selector to choose best guess
  const auto possibleNumbers{m_searchSpace.getPossibleNumbers()};
  return m_strategySelector.selectGuess(possibleNumbers, m_history);
}

void HeuristicSolver::updateGuess(const int32_t guess, const int32_t aCount,
                                  const int32_t bCount) {
  // Store the guess and feedback in history
  m_history.addGuess(guess, aCount, bCount);

  // Clear caches since the search space is changing
  m_strategySelector.clearCaches();

  // Use constraint propagation to eliminate impossible numbers
  m_searchSpace.applyConstraint(guess, aCount, bCount);
}

bool HeuristicSolver::isSolved() const { return m_searchSpace.hasOnlyOne(); }

size_t HeuristicSolver::getRemainingCount() const {
  return m_searchSpace.getRemainingCount();
}

void HeuristicSolver::setStrategy(const GuessStrategy strategy) {
  m_strategySelector.setStrategy(convertStrategy(strategy));
}

HeuristicSolver::GuessStrategy HeuristicSolver::getStrategy() const {
  return convertStrategy(m_strategySelector.getStrategy());
}

std::string_view HeuristicSolver::getCurrentStrategyName() const {
  return m_strategySelector.getCurrentStrategyName();
}

std::string_view HeuristicSolver::getStrategyName(const GuessStrategy strategy) {
  return StrategySelector::getStrategyName(convertStrategy(strategy));
}

StrategySelector::StrategyType
HeuristicSolver::convertStrategy(const GuessStrategy strategy) {
  switch (strategy) {
  case GuessStrategy::entropyBased:
    return StrategySelector::StrategyType::entropyBased;
  case GuessStrategy::miniMax:
    return StrategySelector::StrategyType::miniMax;
  case GuessStrategy::frequencyBased:
    return StrategySelector::StrategyType::frequencyBased;
  case GuessStrategy::hybrid:
  default:
    return StrategySelector::StrategyType::hybrid;
  }
}

HeuristicSolver::GuessStrategy
HeuristicSolver::convertStrategy(
    const StrategySelector::StrategyType strategy) {
  switch (strategy) {
  case StrategySelector::StrategyType::entropyBased:
    return GuessStrategy::entropyBased;
  case StrategySelector::StrategyType::miniMax:
    return GuessStrategy::miniMax;
  case StrategySelector::StrategyType::frequencyBased:
    return GuessStrategy::frequencyBased;
  case StrategySelector::StrategyType::hybrid:
  default:
    return GuessStrategy::hybrid;
  }
}
