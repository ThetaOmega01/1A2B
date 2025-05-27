#include "utils.hpp"
#include <algorithm>
#include <limits>
#include <stdexcept>

namespace utils {

constexpr int32_t intPow(const int32_t base, int32_t exp) {
  if (exp < 0) {
    return 0;
  }

  // Prevent overflow
  if (base == 0) {
    return exp == 0 ? 1 : 0;
  }

  if (exp > 31) { // Prevent excessive computation
    throw std::runtime_error(
        "Exponent too large for safe integer power calculation");
  }

  int64_t result{1};
  int64_t base64{base};

  while (exp > 0) {
    if (exp & 1) {
      result *= base64;
      // Check for overflow
      if (result > std::numeric_limits<int32_t>::max()) {
        throw std::runtime_error("Integer overflow in power calculation");
      }
    }
    base64 *= base64;
    if (base64 > std::numeric_limits<int32_t>::max() && exp > 1) {
      throw std::runtime_error("Integer overflow in power calculation");
    }
    exp >>= 1;
  }

  return static_cast<int32_t>(result);
}

std::array<int32_t, numberSize> getDigits(int32_t number) {
  // Validate input bounds
  if (number < 0) {
    throw std::runtime_error("Cannot extract digits from negative number");
  }

  std::array<int32_t, numberSize> digits{};
  for (int32_t i = numberSize - 1; i >= 0; --i) {
    digits.at(i) = number % 10;
    number /= 10;
  }
  return digits;
}

std::optional<std::array<int32_t, numberSize>>
isValidGuess(const int32_t guess) {
  // Basic range check
  if (guess < minValidNumber || guess > maxValidNumber) {
    return std::nullopt;
  }

  const std::array guessDigits{getDigits(guess)};

  // Check first digit is not zero
  if (guessDigits.at(0) == 0) {
    return std::nullopt;
  }

  // Check for unique digits
  std::array<bool, 10> digitSeen{};
  for (const int32_t digit : guessDigits) {
    if (digitSeen.at(digit)) {
      return std::nullopt; // Duplicate digit found
    }
    digitSeen.at(digit) = true;
  }

  return guessDigits;
}

std::array<int32_t, 2> calculateAB(const int32_t guess, const int32_t target) {
  const std::array<int32_t, numberSize> guessDigits{getDigits(guess)};
  const std::array<int32_t, numberSize> targetDigits{getDigits(target)};

  int32_t As{0};
  int32_t Bs{0};

  std::array<int32_t, 10> targetCount{};
  std::array<int32_t, 10> guessCount{};

  // Count A's (correct position) and build frequency counts for B's
  for (int32_t digitIndex{0}; digitIndex < numberSize; ++digitIndex) {
    if (targetDigits.at(digitIndex) == guessDigits.at(digitIndex)) {
      ++As;
    } else {
      ++targetCount.at(targetDigits.at(digitIndex));
      ++guessCount.at(guessDigits.at(digitIndex));
    }
  }

  // Count B's (correct digit, wrong position)
  for (int32_t countIndex{0}; countIndex < 10; ++countIndex) {
    Bs += std::min(targetCount.at(countIndex), guessCount.at(countIndex));
  }

  return {As, Bs};
}

} // namespace utils
