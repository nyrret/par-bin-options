#include <cmath>
#include <cstdlib>
#include <iostream>

#include "src/main.h"
#include "binomial.h"

int main(int argc, char* argv[]) {
  // // american call from python american-call-option
  // // should be approx 6.8421, from QL, or 6.8586 from calc
  // double americanCallQL = Binomial::binomialTraversal<Binomial::QLAmericanCall>(
  //   200, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  // std::cout << "american call QL: " << americanCallQL << std::endl;

  // // 10.4881
  // double americanPutQL = Binomial::binomialTraversal<Binomial::QLAmericanPut>(
  //   100, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  // std::cout << "american put QL: " << americanPutQL << std::endl;

  // // 7.4510
  // double americanCallQLNoDividend = Binomial::binomialTraversal<Binomial::QLAmericanCall>(
  //   200, 252, 127.62, 130, 0.001, 0.20);
  // std::cout << "american call QL no dividend: " << americanCallQLNoDividend << std::endl;

  // // general framework test -- european call option
  // // should be approx 6.7695
  // double europeanCallQL = Binomial::binomialTraversal<Binomial::QLEuropeanCall>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  // std::cout << "european call QL: " << europeanCallQL << std::endl;

  // // 7.4510
  // double europeanCallQLNoDividend = Binomial::binomialTraversal<Binomial::QLEuropeanCall>(100, 252, 127.62, 130, 0.001, 0.20);
  // std::cout << "european call QL no dividend: " << europeanCallQLNoDividend << std::endl;

  // // 10.4880
  // double europeanPutQL = Binomial::binomialTraversal<Binomial::QLEuropeanPut>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  // std::cout << "european put zubair: " << europeanPutQL << std::endl;

  // // should be approx 6.7695
  // double europeanCallZubair = Binomial::binomialTraversal<Binomial::ZubairEuropeanCall>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  // std::cout << "european call zubair: " << europeanCallZubair << std::endl;

  // // should be approx 10.4880
  // double europeanPutZubair = Binomial::binomialTraversal<Binomial::ZubairEuropeanPut>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  // std::cout << "european put zubair: " << europeanPutZubair << std::endl;

  // // Thurman tutorial: http://www.josephthurman.com/binomial3.html
  // // should be approx 7.4510 (no dividend yield)
  // double europeanCallZubairNoDividend = Binomial::binomialTraversal<Binomial::ZubairEuropeanCall>(100, 252, 127.62, 130, 0.001, 0.20);
  // std::cout << "european call zubair no dividend: " << europeanCallZubairNoDividend << std::endl;

  // // should be approx 6.8586
  // double americanCallZubair = Binomial::binomialTraversal<Binomial::ZubairAmericanCall>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  // std::cout << "american call zubair: " << americanCallZubair << std::endl;

  // // should be approx 10.4881
  // double americanPutZubair = Binomial::binomialTraversal<Binomial::ZubairAmericanPut>(100, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  // std::cout << "american put zubair: " << americanPutZubair << std::endl;

  // // should be approx 7.4510
  // double americanCallZubairNoDividend = Binomial::binomialTraversal<Binomial::ZubairAmericanCall>(100, 252, 127.62, 130, 0.001, 0.20);
  // std::cout << "american call zubair no dividend: " << americanCallZubairNoDividend << std::endl;

  // // parallel
  // // should be approx 7.4510
  // double parEuropeanCallNoDividend = Binomial::parallelBinomialTraversal<Binomial::ZubairEuropeanCall>(100, 252, 127.62, 130, 0.001, 0.20);
  // std::cout << "parallel european call no dividend result: " << parEuropeanCallNoDividend << std::endl;
}