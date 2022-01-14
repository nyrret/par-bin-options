#include <cstdint>
#include <iostream>
#include <math.h>
#include <vector>

#include "binomial.h"

/*
 * T -- expiration time in days
 * S -- stock price
 * K -- strike price
 */
double europeanCall(uint16_t steps, uint16_t expirationTime, double S, double K, double riskFreeRate, double volatility, double dividend_yield) {
  double deltaT = (double)expirationTime/steps/365;
  double dx = volatility * sqrt(deltaT);
  double up = exp(volatility * sqrt(deltaT));
  double down = 1/up;

  double drift_per_step = (riskFreeRate - dividend_yield - 0.5 * volatility * volatility) * deltaT;
  double pu = 0.5 + 0.5 * drift_per_step / dx;
  double pd = 1-pu;

  // initial values at expiration time
  std::vector<double> p;
  for (int i = 0; i < steps+1; ++i) {
     p.push_back(S * pow(up, 2*i - steps) - K);
    if (p[i] < 0) {
        p[i] = 0;
    }
  }

  // move to earlier times
  for (int j = steps; j >= 0; --j) {
    for (int i = 0; i < j; ++i) {
      // binomial value
      p[i] = (pu * p[i+1] + pd * p[i]) * exp(-riskFreeRate*deltaT);
    }
  }
  return p[0];
}

// // Zubair paper  -- for European Call options, I believe
double zubairBinomial(uint16_t steps, uint16_t expirationTime, double S, double K, double riskFreeRate, double volatility) {
  double dt = (double)expirationTime/steps/365;

  double u = exp(sqrt(dt)*volatility);
  double d = exp(sqrt(dt)*(-volatility));
  double pu = (exp(riskFreeRate*dt)-d)/(u-d);

  std::vector<double> optionArray;
  for (int i = 0; i < steps+1; ++i) {
    double assetPrice = S * pow(d, steps-i-1) * pow(u, i);
    optionArray.push_back(std::max(assetPrice - K, 0.0));
    if (optionArray[i] < 0) {
      optionArray[i] = 0;
    }
  }

  double pus = exp(-riskFreeRate*dt)*pu;
  double pds = exp(-riskFreeRate*dt)*(1-pu);

  // iteratively compute option price starting from leaf nodes
  for (int i = steps; i >= 0; --i) { 
    for (int j = 0; j < i-1; ++j) {
      optionArray[j] = pus * optionArray[j+1] + pds * optionArray[j];
    }
  }
  return optionArray[0];
}

/*
 * expirationTime -- in days
 */ 
double thurmanEuropeanCall(double S, double K, uint16_t expirationTime, double riskFreeRate, double volatility, uint16_t N) {
  double dt = (double)expirationTime/N/365;

  double u = exp(volatility*sqrt(dt));
  double d = 1.0/u;
  double p = (exp(riskFreeRate*dt) - d)/(u-d);

  std::vector<double> C;
  for (int i = 0; i < N+1; ++i) {
    C.push_back(std::max(S*pow(u, 2*i - N) - K, 0.0));
  }

  for (int i = N-1; i >= 0; --i) {
    for (int j = 0; j < i+1; ++j) {
      C[j] = exp(-riskFreeRate*dt)*(p*C[j+1] + (1-p)*C[j]);
    }
  }

  return C[0];
}