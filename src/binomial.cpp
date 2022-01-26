#include "binomial.h"

namespace Binomial {
double EuropeanCallWithDividend::getBinomialValue(double currentValue, double futureValue) {
  return (pu_ * futureValue + pd_ * currentValue)*exp(-riskFreeRate_*deltaT_);
}
}  // namespace Binomial