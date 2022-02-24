#include <cstdint>

namespace Binomial {
double qlEuropeanCall(int steps, int expirationTime, double S, double K, double riskFreeRate, double volatility, double dividend_yield);
// double qlEuropeanCall(uint16_t steps, uint16_t expirationTime, double S, double K, double riskFreeRate, double volatility, double dividend_yield);
double zubairEuropeanCall(int N, int expirationTime, double S, double K, double riskFreeRate, double volatility, double dividendYield);
}  // namespace Binomial