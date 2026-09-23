#include "option_pricing/marketdata.h"
#include <stdexcept>

namespace option_pricing
{
    MarketData::MarketData(double spot, double vol, double risk_free_rate, std::chrono::system_clock::time_point timestamp):
        spot{spot},
        vol{vol},
        risk_free_rate{risk_free_rate},
        timestamp{timestamp}
    {
        if (spot <= 0)
        {
            throw std::invalid_argument("Spot price must be positive");
        }
        if (vol <= 0)
        {
            throw std::invalid_argument("Volatility must be positive");
        }   
    }

    double MarketData::get_spot() const
    {
        return spot;
    }

    double MarketData::get_vol() const
    {
        return vol;
    }

    double MarketData::get_rate() const
    {
        return risk_free_rate;
    }

    std::chrono::system_clock::time_point MarketData::get_timestamp() const
    {
        return timestamp;
    }
}
