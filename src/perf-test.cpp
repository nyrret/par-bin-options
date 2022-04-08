#include "binomial.h"
#include "gettime.h"
#include "original-binomial.h"

int main(int argc, char* argv[])
{
  (void)argc;
  (void)argv;
  Timer t = Timer{};

  // general vs. original implementation
  t.start();
  double result = Binomial::qlEuropeanCall(100000, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  t.reportNext("QL European Call");
  // std::cout << "result: " << result << std::endl;

  Binomial::binomialTraversal<Binomial::QLEuropeanCall>(100000, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  t.reportNext("QL general framework");

  double stencilResult = Binomial::stencilBinomialTraversal<Binomial::QLEuropeanCall>(100000, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  t.reportNext("QL serial stencil");
  // std::cout << "stencilResult: " << stencilResult << std::endl;

  // Binomial::parallelBinomialTraversal<Binomial::QLEuropeanCall>(100000, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  // t.reportNext("QL general parallel");

  double parStencilResult = Binomial::parallelStencilBinomialTraversal<Binomial::QLEuropeanCall>(100000, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  t.reportNext("QL par stencil");
  // std::cout << "parStencilResult: " << parStencilResult << std::endl;
  t.stop();
  // t.start();
  // Binomial::binomialTraversal<Binomial::ZubairEuropeanCall>(20000, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  // t.stop();
  // t.reportTotal("Zubair general framework");


  // t.start();
  // Binomial::zubairEuropeanCall(20000, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  // t.stop();
  // t.reportTotal("Zubair European Call");

  // large number of steps
  // t.start();
  // double result = Binomial::binomialTraversal<Binomial::QLEuropeanCall>(20000, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  // t.stop();
  // t.reportTotal("20,000 steps, serial");

  // t.start();
  // result = Binomial::parallelBinomialTraversal<Binomial::QLEuropeanCall>(20000, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  // t.stop();
  // t.reportTotal("20,000 steps, parallel");
}