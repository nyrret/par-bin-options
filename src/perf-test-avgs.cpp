#include "binomial.h"
#include "gettime.h"
#include "original-binomial.h"

int main(int argc, char* argv[])
{
  Timer t = Timer{};

  // general vs. original QL implementation
  double runningTotal = 0;
  t.start();
  for (int i = 0; i < 10; i++) {
    Binomial::qlEuropeanCall(20000, 252, 127.62, 130, 0.001, 0.20, 0.0163);
    runningTotal += t.next();
  }
  t.stop();
  std::cout << "QL European Call: " << runningTotal / 10.0 << std::endl;

  runningTotal = 0;
  t.start();
  for (int i = 0; i < 10; i++) {
    Binomial::binomialTraversal<Binomial::QLEuropeanCall>(20000, 252, 127.62, 130, 0.001, 0.20, 0.0163);
    runningTotal += t.next();
  }
  t.stop();
  std::cout << "QL general framework: " << runningTotal / 10.0 << std::endl;

  // Zubair
  runningTotal = 0;
  t.start();
  for (int i = 0; i < 10; i++) {
    Binomial::zubairEuropeanCall(20000, 252, 127.62, 130, 0.001, 0.20, 0.0163);
    runningTotal += t.next();
  }
  t.stop();
  std::cout << "Zubair Euroean Call" << runningTotal / 10.0 << std::endl;

  runningTotal = 0;
  t.start();
  for (int i = 0; i < 10; i++) {
    Binomial::zubairEuropeanCall(20000, 252, 127.62, 130, 0.001, 0.20, 0.0163);
    runningTotal += t.next();
  }
  t.stop();
  std::cout << "Zubair general framework" << runningTotal / 10.0 << std::endl;

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