#include "option_pricing/blackscholes.h"

#include <cmath>

namespace option_pricing
{
    BlackScholes::BlackScholes(const MarketData& market_data):
        market_data{market_data}
    {}

    double BlackScholes::actual_365(const Option& option) const
    {
        return static_cast<double>(option.days_to_expiry(market_data.get_timestamp()).count())/365.0;
    }

    double BlackScholes::d1(const Option& option) const
    {
        double vol = market_data.get_vol();
        double T = actual_365(option);
        return (std::log(market_data.get_spot()/option.get_strike()) + (market_data.get_rate() + 0.5 * vol * vol) * T) / (vol * std::sqrt(T));
    }

    double BlackScholes::d2(const Option& option) const
    {
        return d1(option) - market_data.get_vol() * std::sqrt(actual_365(option));
    }

    double BlackScholes::normal_cdf(double x) const
    {
        return 0.5 * std::erfc(- x / std::sqrt(2));
    }
}