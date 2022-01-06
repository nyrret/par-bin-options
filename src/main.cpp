#include <cstdlib>
#include <iostream>

#include "main.h"
#include "binomial.h"

int main(int argc, char* argv[]) {
  double result = americanPut(4, 4, 4, 4, 4, 4, 4);
  std::cout << "result: " << result << std::endl;
}