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

            double delta(const Option& option) const;
            double gamma(const Option& option) const;
            double vega(const Option& option) const;
            double theta(const Option& option) const;
            double rho(const Option& option) const;
        
        private:
            const MarketData& market_data;

            double normal_cdf(double x) const;
            double normal_pdf(double x) const;
            
            struct ComputationParameters
            {
                double T;
                double d1;
                double d2;
            };
            ComputationParameters calculate_parameters(const Option& option) const;
    };
}

