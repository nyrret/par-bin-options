#include <cstdlib>
#include <iostream>

#include "src/main.h"
#include "binomial.h"

int main(int argc, char* argv[]) {
  // values taken from python American option QL tutorial
  // want it to be approx 6.84
  // double result = americanCall(200, 127.62, 130, 0.001, 0.20, 0.0163*127.62);

  // from https://github.com/lballabio/QuantLib/blob/master/test-suite/americanoption.cpp
  //double result = americanPut(36, 90.0, 100.0, 0.10, 0.15, 0.10); // should be 10.0

  // zubair binomial, running with QL tutorial items
  // double result = zubairBinomial(127.62, 130.0, 200, 0.001, 0.20, 1);

  // european call from python european-call-option
  // want it to be approx 6.75
  double result = europeanCall(100, 127.62, 130, 0.001, 0.20, 0.0163);//*127.62);

  std::cout << "result: " << result << std::endl;
}