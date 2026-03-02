#include "solver_game.hpp"
#include "../utils/utils.hpp"
#include "user_interface.hpp"
#include <algorithm>
#include <cstdint>
#include <string>

SolverGame::SolverGame(const int32_t maxAttempts,
                       const HeuristicSolver::GuessStrategy strategy)
    : m_solver{strategy}, m_maxAttempts{maxAttempts},
      m_attemptsLeft{maxAttempts} {}

void SolverGame::start() {
  bool shouldRestart{true};

  while (shouldRestart) {
    shouldRestart = false;
    const std::string strategyName{getStrategyName(m_solver.getStrategy())};
    UserInterface::displaySolverStart(strategyName, m_maxAttempts);

    // Main interactive solving loop
    while (m_attemptsLeft > 0) {
      // Get next guess from solver
      const auto nextGuess{m_solver.nextGuess()};

      if (!nextGuess.has_value()) {
        // solver has no more guesses
        UserInterface::displaySolverNoMoreGuesses(m_guessCount);
        return;
      }

      const int32_t guess{nextGuess.value()};
      ++m_guessCount;
      --m_attemptsLeft;

      // Display the solver's guess and ask for feedback
      UserInterface::displaySolverGuess(m_guessCount, guess, m_attemptsLeft);

      // Get feedback from user with reset option
      while (true) {
        const std::string feedbackInput{UserInterface::getFeedbackInput()};

        // Check for reset command
        if (feedbackInput == "reset" || feedbackInput == "RESET" ||
            feedbackInput == "Reset") {
          reset();
          shouldRestart = true;
          break;
        }

        // Parse feedback
        const auto feedback{parseFeedback(feedbackInput)};
        if (!feedback.has_value()) {
          UserInterface::displayInvalidFeedback();
          continue;
        }

        const auto [As, Bs]{feedback.value()};

        // Check if solved
        if (As == utils::numberSize && Bs == 0) {
          UserInterface::displaySolverSuccess(guess, m_guessCount);
          return;
        }

        // Update the solver with the feedback
        m_solver.updateGuess(guess, As, Bs);

        // Display remaining possibilities
        UserInterface::displayRemainingPossibilities(
            m_solver.getRemainingCount());
        break;
      }

      // Break out of main loop if reset was requested
      if (shouldRestart) {
        break;
      }
    }

    // If we get here and not restarting, we ran out of attempts
    if (!shouldRestart) {
      UserInterface::displaySolverFailure(m_guessCount);
    }
  }
}

void SolverGame::reset() {
  m_solver = HeuristicSolver{m_solver.getStrategy()};
  m_attemptsLeft = m_maxAttempts;
  m_guessCount = 0;
  UserInterface::displaySolverReset();
}

std::optional<std::pair<int32_t, int32_t>>
SolverGame::parseFeedback(const std::string_view input) {
  if (input.length() < 3) { // Minimum: "0a0b" or "0A0B"
    return std::nullopt;
  }

  // Convert to lowercase for easier parsing
  std::string lowerInput{input};
  std::ranges::transform(lowerInput, lowerInput.begin(), tolower);

  // Find 'a' and 'b' positions
  const size_t aPos{lowerInput.find('a')};
  const size_t bPos{lowerInput.find('b')};

  if (aPos == std::string::npos || bPos == std::string::npos || aPos >= bPos) {
    return std::nullopt;
  }

  // Extract A count (digit before 'a')
  if (aPos == 0 || !std::isdigit(lowerInput.at(aPos - 1))) {
    return std::nullopt;
  }
  int32_t aCount{lowerInput.at(aPos - 1) - '0'};

  // Extract B count (digit before 'b')
  if (bPos == 0 || !std::isdigit(lowerInput.at(bPos - 1))) {
    return std::nullopt;
  }
  int32_t bCount{lowerInput.at(bPos - 1) - '0'};

  // Validate ranges
  if (aCount < 0 || aCount > 4 || bCount < 0 || bCount > 4 ||
      aCount + bCount > 4) {
    return std::nullopt;
  }

  return std::make_pair(aCount, bCount);
}

std::string
SolverGame::getStrategyName(const HeuristicSolver::GuessStrategy strategy) {
  switch (strategy) {
  case HeuristicSolver::GuessStrategy::entropyBased:
    return "Entropy-based";
  case HeuristicSolver::GuessStrategy::miniMax:
    return "Minimax";
  case HeuristicSolver::GuessStrategy::frequencyBased:
    return "Frequency-based";
  case HeuristicSolver::GuessStrategy::hybrid:
    return "Hybrid";
  default:
    return "Unknown";
  }
}
