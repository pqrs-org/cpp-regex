#include <iostream>
#include <pqrs/regex.hpp>

int main() {
  pqrs::regex regex("^com\\.apple\\.Terminal$");

  std::cout << regex.get_string() << std::endl;

  std::cout << std::regex_search("com.apple.Terminal", regex.get_regex()) << std::endl;
  std::cout << std::regex_search("com.apple.Safari", regex.get_regex()) << std::endl;

  return 0;
}
