#include <cstdint>
#include <iostream>
#include <math.h>
#include <vector>

#include <parlay/parallel.h>
#include <parlay/sequence.h>

namespace Binomial {
class OptionConfig {
  public:
    explicit OptionConfig(
      uint32_t steps,
      double deltaT,
      double S,
      double K,
      double riskFreeRate)
    : steps_{steps}, S_{S}, K_{K}, deltaT_{deltaT}, riskFreeRate_{riskFreeRate} {}

    double getExerciseValue(int currentStep, int numUpMovements);
    double getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements);

    inline double getBinomialValue(double currentValue, double futureValue, int currentStep, int numUpMovements) {
      return (pu_ * futureValue + pd_ * currentValue)*exp(-riskFreeRate_*deltaT_);
    }
    inline double getSpotPrice(int currentStep, int numUpMovements) {
      return S_ * pow(up_, 2*currentStep - (numUpMovements - 1));
    }

  protected:
    uint32_t steps_;
    double deltaT_;
    double S_;  // initial price
    double K_;  // strike price
    double riskFreeRate_;
    double pu_;
    double pd_;
    double up_;
};

// ==========QuantLib=======================

class QuantLibConfig : public OptionConfig {
  public:
    explicit QuantLibConfig(
      uint32_t steps,
      double deltaT,
      double S,
      double K,
      double riskFreeRate,
      double volatility,
      double dividendYield
    ) : OptionConfig(steps, deltaT, S, K, riskFreeRate) {
      double dx = volatility * sqrt(deltaT);
      double drift_per_step = (riskFreeRate - dividendYield - 0.5 * volatility * volatility) * deltaT;
      pu_ = 0.5 + 0.5 * drift_per_step / dx;
      pd_ = 1-pu_;

      up_ = exp(volatility * sqrt(deltaT));
    }
};

class QLEuropeanCall: public QuantLibConfig {
  public: 
    explicit QLEuropeanCall(
      uint32_t steps,
      double deltaT,
      double S,
      double K,
      double riskFreeRate,
      double volatility,
      double dividendYield
    ) : QuantLibConfig(steps, deltaT, S, K, riskFreeRate, volatility, dividendYield) {}

    inline double getExerciseValue(int currentStep, int numUpMovements) {
      return std::max(getSpotPrice(currentStep, numUpMovements) - K_, 0.0);
    }
    inline double getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements) {
      return getBinomialValue(currentValue, futureValue, currentStep, numUpMovements);
    }
};

class QLEuropeanPut: public QuantLibConfig {
  public: 
    explicit QLEuropeanPut(
      uint32_t steps,
      double deltaT,
      double S,
      double K,
      double riskFreeRate,
      double volatility,
      double dividendYield
    ) : QuantLibConfig(steps, deltaT, S, K, riskFreeRate, volatility, dividendYield) {}

    double getExerciseValue(int currentStep, int numUpMovements);
    double getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements);
};

class QLAmericanCall: public QuantLibConfig {
  public: 
    explicit QLAmericanCall(
      uint32_t steps,
      double deltaT,
      double S,
      double K,
      double riskFreeRate,
      double volatility,
      double dividendYield
    ) : QuantLibConfig(steps, deltaT, S, K, riskFreeRate, volatility, dividendYield) {}

    double getExerciseValue(int currentStep, int numUpMovements);
    double getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements);
};

class QLAmericanPut: public QuantLibConfig {
  public: 
    explicit QLAmericanPut(
      uint32_t steps,
      double deltaT,
      double S,
      double K,
      double riskFreeRate,
      double volatility,
      double dividendYield
    ) : QuantLibConfig(steps, deltaT, S, K, riskFreeRate, volatility, dividendYield) {}

    double getExerciseValue(int currentStep, int numUpMovements);
    double getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements);
};

// ==============Zubair=======================

