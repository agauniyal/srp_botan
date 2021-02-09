#pragma once

#include "botan/srp6.h"
#include "botan/system_rng.h"

#include "srp_params.hpp"
#include "utils.hpp"

#include <string>

class Server {
  Botan::SRP6_Server_Session _server;
  std::string _secret;

 public:
  auto step1_getB(const Botan::BigInt& verifier) {
    return _server.step1(verifier, SRP6Params::group_id, SRP6Params::hash_id,
                         Botan::system_rng());
  }

  auto step2_generateSecret(const Botan::BigInt& A) {
    _secret = vec8toHex(_server.step2(A).bits_of());
  }

  auto getSecret() const { return _secret; }
};

#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(SRPServer) {
  class_<Server>("SRPServer")
      .constructor<>()
      .function("step1_getB", &Server::step1_getB)
      .function("step2_generateSecret", &Server::step2_generateSecret)
      .function("getSecret", &Server::getSecret);
}
#endif
