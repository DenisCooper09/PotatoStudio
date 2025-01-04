#pragma once

#include "Decoders/Decoder.hpp"
#include "Decoders/ParameterizedDecoder.hpp"
#include "Decoders/CalibrationDecoder.hpp"

namespace PotatoStudio::Decoders::BME280
{
    struct EncodedSample
    {
        int32_t pressure;
        int32_t temperature;
        int32_t humidity;
    };

    struct DecodedSample
    {
        double pressure;
        double temperature;
        double humidity;
    };

    class BME280_Decoder : public ParameterizedDecoder<EncodedSample, DecodedSample, CalibrationData>
    {
    public:
        void Decode() override;

    private:
        double CompensateTemperature(int32_t raw_temperature);
        double CompensatePressure(int32_t raw_pressure);
        double CompensateHumidity(int32_t raw_humidity);

    private:
        int32_t t_fine = 0;
    };
}
