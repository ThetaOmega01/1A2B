#include "input_validator.hpp"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string_view>

int32_t InputValidator::getIntegerInRange(const int32_t min, const int32_t max,
                                          const std::string_view errorMessage,
                                          const uint32_t maxAttempts) {
  uint32_t attempts{0};
  int32_t value{};

  while (attempts < maxAttempts) {
    std::cin >> value;
    ++attempts;

    if (handleStreamFailure()) {
      std::cout << errorMessage;
      continue;
    }

    if (value >= min && value <= max) {
      return value;
    }

    std::cout << errorMessage;
  }

  throw std::runtime_error("Maximum input attempts exceeded");
}

bool InputValidator::getYesNoChoice(const std::string_view errorMessage,
                                    const uint32_t maxAttempts) {
  uint32_t attempts{0};
  char choice{};

  while (attempts < maxAttempts) {
    std::cin >> choice;
    ++attempts;

    if (handleStreamFailure()) {
      std::cout << errorMessage;
      continue;
    }

    choice = static_cast<char>(std::tolower(choice));
    if (choice == 'y') {
      return true;
    }
    if (choice == 'n') {
      return false;
    }
    std::cout << errorMessage;
  }

  throw std::runtime_error("Maximum input attempts exceeded for yes/no choice");
}

int32_t InputValidator::getValidGuess(const std::string_view errorMessage,
                                      const uint32_t maxAttempts) {
  uint32_t attempts{0};
  int32_t guess{};

  while (attempts < maxAttempts) {
    std::cin >> guess;
    ++attempts;

    if (handleStreamFailure()) {
      std::cout << "Invalid input. Please enter a valid four-digit number: ";
      continue;
    }

    if (utils::isValidGuess(guess)) {
      return guess;
    }
    std::cout << errorMessage;
  }

  throw std::runtime_error("Maximum input attempts exceeded");
}

std::array<int32_t, utils::numberSize>
InputValidator::getValidGuessDigits(const std::string_view errorMessage,
                                    const uint32_t maxAttempts) {
  const int32_t guess{getValidGuess(errorMessage, maxAttempts)};
  return utils::getDigits(guess);
}

void InputValidator::clearInputStream() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool InputValidator::handleStreamFailure() {
  if (std::cin.fail()) {
    clearInputStream();
    return true;
  }
  return false;
}
