#include <cstdint>

double americanPut(uint16_t T, double S, double K, double risk_free_rate, double voltility, double dividend_yield);
double americanCall(uint16_t T, double S, double K, double risk_free_rate, double voltility, double dividend_yield);