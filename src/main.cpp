#include <cstdlib>
#include <iostream>

#include "src/main.h"
#include "src/binomial.h"

int main(int argc, char* argv[]) {
  double result = americanPut(4, 4, 4, 4, 4, 4, 4);
  std::cout << "result: " << result << std::endl;
}