#include "binomial.h"

namespace Binomial {
double OptionConfig::getBinomialValue(double currentValue, double futureValue, int currentStep, int numUpMovements) {
  return (pu_ * futureValue + pd_ * currentValue)*exp(-riskFreeRate_*deltaT_);
}

double OptionConfig::getSpotPrice(int currentStep, int numUpMovements) {
  return S_ * pow(up_, 2*currentStep - (numUpMovements - 1));
}

// QL European 
double QLEuropeanCall::getExerciseValue(int currentStep, int numUpMovements) {
  return std::max(getSpotPrice(currentStep, numUpMovements) - K_, 0.0);
}

double QLEuropeanCall::getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements) {
  return getBinomialValue(currentValue, futureValue, currentStep, numUpMovements);
}

double QLEuropeanPut::getExerciseValue(int currentStep, int numUpMovements) {
  return std::max(K_ - getSpotPrice(currentStep, numUpMovements), 0.0);
}

double QLEuropeanPut::getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements) {
  return getBinomialValue(currentValue, futureValue, currentStep, numUpMovements);
}

// QL American
double QLAmericanCall::getExerciseValue(int currentStep, int numUpMovements) {
  return std::max(getSpotPrice(currentStep, numUpMovements) - K_, 0.0);
}

double QLAmericanCall::getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements) {
  return std::max(getExerciseValue(currentStep, numUpMovements), getBinomialValue(currentValue, futureValue, currentStep, numUpMovements));
}

double QLAmericanPut::getExerciseValue(int currentStep, int numUpMovements) {
  return std::max(K_ - getSpotPrice(currentStep, numUpMovements), 0.0);
}

double QLAmericanPut::getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements) {
  return std::max(getExerciseValue(currentStep, numUpMovements), getBinomialValue(currentValue, futureValue, currentStep, numUpMovements));
}

// Zubair European
double ZubairEuropeanCall::getExerciseValue(int currentStep, int numUpMovements) {
  return std::max(getSpotPrice(currentStep, numUpMovements) - K_, 0.0);
}

double ZubairEuropeanCall::getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements) {
  return getBinomialValue(currentValue, futureValue, currentStep, numUpMovements);
}

double ZubairEuropeanPut::getExerciseValue(int currentStep, int numUpMovements) {
  return std::max(K_ - getSpotPrice(currentStep, numUpMovements), 0.0);
}

double ZubairEuropeanPut::getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements) {
  return getBinomialValue(currentValue, futureValue, currentStep, numUpMovements);
}

// Zubair American
double ZubairAmericanCall::getExerciseValue(int currentStep, int numUpMovements) {
  return std::max(getSpotPrice(currentStep, numUpMovements) - K_, 0.0);
}

double ZubairAmericanCall::getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements) {
  return std::max(getExerciseValue(currentStep, numUpMovements), getBinomialValue(currentValue, futureValue, currentStep, numUpMovements));
}

double ZubairAmericanPut::getExerciseValue(int currentStep, int numUpMovements) {
  return std::max(K_ - getSpotPrice(currentStep, numUpMovements), 0.0);
}

double ZubairAmericanPut::getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements) {
  return std::max(getExerciseValue(currentStep, numUpMovements), getBinomialValue(currentValue, futureValue, currentStep, numUpMovements));
}
}  // namespace Binomial