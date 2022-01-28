#include "binomial.h"

namespace Binomial {
double EuropeanCallWithDividend::getBinomialValue(double currentValue, double futureValue, int i, int currentStep) {
  return (pu_ * futureValue + pd_ * currentValue)*exp(-riskFreeRate_*deltaT_);
}

double EuropeanCallWithDividend::getExerciseValue(int i, int currentStep) {
  return S_ * pow(up_, 2*i - steps_) - K_;
}

double AmericanCallWithDividend::getBinomialValue(double currentValue, double futureValue, int i, int currentStep) {
  return std::max(getExerciseValue(i, currentStep), (pu_ * futureValue + pd_ * currentValue)*exp(-riskFreeRate_*deltaT_));
}

double AmericanCallWithDividend::getExerciseValue(int i, int currentStep) {
  return S_ * pow(up_, 2*i - (currentStep - 1)) - K_;
}
}  // namespace Binomial