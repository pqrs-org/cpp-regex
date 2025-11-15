#include <boost/ut.hpp>
#include <pqrs/regex.hpp>
#include <unordered_map>

int main(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;
  using namespace std::literals;

  "update"_test = [] {
    //
    // Normal
    //

    try {
      pqrs::regex regex("^com\\.apple\\.Terminal$");
      expect("^com\\.apple\\.Terminal$"sv == regex.get_string());
    } catch (const std::exception& e) {
      expect(false);
    }

    //
    // Invalid regex
    //

    try {
      pqrs::regex regex("^com\\.apple\\.Te(rminal$");
      expect(false);
    } catch (const std::exception& e) {
      expect("The expression contained mismatched ( and )."sv == std::string{e.what()});
    }
  };

  "json"_test = [] {
    //
    // Normal
    //

    try {
      nlohmann::json json("^com\\.apple\\.Terminal$");
      auto regex = json.get<pqrs::regex>();
      expect("^com\\.apple\\.Terminal$"sv == regex.get_string());
      expect(json.dump() == nlohmann::json(regex).dump());
    } catch (const pqrs::json::unmarshal_error& e) {
      expect(false);
    }

    //
    // Invalid regex
    //

    try {
      nlohmann::json json("^com\\.apple\\.Te(rminal$");
      auto regex = json.get<pqrs::regex>();
    } catch (const pqrs::json::unmarshal_error& e) {
      expect("The expression contained mismatched ( and ).: `^com\\.apple\\.Te(rminal$`"sv == std::string{e.what()});
    }

    //
    // Unexpected JSON
    //

    try {
      nlohmann::json().get<pqrs::regex>();
      expect(false);
    } catch (const pqrs::json::unmarshal_error& e) {
      expect("json must be string, but is `null`"sv == std::string{e.what()});
    }
  };

  "hash"_test = [] {
    std::unordered_map<pqrs::regex, bool> m;
    pqrs::regex regex;
    m[regex] = true;
  };

  return 0;
}
