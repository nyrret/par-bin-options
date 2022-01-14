#include <cmath>
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
  double zubairResult = zubairBinomial(200, 252, 127.62, 130.0, 0.001, 0.20);
  std::cout << "zubair result: " << zubairResult << std::endl;

  // european call from python european-call-option
  // want it to be approx 6.75
  // TODO: steps should be 100
  double result = europeanCall(200, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  std::cout << "europeanCall result: " << result << std::endl;

  // result from calculator
  // should be around 7.45 ecause doesn't include dividend yield
  double thurmanCalc = thurmanEuropeanCall(127.62, 130.0, 252, 0.001, 0.2, 200);
  std::cout << "thurmanCalc result: " << thurmanCalc << std::endl;
}