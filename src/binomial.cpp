#include "binomial.h"

namespace Binomial {
double CallWithDividendConfig::getExerciseValue(int currentStep, int numUpMovements) {
  return S_ * pow(up_, 2*currentStep - (numUpMovements - 1)) - K_;
}

double CallWithDividendConfig::getBinomialValue(double currentValue, double futureValue, int currentStep, int numUpMovements) {
  return (pu_ * futureValue + pd_ * currentValue)*exp(-riskFreeRate_*deltaT_);
}

double EuropeanCallWithDividend::getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements) {
  return getBinomialValue(currentValue, futureValue, currentStep, numUpMovements);
}

double AmericanCallWithDividend::getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements) {
  return std::max(getExerciseValue(currentStep, numUpMovements), getBinomialValue(currentValue, futureValue, currentStep, numUpMovements));
}
}  // namespace Binomial