#include "option_pricing/blackscholes.h"

#include <numbers>
#include <cmath>
#include <algorithm>

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

    BlackScholes::ComputationParameters BlackScholes::calculate_parameters(const Option& option) const
    {
        ComputationParameters params;
        params.T = actual_365(option);
        if (params.T <=0)
        {
            throw std::invalid_argument("Option has already expired.");
        }
        params.d1 = (std::log(market_data.get_spot()/option.get_strike()) + (market_data.get_rate() + 0.5 * market_data.get_vol() * market_data.get_vol()) * params.T) / (market_data.get_vol() * std::sqrt(params.T));
        params.d2 = params.d1 - market_data.get_vol() * std::sqrt(params.T);
        return params;
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

        if (T<0)
        {
            throw std::domain_error("Option has already expired in the past");
        } else if (T == 0)
        {
            int put_call_sign = option.get_option_type() == OptionType::Call ? 1 : -1;
            return std::max(put_call_sign * (market_data.get_spot()-option.get_strike()),.0);
        }

        auto [_,d1,d2] = calculate_parameters(option);

        if (option.get_option_type() == OptionType::Call)
        {
            return market_data.get_spot() * normal_cdf(d1)-option.get_strike() * std::exp(- market_data.get_rate() * T) * normal_cdf(d2);
        }

        return option.get_strike() * std::exp(- market_data.get_rate() * T) * normal_cdf(-d2) - market_data.get_spot() * normal_cdf(-d1);
    }

    // Greeks

    double BlackScholes::delta(const Option& option) const
    {
        auto [T, d1, d2] = calculate_parameters(option);
        if (option.get_option_type() == OptionType::Call)
        {
            return normal_cdf(d1);
        }

        return -normal_cdf(-d1);
    }

    double BlackScholes::gamma(const Option& option) const
    {
        auto [T,d1,d2] = calculate_parameters(option);
        return normal_pdf(d1)/(market_data.get_spot() * market_data.get_vol() * std::sqrt(T));
    }

    double BlackScholes::vega(const Option& option) const
    {   
        auto [T,d1,d2] = calculate_parameters(option);
        return normal_pdf(d1) * market_data.get_spot() * std::sqrt(T);
    }

    double BlackScholes::theta(const Option& option) const
    {   
        int sign = option.get_option_type() == OptionType::Call ? 1 : -1;
        auto [T,d1,d2] = calculate_parameters(option);

        return -(market_data.get_spot() * normal_pdf(d1) * market_data.get_vol())/(2 * std::sqrt(T))
               - sign * market_data.get_rate() * option.get_strike() * std::exp(- market_data.get_rate() * T) * normal_cdf(sign * d2);
    }

    double BlackScholes::rho(const Option& option) const
    {   
        int sign = option.get_option_type() == OptionType::Call ? 1 : -1;
        auto [T,d1,d2] = calculate_parameters(option);

        return sign * option.get_strike() * T * std::exp(- market_data.get_rate() * T) * normal_cdf(sign * d2);
    }

}