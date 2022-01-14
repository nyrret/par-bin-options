#include <iostream>
#include <ql/time/date.hpp>
// using namespace QuantLib;
// int main()
// {
// Date veryFirstDate(1, January, 1901);
// Date anotherVeryFirstDate(367);
// Date yetAnotherVeryFirstDate(veryFirstDate);
// std::cout << (Date(10, December, 1979)).weekday() << "\n";
// std::cout << veryFirstDate << "\n";
// std::cout << anotherVeryFirstDate << "\n";
// std::cout << yetAnotherVeryFirstDate << "\n";
// std::cout << Date::minDate() << "\n";
// std::cout << Date::maxDate() << "\n";
// return 0;
// }

// https://www.quantlib.org/install/macosx.shtml
// g++ -g -std=c++11 -I/usr/local/include/ -I/usr/local/include/boost qlibtest.cpp \
//     -o qlibtest -L/usr/local/lib/ -lQuantLib

#include <ql/quantlib.hpp>

using namespace QuantLib;

int main(int, char* []) {

// date set up
Calendar calendar = TARGET(); 
Date todaysDate(8, May, 2015);
Date settlementDate(8, May, 2015);
Settings::instance().evaluationDate() = todaysDate;

// option parameters
Option::Type type(Option::Call);
Real stock = 127.62;
Real strike = 130;
Spread dividendYield = 0.0163;
Rate riskFreeRate = 0.001;
Volatility volatility = 0.20;
Date maturity(15, Jan, 2016);
DayCounter dayCounter = Actual365Fixed();

boost::shared_ptr<Exercise> 
europeanExercise(new EuropeanExercise(maturity));

Handle<Quote> 
underlyingH(boost::shared_ptr<Quote>(new SimpleQuote(stock)));

// bootstrap the yield/dividend/vol curves
Handle<YieldTermStructure> flatTermStructure(boost::shared_ptr<YieldTermStructure>(
    new FlatForward(
        settlementDate,
        riskFreeRate,
        dayCounter)));

Handle<YieldTermStructure> flatDividendTS(boost::shared_ptr<YieldTermStructure>(
    new FlatForward(settlementDate,
        dividendYield,
        dayCounter)));

Handle<BlackVolTermStructure> flatVolTS(boost::shared_ptr<BlackVolTermStructure>(
    new BlackConstantVol(
        settlementDate,
        calendar,
        volatility,
        dayCounter)));

boost::shared_ptr<StrikedTypePayoff> payoff(
    new PlainVanillaPayoff(
        type,
        strike));

boost::shared_ptr<BlackScholesMertonProcess> bsmProcess(
    new BlackScholesMertonProcess(
        underlyingH,
        flatDividendTS,
        flatTermStructure,
        flatVolTS));

// our option is European-style
VanillaOption europeanOption(
    payoff,
    europeanExercise);

// computing the option price with the analytic Black-Scholes formulae
// europeanOption.setPricingEngine(boost::shared_ptr<PricingEngine>(
//     new AnalyticEuropeanEngine(
//         bsmProcess)));

int timeSteps=2;
// binomial model
europeanOption.setPricingEngine(ext::shared_ptr<PricingEngine>(
                new BinomialVanillaEngine<CoxRossRubinstein>(bsmProcess,timeSteps)));

double result = europeanOption.NPV();

// outputting
std::cout << "Option type = " << type << std::endl;
std::cout << "Maturity = " << maturity << std::endl;
std::cout << "Stock price = " << stock << std::endl;
std::cout << "Strike = " << strike << std::endl;
std::cout << "Risk-free interest rate = " << io::rate(riskFreeRate) << std::endl;
std::cout << "Dividend yield = " << io::rate(dividendYield) << std::endl;
std::cout << "Volatility = " << io::volatility(volatility) <<  std::endl << std::endl;
std::cout << "Time Steps = " << timeSteps <<  std::endl << std::endl;
std::cout<<"European Option value = " << result << std::endl;
return 0;
}