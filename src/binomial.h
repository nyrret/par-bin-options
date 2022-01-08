#include <cstdint>

double europeanCall(uint16_t steps, double S, double K, double riskFreeRate, double voltility, double dividend_yield);

// // wikipedia implementations
// double americanPut(uint16_t T, double S, double K, double riskFreeRate, double voltility, double dividend_yield);
// double americanCall(uint16_t T, double S, double K, double riskFreeRate, double voltility, double dividend_yield);
// 
// // Zubair american call option
// double zubairBinomial(double S, double K, uint16_t steps, double riskFreeRate, double voltility, double dt);