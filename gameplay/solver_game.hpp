/**
 * @file solver_game.hpp
 * @brief Solver game
 */

#pragma once

#include "../solver/heuristic_solver.hpp"

/**
 * @class SolverGame
 * @brief Solver session
 */
class SolverGame {
public:
  /**
   * @brief Constructs a new SolverGame instance
   * @param maxAttempts Maximum number of attempts allowed
   * @param strategy The solver strategy to use
   */
  SolverGame(int32_t maxAttempts, HeuristicSolver::GuessStrategy strategy);

  /**
   * @brief Starts the interactive solving process
   */
  void start();

  /**
   * @brief Reset the solver to start over
   */
  void reset();

  /**
   * @brief Get the strategy name as string
   * @param strategy The strategy enum
   * @return Readable strategy name
   */
  static std::string getStrategyName(HeuristicSolver::GuessStrategy strategy);

private:
  HeuristicSolver m_solver;
  int32_t m_maxAttempts;
  int32_t m_attemptsLeft;
  int32_t m_guessCount{0};

  /**
   * @brief Parse user feedback input (e.g., "2A1B", "2a1b")
   * @param input The user's feedback string
   * @return Pair of (A count, B count), or nullopt if invalid
   */
  static std::optional<std::pair<int32_t, int32_t>>
  parseFeedback(std::string_view input);
};
