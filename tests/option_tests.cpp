#include <gtest/gtest.h>
#include "option_pricing/option.h"

#include <stdexcept>

using namespace option_pricing;

TEST(Option_Tests, Call_Construction)
{
    auto expected_expiry = std::chrono::year_month_day{std::chrono::year{2027}, std::chrono::month{9}, std::chrono::day{23}};
    Option call{OptionType::Call, 100, std::chrono::year_month_day{std::chrono::year{2027}, std::chrono::month{9}, std::chrono::day{23}}};
    EXPECT_EQ(call.get_option_type(), OptionType::Call);
    EXPECT_EQ(call.get_strike(), 100);
    EXPECT_EQ(call.get_expiry(),expected_expiry);

}

TEST(Option_Tests, Invalid_Strike)
{
    auto construct_invalid = []()
    {
        Option call{
            OptionType::Call,
            0,
            std::chrono::year_month_day{
                std::chrono::year{2027},
                std::chrono::month{9},
                std::chrono::day{23}
            }
        };
    };

    EXPECT_THROW(construct_invalid(), std::invalid_argument);
}

TEST(Option_Tests, Invalid_Date)
{
    auto construct_invalid = []()
    {
        Option call{
            OptionType::Call,
            0,
            std::chrono::year_month_day{
                std::chrono::year{2027},
                std::chrono::month{9},
                std::chrono::day{31}
            }
        };
    };

    EXPECT_THROW(construct_invalid(), std::invalid_argument);
}

TEST(Option_Tests, Invalid_Option_Type)
{
    auto construct_invalid = []()
    {
        Option call{
            static_cast<OptionType>(3),
            0,
            std::chrono::year_month_day{
                std::chrono::year{2027},
                std::chrono::month{9},
                std::chrono::day{23}
            }
        };
    };

    EXPECT_THROW(construct_invalid(), std::invalid_argument);
}