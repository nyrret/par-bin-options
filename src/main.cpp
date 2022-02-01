#include <cmath>
#include <cstdlib>
#include <iostream>

#include "src/main.h"
#include "binomial.h"

int main(int argc, char* argv[]) {
  // european call from Zubair paper
  // should be approx 7.4510 (no dividend yield)
  // not correct right now
  // double zubairResult = Binomial::zubairBinomial(100, 252, 127.62, 130.0, 0.001, 0.20);
  // std::cout << "zubair result: " << zubairResult << std::endl;

  // // european call from python european-call-option
  // // should be approx 6.7695
  // double europeanResult = Binomial::europeanCall(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  // std::cout << "europeanCall result: " << europeanResult << std::endl;

  // // american call from python american-call-option
  // // should be approx 6.8421
  // double americanResult = Binomial::americanCall(200, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  double americanResult = Binomial::binomialTraversal<Binomial::AmericanCallWithDividend>(
    200, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  std::cout << "american call result: " << americanResult << std::endl;

  // general framework test -- european call option
  // should be approx 6.7695
  double result = Binomial::binomialTraversal<Binomial::EuropeanCallWithDividend>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  std::cout << "european call result: " << result << std::endl;

  // Thurman tutorial: http://www.josephthurman.com/binomial3.html
  // should be approx 7.4510 (no dividend yield)
  double europeanCallNoDividend = Binomial::binomialTraversal<Binomial::EuropeanCallNoDividend>(100, 252, 127.62, 130, 0.001, 0.20);
  std::cout << "european call no dividend result: " << europeanCallNoDividend << std::endl;

  // should be approx 7.4510
  double americanCallNoDividend = Binomial::binomialTraversal<Binomial::AmericanCallNoDividend>(100, 252, 127.62, 130, 0.001, 0.20);
  std::cout << "american call no dividend result: " << americanCallNoDividend << std::endl;
}