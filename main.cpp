#include <iostream>
#include <cmath>
#include "option_pricing/marketdata.h"
#include "option_pricing/option.h"
#include "option_pricing/blackscholes.h"

using namespace option_pricing;

int main()
{
    try
    {
        Option call{OptionType::Call, 100, std::chrono::year_month_day{std::chrono::year{2027}, std::chrono::month{9}, std::chrono::day{23}}};
        Option put{OptionType::Put, 100, std::chrono::year_month_day{std::chrono::year{2027}, std::chrono::month{9}, std::chrono::day{23}}};
        MarketData market_data{100,0.2,0.05, std::chrono::system_clock::now()};
        BlackScholes model{market_data};
        std::cout << model.option_price(call) - model.option_price(put) <<'\n';
        std::cout << market_data.get_spot()-call.get_strike() * std::exp(- market_data.get_rate() * model.actual_365(call)) <<'\n';

    } catch (const std::exception& e)
    {
        std::cout << e.what() <<'\n';
    }
    
}