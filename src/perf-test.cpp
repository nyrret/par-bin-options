#include "binomial.h"
#include "gettime.h"
#include "original-binomial.h"

int main(int argc, char* argv[])
{
  Timer t = Timer{};

  // general vs. original implementation
  t.start();
  Binomial::binomialTraversal<Binomial::QLEuropeanCall>(20000, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  t.stop();
  t.reportTotal("QL general framework");

  t.start();
  Binomial::binomialTraversal<Binomial::ZubairEuropeanCall>(20000, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  t.stop();
  t.reportTotal("Zubair general framework");

  t.start();
  Binomial::qlEuropeanCall(20000, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  t.stop();
  t.reportTotal("QL European Call");

  t.start();
  Binomial::zubairEuropeanCall(20000, 252, 127.62, 130, 0.001, 0.20, 0.0163);
  t.stop();
  t.reportTotal("Zubair European Call");

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