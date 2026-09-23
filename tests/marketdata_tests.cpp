#include <gtest/gtest.h>
#include "option_pricing/marketdata.h"

#include <stdexcept>

using namespace option_pricing;

TEST(MarketData_Tests, MarketData_Construction)
{
    auto expected_timestamp = std::chrono::system_clock::now();
    MarketData market_data{100,0.2,0.05, expected_timestamp};
    EXPECT_EQ(market_data.get_rate(), 0.05);
    EXPECT_EQ(market_data.get_spot(), 100);
    EXPECT_EQ(market_data.get_vol(), 0.2);
    EXPECT_EQ(market_data.get_timestamp(), expected_timestamp);

}

TEST(MarketData_Tests, Invalid_Spot)
{
    auto construct_invalid = []()
    {
        MarketData market_data{0,0.2,0.05, std::chrono::system_clock::now()};
    };

    EXPECT_THROW(construct_invalid(), std::invalid_argument);
}

TEST(MarketData_Tests, Invalid_Vol)
{
    auto construct_invalid = []()
    {
        MarketData market_data{100,0,0.05, std::chrono::system_clock::now()};
    };

    EXPECT_THROW(construct_invalid(), std::invalid_argument);
}

TEST(MarketData_Tests, Negative_Rate)
{
    MarketData market_data{100,0.2,-0.05, std::chrono::system_clock::now()};
    EXPECT_EQ(market_data.get_rate(), -0.05);
}