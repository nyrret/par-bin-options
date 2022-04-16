#include "binomial.h"
#include "gettime.h"
#include "original-binomial.h"

int main(int argc, char* argv[])
{
  (void)argc;
  (void)argv;
  Timer t = Timer{};

  t.start();

  // general vs. original implementation
  // Binomial::qlEuropeanCall(20000, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  // t.reportNext("European Call");
  // // std::cout << "result: " << result << std::endl;

  // Binomial::parallelStencilBinomialTraversal<Binomial::QLEuropeanCall>(100000, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  // t.reportNext("QL par stencil");
  // getchar();

  // t.start();
  // for (int i = 0; i < 3; i++) {
  //   Binomial::parallelStencilBinomialTraversal<Binomial::QLEuropeanCall>(100000, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  //   t.reportNext("QL par stencil");
  // }

  Binomial::binomialTraversal<Binomial::QLEuropeanCall>(137000, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  t.reportNext("general framework");

  // Binomial::stencilBinomialTraversal<Binomial::QLEuropeanCall>(500000, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  // t.reportNext("QL serial stencil");
  // std::cout << "stencilResult: " << stencilResult << std::endl;

  Binomial::parallelBinomialTraversal<Binomial::QLEuropeanCall>(137000, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  t.reportNext("QL general parallel");

  // Binomial::parallelStencilBinomialTraversal<Binomial::QLEuropeanCall>(100000, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  // t.reportNext("QL par stencil");
  // std::cout << "parStencilResult: " << parStencilResult << std::endl;
  // t.stop();

  // Zubair

  // t.start();
  // Binomial::binomialTraversal<Binomial::ZubairEuropeanCall>(20000, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  // t.stop();
  // t.reportTotal("Zubair general framework");


  // t.start();
  // Binomial::zubairEuropeanCall(200000, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  // t.reportNext("zubair orig");
  t.stop();
  // t.reportTotal("Zubair European Call");
}