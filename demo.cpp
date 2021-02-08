#include "srp_client.hpp"
#include "srp_params.hpp"
#include "srp_server.hpp"
#include "utils.hpp"

#include <iostream>

int main() {
  using std::cout, std::boolalpha, std::endl;

  Client client("ag", "dontuse12345");  // params are username, password
  Server server;

  const auto verifier = client.step1_getVerifier();
  const auto B = server.step1_getB(verifier);
  const auto A = client.step2_getA(B);
  server.step2_generateSecret(A);

  cout << "Client's shared secret: " << client.getSecret() << "\n\n";
  cout << "Server's shared secret: " << server.getSecret() << "\n";
  cout << "\nAre same? " << boolalpha
       << (client.getSecret() == server.getSecret()) << endl;
}
