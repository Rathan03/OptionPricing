#pragma once
#include "option_pricing/marketdata.h"
#include "option_pricing/option.h"

namespace option_pricing
{
    class BlackScholes
    {
        public:
            BlackScholes(const MarketData& market_data);

            double actual_365(const Option& option) const;
            double option_price(const Option& option) const;
        
        private:
            const MarketData& market_data;

            double d1(const Option& option) const;
            double d2(const Option& option) const;
        
        public:
            double normal_cdf(double x) const;
    };
}