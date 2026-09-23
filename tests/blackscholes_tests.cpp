#include <gtest/gtest.h>
#include "option_pricing/option.h"
#include "option_pricing/marketdata.h"
#include "option_pricing/blackscholes.h"

#include <stdexcept>
#include <cmath>

std::chrono::system_clock::time_point timestamp_current{
    std::chrono::milliseconds(1790166997000)
};
std::chrono::system_clock::time_point timestamp_year_on{
    std::chrono::seconds(1821706050)
};

using namespace option_pricing;

MarketData market_data{100,0.2,0.05, timestamp_current};
Option call{OptionType::Call, 100, std::chrono::year_month_day{std::chrono::year{2027}, std::chrono::month{9}, std::chrono::day{23}}};
Option put{OptionType::Put, 100, std::chrono::year_month_day{std::chrono::year{2027}, std::chrono::month{9}, std::chrono::day{23}}};
BlackScholes model{market_data};

TEST(BlackScholes_Test, Time_to_Expiry)
{
    EXPECT_NEAR(model.actual_365(call), 1.0, 1/364.0);
}

TEST(BlackScholes_Test, Call_Price)
{
    EXPECT_NEAR(model.option_price(call), 10.4506, 0.0001);
}

TEST(BlackScholes_Test, Put_Price)
{
    EXPECT_NEAR(model.option_price(put), 5.5735, 0.0001);
}

TEST(BlackScholes_Test, Put_Call_Parity)
{
    EXPECT_NEAR(market_data.get_spot()-call.get_strike() * std::exp(- market_data.get_rate() * model.actual_365(call)), model.option_price(call) - model.option_price(put), 1e-5);
}

TEST(BlackScholes_Test, Call_Delta)
{
    EXPECT_NEAR(model.delta(call), 0.6368, 1e-4);
}

TEST(BlackScholes_Test, Put_Delta)
{
    EXPECT_NEAR(model.delta(put), -0.3632, 1e-4);
}

TEST(BlackScholes_Test, Call_Gamma)
{
    EXPECT_NEAR(model.gamma(call), 0.018762, 1e-5);
}

TEST(BlackScholes_Test, Put_Gamma)
{
    EXPECT_NEAR(model.gamma(put), 0.018762, 1e-5);
}

TEST(BlackScholes_Test, Call_Vega)
{
    EXPECT_NEAR(model.vega(call), 37.5240, 1e-4);
}

TEST(BlackScholes_Test, Put_Vega)
{
    EXPECT_NEAR(model.vega(put), 37.5240, 1e-4);
}

TEST(BlackScholes_Test, Call_Theta)
{
    EXPECT_NEAR(model.theta(call), -6.4140, 1e-4);
}

TEST(BlackScholes_Test, Put_Theta)
{
    EXPECT_NEAR(model.theta(put), -1.6579, 1e-4);
}

TEST(BlackScholes_Test, Call_Rho)
{
    EXPECT_NEAR(model.rho(call), 53.2325, 1e-4);
}

TEST(BlackScholes_Test, Put_Rho)
{
    EXPECT_NEAR(model.rho(put), -41.8905, 1e-4);
}