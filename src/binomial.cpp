#include <cstdint>
#include <math.h>
#include <vector>

#include "binomial.h"

/*
 * T -- expiration time
 * S -- stock price
 * K -- strike price
 * q -- dividend yield
 * n -- height of the binomial tree
 * 
 * Source: https://en.wikipedia.org/wiki/Binomial_options_pricing_model
 */
double americanPut(uint16_t T, double S, double K, double r, double sigma, double q, uint16_t n) {
  double deltaT = T / n;
  double up = exp(sigma * sqrt(deltaT));
  double p0 = (up*exp(-q * deltaT) - exp(-r * deltaT)) / (pow(up, 2) - 1);
  double p1 = exp(-r * deltaT) - p0;

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
 * q -- dividend yield
 * n -- height of the binomial tree
 * 
 * Source: https://en.wikipedia.org/wiki/Binomial_options_pricing_model
 */
double americanCall(uint16_t T, double S, double K, double r, double sigma, double q, uint16_t n) {
  double deltaT = T / n;
  double up = exp(sigma * sqrt(deltaT));
  double p0 = (up*exp(-q * deltaT) - exp(-r * deltaT)) / (pow(up, 2) - 1);
  double p1 = exp(-r * deltaT) - p0;

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