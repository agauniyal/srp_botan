#include "botan/srp6.h"

#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(SRPBigInt) {
  value_object<Botan::BigInt>("SRPBigInt");
}
#endif

#include "srp_client.hpp"
#include "srp_server.hpp"
