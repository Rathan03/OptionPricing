#include "option_pricing/option.h"

#include <stdexcept>

namespace option_pricing
{
    Option::Option(OptionType option_type, double strike, std::chrono::year_month_day expiry):
        option_type{option_type},
        strike{strike},
        expiry{expiry}
    {
        if (strike <= 0)
        {
            throw std::invalid_argument("Strike price must be positive");
        }
        if (!expiry.ok())
        {
            throw std::invalid_argument("Expiry must be a valid date.");
        }
        if (option_type != OptionType::Call && option_type != OptionType::Put)
        {
            throw std::invalid_argument("Must be a valid option type.");
        }
    }

    OptionType Option::get_option_type() const
    {
        return option_type;
    }

    double Option::get_strike() const
    {
        return strike;
    }

    std::chrono::year_month_day Option::get_expiry() const
    {
        return expiry;
    }
}