class ZubairConfig : public OptionConfig {
  public: 
    explicit ZubairConfig(
      uint32_t steps,
      double deltaT,
      double S,
      double K,
      double riskFreeRate,
      double volatility,
      double dividendYield
    ) : OptionConfig(steps, deltaT, S, K, riskFreeRate) {
      up_ = exp(volatility * sqrt(deltaT));
      double down = 1.0/up_;

      pu_ = (exp((riskFreeRate-dividendYield)*deltaT) - down)/(up_-down);
      pd_ = 1-pu_;
    }
};

class ZubairEuropeanCall: public ZubairConfig {
  public: 
    explicit ZubairEuropeanCall(
      uint32_t steps,
      double deltaT,
      double S,
      double K,
      double riskFreeRate,
      double volatility,
      double dividendYield
    ) : ZubairConfig(steps, deltaT, S, K, riskFreeRate, volatility, dividendYield) {}

    double getExerciseValue(int currentStep, int numUpMovements);
    double getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements);
};

class ZubairEuropeanPut: public ZubairConfig {
  public: 
    explicit ZubairEuropeanPut(
      uint32_t steps,
      double deltaT,
      double S,
      double K,
      double riskFreeRate,
      double volatility,
      double dividendYield
    ) : ZubairConfig(steps, deltaT, S, K, riskFreeRate, volatility, dividendYield) {}

    double getExerciseValue(int currentStep, int numUpMovements);
    double getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements);
};

class ZubairAmericanCall: public ZubairConfig {
  public: 
    explicit ZubairAmericanCall(
      uint32_t steps,
      double deltaT,
      double S,
      double K,
      double riskFreeRate,
      double volatility,
      double dividendYield
    ) : ZubairConfig(steps, deltaT, S, K, riskFreeRate, volatility, dividendYield) {}

    double getExerciseValue(int currentStep, int numUpMovements);
    double getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements);
};

class ZubairAmericanPut: public ZubairConfig {
  public: 
    explicit ZubairAmericanPut(
      uint32_t steps,
      double deltaT,
      double S,
      double K,
      double riskFreeRate,
      double volatility,
      double dividendYield
    ) : ZubairConfig(steps, deltaT, S, K, riskFreeRate, volatility, dividendYield) {}

    double getExerciseValue(int currentStep, int numUpMovements);
    double getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements);
};

template <class Config>
double binomialTraversal(uint32_t steps, uint16_t expirationTime, double S, double K, double riskFreeRate, double volatility, double dividendYield = 0) {
  static_assert(std::is_base_of<OptionConfig, Config>::value,
    "Config must be a derived class of OptionConfig");

  double deltaT = (double)expirationTime/steps/365;

  Config config = Config{steps, deltaT, S, K, riskFreeRate, volatility, dividendYield};

  // initial values at expiration time
  std::vector<double> p;
  for (int i = 0; i < steps+1; ++i) {
    p.push_back(config.getExerciseValue(i, steps+1));
    if (p[i] < 0) {
      p[i] = 0;
    }
  }

  for (int j = steps; j >= 0; --j) {
    for (int i = 0; i < j; ++i) {
      // binomial value
      p[i] = config.getNodeValue(p[i], p[i+1], i, j);
    }
  }

  return p[0];
}

template <class Config>
double parallelBinomialTraversal(uint32_t steps, uint16_t expirationTime, double S, double K, double riskFreeRate, double volatility, double dividendYield = 0) {
  static_assert(std::is_base_of<OptionConfig, Config>::value,
    "Config must be a derived class of OptionConfig");

  double deltaT = (double)expirationTime/steps/365;

  Config config = Config{steps, deltaT, S, K, riskFreeRate, volatility, dividendYield};

  // initial values at expiration time
  std::vector<double> p;
  for (int i = 0; i < steps+1; ++i) {
    p.push_back(config.getExerciseValue(i, steps+1));
    if (p[i] < 0) {
      p[i] = 0;
    }
  }

  // move to earlier times 
  std::vector<double> pastValues(steps+1);
  p.swap(pastValues);
  for (int j = steps; j >= 0; --j) {
    parlay::parallel_for(0, j, [&](int i) {
      // binomial value
      p[i] = config.getNodeValue(pastValues[i], pastValues[i+1], i, j);
    });
    p.swap(pastValues);
  }

  return p[0];
}
}  // namespace Binomial