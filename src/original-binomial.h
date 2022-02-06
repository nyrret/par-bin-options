#include <cstdint>

namespace Binomial {
double qlEuropeanCall(uint32_t steps, uint16_t expirationTime, double S, double K, double riskFreeRate, double volatility, double dividend_yield);
double zubairEuropeanCall(uint32_t N, uint16_t expirationTime, double S, double K, double riskFreeRate, double volatility, double dividendYield);
}  // namespace Binomial