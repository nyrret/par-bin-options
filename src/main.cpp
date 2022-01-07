#include <cstdlib>
#include <iostream>

#include "src/main.h"
#include "binomial.h"

int main(int argc, char* argv[]) {
  double result = americanCall(4, 4, 4, 4, 4, 4, 4);
  std::cout << "result: " << result << std::endl;
}