#include "option_pricing/blackscholes.h"

#include <numbers>
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

    double BlackScholes::normal_pdf(double x) const
    {
        return (1/(std::sqrt(2 * std::numbers::pi))) * std::exp(-0.5 * x * x);
    }

    double BlackScholes::option_price(const Option& option) const
    {   
        double T = actual_365(option);
        double d1 = this->d1(option);
        double d2 = this->d2(option);

        if (option.get_option_type() == OptionType::Call)
        {
            return market_data.get_spot() * normal_cdf(d1)-option.get_strike() * std::exp(- market_data.get_rate() * T) * normal_cdf(d2);
        }

        return option.get_strike() * std::exp(- market_data.get_rate() * T) * normal_cdf(-d2) - market_data.get_spot() * normal_cdf(-d1);
    }

    // Greeks

    double BlackScholes::delta(const Option& option) const
    {
        if (option.get_option_type() == OptionType::Call)
        {
            return normal_cdf(d1(option));
        }

        return -normal_cdf(-d1(option));
    }

    double BlackScholes::gamma(const Option& option) const
    {
        return normal_pdf(d1(option))/(market_data.get_spot() * market_data.get_vol() * std::sqrt(actual_365(option)));
    }

    double BlackScholes::vega(const Option& option) const
    {
        return normal_pdf(d1(option)) * market_data.get_spot() * std::sqrt(actual_365(option));
    }

    double BlackScholes::theta(const Option& option) const
    {   
        int sign = option.get_option_type() == OptionType::Call ? 1 : -1;

        return -(market_data.get_spot() * normal_pdf(d1(option)) * market_data.get_vol())/(2 * std::sqrt(actual_365(option)))
               - sign * market_data.get_rate() * option.get_strike() * std::exp(- market_data.get_rate() * actual_365(option)) * normal_cdf(sign * d2(option));
    }

    double BlackScholes::rho(const Option& option) const
    {   
        int sign = option.get_option_type() == OptionType::Call ? 1 : -1;

        return sign * option.get_strike() * actual_365(option) * std::exp(- market_data.get_rate() * actual_365(option)) * normal_cdf(sign * d2(option));
    }
}