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
 * Partially adapted from Zubair
 */
double europeanCall(uint16_t steps, uint16_t expirationTime, double S, double K, double riskFreeRate, double voltility, double dividend_yield) {
  double deltaT = (double)expirationTime/steps/365;
  double dx = voltility * sqrt(deltaT);
  double up = exp(voltility * sqrt(deltaT));
  std::cout << "up: " << up << std::endl;
  double down = 1/up;

  // zubair
  // double pu = (exp(riskFreeRate*deltaT)-down)/(up-down);
  double drift_per_step = (riskFreeRate - dividend_yield - 0.5 * voltility * voltility) * deltaT;
  double pu = 0.5 + 0.5 * drift_per_step / dx;
  double pd = 1-pu;

  // initial values at expiration time
  std::vector<double> p;
  for (int i = 0; i < steps+1; ++i) {
    std::cout << "up: " << up << " 2*i: " << 2*i << " steps: " << steps << std::endl;
    std::cout << pow(up, 2*i - steps) << std::endl;
     p.push_back(S * pow(up, 2*i - steps) - K);
    // p.push_back(S * pow(up, Nu - Nd) - K);
    if (p[i] < 0) {
        p[i] = 0;
    }
    std::cout << "p[" << i << "] = " << p[i] << std::endl;
  }

  // move to earlier times
  for (int j = steps; j >= 0; --j) {
    for (int i = 0; i < j; ++i) {
      // binomial value
      p[i] = (pu * p[i+1] + pd * p[i]) * exp(-riskFreeRate*deltaT);; //
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
// // Zubair paper  -- for European Call options, I believe
double zubairBinomial(double S, double K, uint16_t steps, double riskFreeRate, double voltility, double dt) {
  double u = exp(sqrt(dt)*voltility);
  double d = exp(sqrt(dt)*(-voltility));
  double pu = (exp(riskFreeRate*dt)-d)/(u-d);

  std::vector<double> optionArray;
  for (int i = 0; i < steps; ++i) {
    double assetPrice = S * pow(d, steps-i) * pow(u, i-1);
    optionArray.push_back(std::max(assetPrice - K, 0.0));
  }

  double pus = exp(-riskFreeRate*dt)*pu;
  double pds = exp(-riskFreeRate*dt)*(1-pu);

  // iteratively compute option price starting from leaf nodes
  for (int i = steps-1; i >= 0; --i) { // TODO: this loop in paper is weird
    for (int j = 0; j < i; ++j) {
      optionArray[j] = pus * optionArray[j+1] + pds * optionArray[j];
    }
  }
  return optionArray[0];
}

double thurmanEuropeanCall(double S, double K, double expirationTime, double riskFreeRate, double volatility, uint16_t N) {
  double dt = (1.0*expirationTime)/N;

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