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