#include <iostream>
#include "option_pricing/marketdata.h"
#include "option_pricing/option.h"
#include "option_pricing/blackscholes.h"

using namespace option_pricing;

int main()
{
    try
    {
        Option option{OptionType::Call, 100, std::chrono::year_month_day{std::chrono::year{2027}, std::chrono::month{9}, std::chrono::day{23}}};
        MarketData market_data{100,0.2,0.05, std::chrono::system_clock::now()};
        BlackScholes model{market_data};
        std::cout << model.normal_cdf(-1) <<'\n';

    } catch (const std::exception& e)
    {
        std::cout << e.what() <<'\n';
    }
    
}