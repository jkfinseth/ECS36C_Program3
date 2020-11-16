#include <iostream>
#include "multiset.h"

// Recursive function to find all factors
void Factor(int input, Multiset<int>& storage) {
  int cap, i, condition;

  condition = 0;

  cap = input / 2;

  for (i = 2; i <= cap; i++) {
    if (input % i == 0) {
      storage.Insert(i);
      Factor(input / i, storage);
      condition = 1;
      break;
    }
  }

  if (condition == 0)
    storage.Insert(input);
}

// Checks if number is prime
bool IsPrime(int input) {
  int cap, i;

  cap = input / 2;

  for (i = 2; i <= cap; i++) {
    if (input % i == 0)
      return false;
  }

  return true;
}

int main(int argc, char *argv[]) {
  Multiset<int> prime_factors;
  std::string operation;
  int test;

  // Error check to ensure user is properly using the program
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] <<
    " <number> <command> [<args>]" << std::endl;
    exit(1);
  }

  std::string integer = argv[1];
  std::istringstream temp(integer);
  if (!(temp >> test)) {
    std::cerr << "Invalid number" << std::endl;
    exit(1);
  }

  // Check what to do
  operation = argv[2];

  // All Command
  if (!operation.compare("all")) {
    if (IsPrime(test)) {
      std::cout << "No prime factors" << std::endl;
    } else {
      Factor(test, prime_factors);

      std::cout << prime_factors;
    }
  // Min Command
  } else if (!operation.compare("min")) {
    Factor(test, prime_factors);

    std::cout << prime_factors.Min() << " (x" <<
    prime_factors.Count(prime_factors.Min()) << ")" <<
    std::endl;
  // Max Command
  } else if (!operation.compare("max")) {
    Factor(test, prime_factors);

    std::cout << prime_factors.Max() << " (x" <<
    prime_factors.Count(prime_factors.Max()) << ")" <<
    std::endl;
  // Near command
  } else if (!operation.compare("near")) {
    if (argc == 3) {
      std::cerr << "Command \'near\' expects another argument:" <<
      " [+/-]prime" << std::endl;
      exit(1);
    }

    int x;

    Factor(test, prime_factors);

    // +Prime
    if (argv[3][0] == '+') {
      std::string argv3 = argv[3];
      integer = argv3.substr(1, argv3.length() - 1);

      std::istringstream integ(integer);

      if (!(integ >> x)) {
        std::cerr << "Invalid prime" << std::endl;
        exit(1);
      }

      x++;
      if (x < prime_factors.Max())
        std::cout << prime_factors.Ceil(x) << " (x" <<
        prime_factors.Count(prime_factors.Ceil(x)) << ")" <<
        std::endl;
      else
        std::cout << "No match" << std::endl;
    // -Prime
    } else if (argv[3][0] == '-') {
      std::string argv3 = argv[3];
      integer = argv3.substr(1, argv3.length() - 1);

      std::istringstream integ(integer);

      if (!(integ >> x)) {
        std::cerr << "Invalid prime" << std::endl;
        exit(1);
      }

      if (x > prime_factors.Min())
        std::cout << prime_factors.Floor(x) << " (x" <<
        prime_factors.Count(prime_factors.Floor(x)) << ")" <<
        std::endl;
      else
        std::cout << "No match" << std::endl;
    // User input no +/-
    } else {
      integer = argv[3];

      std::istringstream integ(integer);

      if (!(integ >> x)) {
        std::cerr << "Invalid prime" << std::endl;
        exit(1);
      }

      if (prime_factors.Contains(x))
        std::cout << x << " (x" <<
        prime_factors.Count(x) << ")" <<
        std::endl;
      else
        std::cout << "No match" << std::endl;
    }
  // Invalid command
  } else {
    std::cerr << "Command \'" << argv[2] << "\' is invalid" << std::endl;
    std::cerr << "Possible commands are: all|min|max|near" << std::endl;
    exit(1);
  }

  return 0;
}
