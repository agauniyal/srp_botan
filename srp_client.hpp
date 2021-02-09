#pragma once

#include "botan/srp6.h"
#include "botan/system_rng.h"

#include "srp_params.hpp"
#include "utils.hpp"

#include <string>
#include <utility>
#include <vector>
#include <cstdio>

class Client {
  std::vector<uint8_t> _salt;
  std::string _username;
  std::string _password;
  std::string _secret;

 public:
  Client(std::string username, std::string password)
      : _username(std::move(username)), _password(std::move(password)) {
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
    try{
      auto [A, secret] = srp6_client_agree(_username, _password, SRP6Params::group_id, SRP6Params::hash_id, _salt, B, Botan::system_rng());
      _secret = vec8toHex(secret.bits_of());
      return A;
    } catch (std::exception &e) {
      std::puts(e.what());
      return Botan::BigInt{};
    }
  }

  auto getSecret() const { return _secret; }
};

#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(SRPClient) {
  class_<Client>("SRPClient")
      .constructor<const std::string, const std::string>()
      .function("getUsernamePassword", &Client::getUsernamePassword)
      .function("getSalt", &Client::getSalt)
      .function("step1_getVerifier", &Client::step1_getVerifier)
      .function("step2_getA", &Client::step2_getA)
      .function("getSecret", &Client::getSecret);
}
#endif
