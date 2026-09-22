#pragma once

#include <chrono>

namespace option_pricing
{
    enum class OptionType
    {
        Call,
        Put
    };

    class Option
    {
        public:
            Option(OptionType option_type, double strike, std::chrono::year_month_day expiry);
            OptionType get_option_type() const;
            double get_strike() const;
            std::chrono::year_month_day get_expiry() const;

        private:
            OptionType option_type;
            double strike;
            std::chrono::year_month_day expiry;
    }; 
}