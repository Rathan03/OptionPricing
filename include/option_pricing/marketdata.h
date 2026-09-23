#pragma once
#include <chrono>

namespace option_pricing
{
    class MarketData
    {
        public:
            MarketData(double spot, double vol, double risk_free_rate, std::chrono::system_clock::time_point timestamp);
            double get_spot() const;
            double get_vol() const;
            double get_rate() const;
            std::chrono::system_clock::time_point get_timestamp() const;

        private:
            double spot;
            double vol;
            double risk_free_rate;
            std::chrono::system_clock::time_point timestamp;
    };
}