#include "interface.hpp"
#include <stdexcept>

GameSessionBase::GameSessionBase(const int32_t secret,
                                 const int32_t maxAttempts)
    : m_secret{secret}, m_maxAttempts{maxAttempts},
      m_attemptsLeft{maxAttempts} {
  if (maxAttempts <= 0) {
    throw std::invalid_argument("Maximum attempts must be positive");
  }
  if (secret < 1000 || secret > 9876) {
    throw std::invalid_argument(
        "Secret number must be a valid 4-digit number with unique digits");
  }
}

void GameSessionBase::setMaxAttempts(const int32_t maxAttempts) {
  if (maxAttempts <= 0) {
    throw std::invalid_argument("Maximum attempts must be positive");
  }
  m_maxAttempts = maxAttempts;
  m_attemptsLeft = maxAttempts;
  m_gameWon = false; // Reset game state when changing attempts
}
