#include <cstdint>

double europeanCall(uint16_t steps, uint16_t expirationTime, double S, double K, double riskFreeRate, double volatility, double dividend_yield);

// // Zubair european call option
double zubairBinomial(uint16_t steps, uint16_t expirationTime, double S, double K, double riskFreeRate, double volatility);

double thurmanEuropeanCall(double S, double K, uint16_t expirationTime, double riskFreeRate, double volatility, uint16_t N);