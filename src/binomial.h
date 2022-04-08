#include <cstdint>
#include <iostream>
#include <math.h>
#include <vector>

#include "gettime.h"

#include <parlay/parallel.h>
#include <parlay/sequence.h>

namespace Binomial {
class OptionConfig {
  public:
    explicit OptionConfig(
      int steps,
      double deltaT,
      double S,
      double K,
      double riskFreeRate)
    : steps_{steps}, deltaT_{deltaT}, S_{S}, K_{K}, riskFreeRate_{riskFreeRate} {
      modifier_ = exp(-riskFreeRate*deltaT);
    }

    double getExerciseValue(int currentStep, int numUpMovements) const;
    double getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements) const;

    inline double getBinomialValue(double currentValue, double futureValue) const {
      return (pu_ * futureValue + pd_ * currentValue)*modifier_;
    }
    inline double getSpotPrice(int currentStep, int numUpMovements) const {
      return S_ * pow(up_, 2*currentStep - (numUpMovements - 1));
    }

  protected: 
    int steps_;
    double deltaT_;
    double S_;  // initial price
    double K_;  // strike price
    double riskFreeRate_;
    double pu_;
    double pd_;
    double up_;
    double modifier_;
};

// ==========QuantLib=======================

class QuantLibConfig : public OptionConfig {
  public:
    explicit QuantLibConfig(
      int steps,
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

class QLEuropeanCall : public QuantLibConfig { 
  public: 
    explicit QLEuropeanCall(
      int steps,
      double deltaT,
      double S,
      double K,
      double riskFreeRate,
      double volatility,
      double dividendYield
    ) : QuantLibConfig(steps, deltaT, S, K, riskFreeRate, volatility, dividendYield) {}

    inline double getExerciseValue(int currentStep, int numUpMovements) const {
      return std::max(S_ * pow(up_, 2*currentStep - (numUpMovements - 1)) - K_, 0.0);
    }
    inline double getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements) const {
      (void)currentStep;
      (void)numUpMovements;
      return (pu_ * futureValue + pd_ * currentValue)*modifier_;
    }
};

class QLEuropeanPut: public QuantLibConfig {
  public: 
    explicit QLEuropeanPut(
      int steps,
      double deltaT,
      double S,
      double K,
      double riskFreeRate,
      double volatility,
      double dividendYield
    ) : QuantLibConfig(steps, deltaT, S, K, riskFreeRate, volatility, dividendYield) {}

    inline double getExerciseValue(int currentStep, int numUpMovements) const {
      return std::max(K_ - getSpotPrice(currentStep, numUpMovements), 0.0);
    }
    
    inline double getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements) const {
      (void)currentStep;
      (void)numUpMovements;
      return getBinomialValue(currentValue, futureValue);
    }
};

class QLAmericanCall: public QuantLibConfig {
  public: 
    explicit QLAmericanCall(
      int steps,
      double deltaT,
      double S,
      double K,
      double riskFreeRate,
      double volatility,
      double dividendYield
    ) : QuantLibConfig(steps, deltaT, S, K, riskFreeRate, volatility, dividendYield) {}

    inline double getExerciseValue(int currentStep, int numUpMovements) const {
      return std::max(getSpotPrice(currentStep, numUpMovements) - K_, 0.0);
    }
    
    inline double getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements) const {
      return std::max(getExerciseValue(currentStep, numUpMovements), getBinomialValue(currentValue, futureValue));
    }

};

class QLAmericanPut: public QuantLibConfig {
  public: 
    explicit QLAmericanPut(
      int steps,
      double deltaT,
      double S,
      double K,
      double riskFreeRate,
      double volatility,
      double dividendYield
    ) : QuantLibConfig(steps, deltaT, S, K, riskFreeRate, volatility, dividendYield) {}

    inline double getExerciseValue(int currentStep, int numUpMovements) const {
      return std::max(K_ - getSpotPrice(currentStep, numUpMovements), 0.0);
    }

    inline double getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements) const {
      return std::max(getExerciseValue(currentStep, numUpMovements), getBinomialValue(currentValue, futureValue));
    }
};

// ==============Zubair=======================

class ZubairConfig : public OptionConfig {
  public: 
    explicit ZubairConfig(
      int steps,
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
      int steps,
      double deltaT,
      double S,
      double K,
      double riskFreeRate,
      double volatility,
      double dividendYield
    ) : ZubairConfig(steps, deltaT, S, K, riskFreeRate, volatility, dividendYield) {}

    inline double getExerciseValue(int currentStep, int numUpMovements) const {
      return std::max(getSpotPrice(currentStep, numUpMovements) - K_, 0.0);
    }

