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
  double zubairResult = zubairBinomial(127.62, 130.0, 98, 0.001, 0.20, 252/98.0);
  std::cout << "zubair result: " << zubairResult << std::endl;

  // european call from python european-call-option
  // want it to be approx 6.75
  // TODO: steps should be 100
  double result = europeanCall(200, 0.7, 127.62, 130, 0.001, 0.20, 0.0163);

  std::cout << "result: " << result << std::endl;

  // thurman european call option
  double thurman = thurmanEuropeanCall(100.0, 120.0, 1, 0.01, 0.2, 100);
  std::cout << "thurman: " << thurman << std::endl;

  // result from calculator
  // TODO: go up
  double thurmanCalc = thurmanEuropeanCall(127.62, 130.0, 0.7, 0.001, 0.2, 100);
  std::cout << "thurmanCalc: " << thurmanCalc << std::endl;
}