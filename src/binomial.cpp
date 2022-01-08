#include <cstdint>
#include <iostream>
#include <math.h>
#include <vector>

#include "binomial.h"

/*
 * T -- expiration time
 * S -- stock price
 * K -- strike price
 * 
 * Adapted from https://en.wikipedia.org/wiki/Binomial_options_pricing_model
 */
double europeanCall(uint16_t steps, uint16_t expirationTime, double S, double K, double riskFreeRate, double voltility, double dividend_yield) {
  double deltaT = (double)expirationTime/steps;
  double up = exp(voltility * sqrt(deltaT));
  double down = 1/up;

  double p0 = (exp((riskFreeRate-dividend_yield)*deltaT) - down)/(up-down);
  double p1 = 1-p0;

  // initial values at expiration time
  std::vector<double> p;
  for (int i = 0; i < steps; ++i) {
    p.push_back(S * pow(up, 2*i - steps) - K);
    if (p[i] < 0) {
        p[i] = 0;
    }
  }

  // move to earlier times
  for (int j = steps-1; j >= 0; --j) {
    for (int i = 0; i < j; ++i) {
      // binomial value
      p[i] = p0 * p[i+1] + p1 * p[i];
    }
  }
  return p[0];
}


// /*
//  * T -- expiration time
//  * S -- stock price
//  * K -- strike price
//  * n -- height of the binomial tree
//  * 
//  * Source: https://en.wikipedia.org/wiki/Binomial_options_pricing_model
//  */
// double americanPut(uint16_t T, double S, double K, double riskFreeRate, double voltility, double dividend_yield) {
//   double deltaT = 1;
//   uint16_t n = T;
//   double up = exp(voltility * sqrt(deltaT));
//   double p0 = (up*exp(-dividend_yield * deltaT) - exp(-riskFreeRate * deltaT)) / (pow(up, 2) - 1);
//   double p1 = exp(-riskFreeRate * deltaT) - p0;
// 
//   // initial values at time T
//   std::vector<double> p;
//   for (int i = 0; i < n; ++i) {
//     p.push_back(K - S * pow(up, 2*i - n));
//     if (p[i] < 0) {
//         p[i] = 0;
//     }
//   }
// 
//   // move to earlier times
//   for (int j = n-1; j >= 0; --j) {
//     for (int i = 0; i < j; ++i) {
//       // binomial value
//       p[i] = p0 * p[i+1] + p1 * p[i];
// 
//       // exercise value
//       double exercise = K - S * pow(up, 2*i - j);
//       if (p[i] < exercise) {
//           p[i] = exercise;
//       }
//     }
//   }
//   return p[0];
// }
// 
// /*
//  * T -- expiration time
//  * S -- stock price
//  * K -- strike price
//  * n -- height of the binomial tree
//  * 
//  * Source: https://en.wikipedia.org/wiki/Binomial_options_pricing_model
//  */
// double americanCall(uint16_t T, double S, double K, double riskFreeRate, double voltility, double dividend_yield) {
//   double deltaT = 1;
//   uint16_t n = T;
//   double up = exp(voltility * sqrt(deltaT));
//   double p0 = (up*exp(-dividend_yield * deltaT) - exp(-riskFreeRate * deltaT)) / (pow(up, 2) - 1);
//   double p1 = exp(-riskFreeRate * deltaT) - p0;
// 
//   // initial values at time T
//   std::vector<double> p;
//   for (int i = 0; i < n; ++i) {
//     p.push_back(K - S * pow(up, 2*i - n));
//     if (p[i] < 0) {
//         p[i] = 0;
//     }
//   }
// 
//   // move to earlier times
//   for (int j = n-1; j >= 0; --j) {
//     for (int i = 0; i < j; ++i) {
//       // binomial value
//       p[i] = p0 * p[i+1] + p1 * p[i];
// 
//       // exercise value
//       double exercise = S * pow(up, 2*i - j) - K;
//       if (p[i] < exercise) {
//           p[i] = exercise;
//       }
//     }
//   }
//   return p[0];
// }
// 
// // Zubair paper  -- for Call options, I believe
// double zubairBinomial(double S, double K, uint16_t steps, double riskFreeRate, double voltility, double dt) {
//   double u = exp(sqrt(dt)*voltility);
//   double d = exp(sqrt(dt)*(-voltility));
//   double pu = (exp(riskFreeRate*dt)-d)/(u-d);
// 
//   std::vector<double> optionArray;
//   for (int i = 0; i < steps; ++i) {
//     double assetPrice = S * pow(d, steps-i) * pow(u, i-1);
//     optionArray.push_back(std::max(assetPrice - K, 0.0));
//   }
// 
//   double pus = exp(-riskFreeRate*dt)*pu;
//   double pds = exp(-riskFreeRate*dt)*(1-pu);
// 
//   // iteratively compute option price starting from leaf nodes
//   for (int i = steps; i >= 0; --i) {
//     for (int j = 0; j < i; ++j) {
//       optionArray[j] = pus * optionArray[j+1] + pds * optionArray[j];
//     }
//   }
//   return optionArray[0];
// }