    inline double getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements) const {
      (void)currentStep;
      (void)numUpMovements;
      return getBinomialValue(currentValue, futureValue);
    }

};

class ZubairEuropeanPut: public ZubairConfig {
  public: 
    explicit ZubairEuropeanPut(
      int steps,
      double deltaT,
      double S,
      double K,
      double riskFreeRate,
      double volatility,
      double dividendYield
    ) : ZubairConfig(steps, deltaT, S, K, riskFreeRate, volatility, dividendYield) {}

    inline double getExerciseValue(int currentStep, int numUpMovements) const {
      return std::max(K_ - getSpotPrice(currentStep, numUpMovements), 0.0);
    }

    inline double getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements) const {
      (void)currentStep;
      (void)numUpMovements;
      return getBinomialValue(currentValue, futureValue);
    }

};

class ZubairAmericanCall: public ZubairConfig {
  public: 
    explicit ZubairAmericanCall(
      int steps,
      double deltaT,
      double S,
      double K,
      double riskFreeRate,
      double volatility,
      double dividendYield
    ) : ZubairConfig(steps, deltaT, S, K, riskFreeRate, volatility, dividendYield) {}

    inline double getExerciseValue(int currentStep, int numUpMovements) const {
      return std::max(getSpotPrice(currentStep, numUpMovements) - K_, 0.0);
    }

    inline double getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements) const {
      return std::max(getExerciseValue(currentStep, numUpMovements), getBinomialValue(currentValue, futureValue));
    }

};

class ZubairAmericanPut: public ZubairConfig {
  public: 
    explicit ZubairAmericanPut(
      int steps,
      double deltaT,
      double S,
      double K,
      double riskFreeRate,
      double volatility,
      double dividendYield
    ) : ZubairConfig(steps, deltaT, S, K, riskFreeRate, volatility, dividendYield) {}

    inline double getExerciseValue(int currentStep, int numUpMovements) const {
      return std::max(K_ - getSpotPrice(currentStep, numUpMovements), 0.0);
    }

    inline double getNodeValue(double currentValue, double futureValue, int currentStep, int numUpMovements) const {
      return std::max(getExerciseValue(currentStep, numUpMovements), getBinomialValue(currentValue, futureValue));
    }
};

template <class Config>
double binomialTraversal(int steps, int expirationTime, double S, double K, double riskFreeRate, double volatility, double dividendYield = 0) {
  static_assert(std::is_base_of<OptionConfig, Config>::value,
    "Config must be a derived class of OptionConfig");

  const double deltaT = (double)expirationTime/steps/365;

  const Config config = Config{
    steps, deltaT, S, K, riskFreeRate, volatility, dividendYield};

  // initial values at expiration time
  std::vector<double> p;
  for (int i = 0; i < steps+1; ++i) {
    p.push_back(config.getExerciseValue(i, steps+1)); 
    if (p[i] < 0) {
      p[i] = 0;
    }
  }

  // move to earlier times 
  for (int j = steps; j >= 0; --j) {
    for (int i = 0; i < j; ++i) {
      // binomial value
      p[i] = config.getNodeValue(p[i], p[i+1], i, j);
    }
  }

  return p[0];
}

