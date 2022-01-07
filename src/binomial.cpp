#include <cstdint>
#include <math.h>
#include <vector>

#include "binomial.h"

/*
 * T -- expiration time
 * S -- stock price
 * K -- strike price
 * n -- height of the binomial tree
 * 
 * Source: https://en.wikipedia.org/wiki/Binomial_options_pricing_model
 */
double americanPut(uint16_t T, double S, double K, double risk_free_rate, double voltility, double dividend_yield) {
  double deltaT = 1;
  uint16_t n = T;
  double up = exp(voltility * sqrt(deltaT));
  double p0 = (up*exp(-dividend_yield * deltaT) - exp(-risk_free_rate * deltaT)) / (pow(up, 2) - 1);
  double p1 = exp(-risk_free_rate * deltaT) - p0;

  // initial values at time T
  std::vector<double> p;
  for (int i = 0; i < n; ++i) {
    p.push_back(K - S * pow(up, 2*i - n));
    if (p[i] < 0) {
        p[i] = 0;
    }
  }

  // move to earlier times
  for (int j = n-1; j >= 0; --j) {
    for (int i = 0; i < j; ++i) {
      // binomial value
      p[i] = p0 * p[i+1] + p1 * p[i];

      // exercise value
      double exercise = K - S * pow(up, 2*i - j);
      if (p[i] < exercise) {
          p[i] = exercise;
      }
    }
  }
  return p[0];
}

/*
 * T -- expiration time
 * S -- stock price
 * K -- strike price
 * n -- height of the binomial tree
 * 
 * Source: https://en.wikipedia.org/wiki/Binomial_options_pricing_model
 */
double americanCall(uint16_t T, double S, double K, double risk_free_rate, double voltility, double dividend_yield) {
  double deltaT = 1;
  uint16_t n = T;
  double up = exp(voltility * sqrt(deltaT));
  double p0 = (up*exp(-dividend_yield * deltaT) - exp(-risk_free_rate * deltaT)) / (pow(up, 2) - 1);
  double p1 = exp(-risk_free_rate * deltaT) - p0;

  // initial values at time T
  std::vector<double> p;
  for (int i = 0; i < n; ++i) {
    p.push_back(K - S * pow(up, 2*i - n));
    if (p[i] < 0) {
        p[i] = 0;
    }
  }

  // move to earlier times
  for (int j = n-1; j >= 0; --j) {
    for (int i = 0; i < j; ++i) {
      // binomial value
      p[i] = p0 * p[i+1] + p1 * p[i];

      // exercise value
      double exercise = S * pow(up, 2*i - j) - K;
      if (p[i] < exercise) {
          p[i] = exercise;
      }
    }
  }
  return p[0];
}