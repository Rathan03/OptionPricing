#include <gtest/gtest.h>
#include "option_pricing/marketdata.h"

#include <stdexcept>

using namespace option_pricing;

TEST(MarketData_Tests, MarketData_Construction)
{
    auto expected_timestamp = std::chrono::system_clock::now();
    MarketData market_data{100,0.2,0.05, std::chrono::system_clock::now()};
    EXPECT_EQ(market_data.get_rate(), 0.05);
    EXPECT_EQ(market_data.get_spot(), 100);
    EXPECT_EQ(market_data.get_vol(), 0.2);
    EXPECT_EQ(market_data.get_timestamp(), expected_timestamp);

}