template <class Config>
double parallelBinomialTraversal(int steps, int expirationTime, double S, double K, double riskFreeRate, double volatility, double dividendYield = 0) {
  static_assert(std::is_base_of<OptionConfig, Config>::value,
    "Config must be a derived class of OptionConfig");

  const double deltaT = (double)expirationTime/steps/365;

  const Config config = Config{
    steps, deltaT, S, K, riskFreeRate, volatility, dividendYield};

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

// ==========================================================
// =============Stencil Computation==========================
// ==========================================================

// level -- how many levels deep bottom of this triangle is
//          (top point in entire stencil computation is at level 1)
template <class Config>
inline void stencilTriangle(
  std::vector<double> &p, int m1, bool isOnBottom, int level, const Config &config) {
  for (int i = 0; i < m1-1; i++) {  // number of rows in triangle to look at
    for (int j = 0; j < m1-i-1; j++) {  // elts in that row
      p[j] = config.getNodeValue(
        p[j], p[j+1], j, level-isOnBottom-i);
    }
  }
}

// level -- how many levels deep bottom of this rhombus is
//          (top point in entire stencil computation is at level 1)
template <class Config>
inline void stencilRhombus(
  std::vector<double> &p, 
  int startIndex, 
  int m1, 
  int m2, 
  int level,
  bool isOnBottom,
  const Config &config
) {
  for (int i = 0; i < m1-1; i++) {
    for (int j = 0; j < m2; j++) {
      p[startIndex+j+m1-i-2] = config.getNodeValue(
        p[startIndex+j+m1-i-2], 
        p[startIndex+m1+j-i-1], 
        startIndex+j+m1-i-2, 
        level-isOnBottom-i 
      );
    }
  }
}

template <class Config>
double stencilBinomialTraversal(int steps, int expirationTime, double S, double K, double riskFreeRate, double volatility, double dividendYield = 0) {
  static_assert(std::is_base_of<OptionConfig, Config>::value,
    "Config must be a derived class of OptionConfig");

  const double deltaT = (double)expirationTime/steps/365;

  const Config config = Config{
    steps, deltaT, S, K, riskFreeRate, volatility, dividendYield};

  // initial values at expiration time
  std::vector<double> p;
  for (int i = 0; i < steps+1; ++i) {
    p.push_back(config.getExerciseValue(i, steps+1));
    if (p[i] < 0) {
      p[i] = 0;
    }
  }

  // stencil computation
  // TODO -- compile-time constant, can take param at compile-time
  const int cacheCapacity = std::min(128000, steps);   
  const int blockSize = (cacheCapacity+1)/2; 
  const int numBlocks = (steps+1)/blockSize; 
  const int edgeBlockSize = (steps+1)%blockSize;

  stencilTriangle(p, blockSize, true, numBlocks*blockSize + edgeBlockSize, config);
  for (int i = 1; i < numBlocks; i++) {
    stencilRhombus(
      p, 
      (i-1)*blockSize + 1, 
      blockSize, 
      blockSize, 
      numBlocks*blockSize + edgeBlockSize,
      true,
      config
    );
    for (int j = 1; j <= i-1; j++) {
      stencilRhombus(
        p, 
        (i-j-1)*blockSize + 1, 
        blockSize+1, 
        blockSize, 
        (numBlocks-j)*blockSize + edgeBlockSize,
        false,
        config
      );
    }
    stencilTriangle(
      p, blockSize+1, false, (numBlocks-i)*blockSize + edgeBlockSize, config);
  }

  // extra blocks in case did not divide evenly
  if (edgeBlockSize > 0) {
    stencilRhombus(
      p, 
      (numBlocks-1)*blockSize + 1, 
      blockSize, 
      edgeBlockSize, 
      numBlocks*blockSize + edgeBlockSize, 
      true, 
      config
    );
    for (int i = 1; i < numBlocks; i++) {
      stencilRhombus(
        p, 
        (numBlocks-i-1)*blockSize + 1, 
        blockSize+1, 
        edgeBlockSize, 
        (numBlocks-i)*blockSize + edgeBlockSize, 
        false, 
        config
      );
    }
    stencilTriangle(p, edgeBlockSize+1, false, edgeBlockSize, config);
  }

  return p[0];
}  // end stencilBinomialTraversal

// =================================================
// ===============Parallel Stencil==================
// =================================================

// level -- how many levels deep bottom of this triangle is
//          (top point in entire stencil computation is at level 1)
template <class Config>
inline void parallelStencilTriangle(
  std::vector<double> &p, 
  std::vector<double> &edgePoints,
  int startIndex, 
  int m1, 
  int triangleSize,
  int level, 
  const Config &config
) {
  for (int i = 0; i < triangleSize-1; i++) {  // number of rows in triangle to look at
    for (int j = 0; j < triangleSize-i-1; j++) {  // elts in that row
      double value = config.getNodeValue(
        p[startIndex+j], p[startIndex+j+1], startIndex+j, level-1-i);  // -1 because all the triangles are on the bottom, so start one row up
      p[startIndex+j] = value;

      // point is on triangle left edge and not in leftmost triangle,
      // so later shapes will need to refer to these points
      if (startIndex != 0 && j == 0) {
        // +1 because we don't store the bottommost point in the triangle
        edgePoints[startIndex-m1+i+1] = value;
      }
    }
  }
}

// level -- how many levels deep the left bottom corner of this rhombus is
//          (top point in entire stencil computation is at level 1)
// startIndex -- where the left edge is
template <class Config>
inline void parallelStencilRhombus(
  std::vector<double> &p, 
  std::vector<double> &pastEdgePoints,
  std::vector<double> &currEdgePoints,
  int startIndex, 
  int m1, 
  int width,
  int level,
  const Config &config
) {
  // start at bottom right point, and go up to middle row
  // go left to right in each row
  for (int i = 0; i < m1; i++) {  // row 
    int rowLen = std::min(i+1, width);
    for (int j = 0; j < rowLen; j++) {  // column
      
      // point on the right edge -- need to look at edges array
      if (j == i) {  // first check to ensure not an edge block
        double value = config.getNodeValue(
          p[startIndex+(m1-i-1)+j],   // current value
          pastEdgePoints[startIndex+i],   // future value 
          startIndex+(m1-i-1)+j, 
          level+(m1-i-1) 
        );
        p[startIndex+(m1-i-1)+j] = value;
      } else {
        double value = config.getNodeValue(
          p[startIndex+(m1-i-1)+j],   // current value
          p[startIndex+(m1-i-1)+j+1],   // future value
          startIndex+(m1-i-1)+j, 
          level+(m1-i-1) 
        );
        p[startIndex+(m1-i-1)+j] = value;

        // on the left edge of rhombus with other rhombuses to the left of it
        if (startIndex != 0 && i == m1-1 && j == 0) {
          currEdgePoints[startIndex-m1] = value;
        }
      } 
    }
  }

  // up above middle row until top point
  for (int i = 0; i < width-1; i++) {  // row
    int rowLen = std::min(m1-i-1, width-i-1);
    for (int j = 0; j < rowLen; j++) {  // column
      double value = config.getNodeValue(
        p[startIndex+j],   // current value
        p[startIndex+j+1],   // future value
        startIndex+j,
        level-i-1   
      );
      p[startIndex+j] = value;

      // on left edge of rhombus with other rhombuses to left of it
      if (startIndex != 0 && j == 0) {
        currEdgePoints[startIndex-m1+i+1] = value;
      }
    }
  }
}

template <class Config>
double parallelStencilBinomialTraversal(int steps, int expirationTime, double S, double K, double riskFreeRate, double volatility, double dividendYield = 0) {
  static_assert(std::is_base_of<OptionConfig, Config>::value,
    "Config must be a derived class of OptionConfig");

  const double deltaT = (double)expirationTime/steps/365;

  const Config config = Config{
    steps, deltaT, S, K, riskFreeRate, volatility, dividendYield};

  // stencil computation
  // TODO -- compile-time constant, can take param at compile-time
  const int cacheCapacity = std::min(4000, steps);   
  const int blockSize = (cacheCapacity+1)/2; 
  const int numBlocks = (steps+1)/blockSize; 
  const int edgeBlockSize = (steps+1)%blockSize;

  // stores the points on the left edge of the previous row of shapes,
  // starting from the second shape in the row and indexing bottom to top
  std::vector<double> pastEdgePoints;
  pastEdgePoints.reserve(blockSize*(numBlocks-1)+edgeBlockSize);
  std::vector<double> currEdgePoints;
  currEdgePoints.reserve(blockSize*(numBlocks-1)+edgeBlockSize);

  // initial values at expiration time
  std::vector<double> p;
  for (int i = 0; i < steps+1; ++i) {
    p.push_back(config.getExerciseValue(i, steps+1));
    if (p[i] < 0) {
      p[i] = 0;
    }
  
    // the edge point of a triangle in the bottom left corner
    if (i != 0 && i % blockSize == 0) {
      pastEdgePoints[i-blockSize] = p[i];
    }
  }

  // compute bottom row of triangles
  int triangleLevel = numBlocks*blockSize + edgeBlockSize;
  for (int i = 0; i < numBlocks; i++) {
    parallelStencilTriangle(
      p, pastEdgePoints, i*blockSize, blockSize, blockSize, triangleLevel, config);
  }

  if (edgeBlockSize > 0) {
    parallelStencilTriangle(
      p, 
      pastEdgePoints, 
      numBlocks*blockSize, 
      blockSize, 
      edgeBlockSize, 
      triangleLevel, 
      config
    );
  }

  // rows are zero-indexed, 0 is bottom
  for (int row = 1; row < numBlocks+1; row++) {  
    // compute rhombuses in a row in the same loop (bottom to top)
    parlay::parallel_for(0, numBlocks-row, [&](int j) {
      parallelStencilRhombus(
        p, 
        pastEdgePoints,
        currEdgePoints,
        j*blockSize,
        blockSize,
        blockSize,
        (numBlocks-row)*blockSize + edgeBlockSize,
        config
      );
    });

    // do the edge block if needed
    if (edgeBlockSize > 0) {
      parallelStencilRhombus(
        p, 
        pastEdgePoints,
        currEdgePoints,
        (numBlocks-row)*blockSize,
        blockSize,
        edgeBlockSize,
        (numBlocks-row)*blockSize + edgeBlockSize,
        config
      );
    }

    pastEdgePoints.swap(currEdgePoints); 
  }

  return p[0];
}  // end parallelStencilBinomialTraversal
}  // namespace Binomial
