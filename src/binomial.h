#include <cstdint>

double europeanCall(uint16_t steps, uint16_t expirationTime, double S, double K, double riskFreeRate, double voltility, double dividend_yield);

// // wikipedia implementations
// double americanPut(uint16_t T, double S, double K, double riskFreeRate, double voltility, double dividend_yield);
// double americanCall(uint16_t T, double S, double K, double riskFreeRate, double voltility, double dividend_yield);
// 
// // Zubair european call option
double zubairBinomial(double S, double K, uint16_t steps, double riskFreeRate, double voltility, double dt);