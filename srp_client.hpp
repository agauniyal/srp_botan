#pragma once

#include "botan/srp6.h"
#include "botan/system_rng.h"

#include "srp_params.hpp"
#include "utils.hpp"

#include <string>
#include <string_view>
#include <utility>
#include <vector>

class Client {
  std::vector<uint8_t> _salt;
  std::string _username;
  std::string _password;
  std::string _secret;

 public:
  Client(const std::string_view& username, const std::string_view& password)
      : _username(username), _password(password) {
    Botan::system_rng().random_vec(_salt, 16);
  }

  std::pair<std::string, std::string> getUsernamePassword() const {
    return {_username, _password};
  }

  auto getSalt() { return vec8toHex(_salt); }

  auto step1_getVerifier() {
    return Botan::generate_srp6_verifier(
        _username, _password, _salt, SRP6Params::group_id, SRP6Params::hash_id);
  }

  auto step2_getA(const Botan::BigInt& B) {
    auto [A, secret] =
        srp6_client_agree(_username, _password, SRP6Params::group_id,
                          SRP6Params::hash_id, _salt, B, Botan::system_rng());
    _secret = vec8toHex(secret.bits_of());
    return A;
  }

  auto getSecret() const { return _secret; }
};
