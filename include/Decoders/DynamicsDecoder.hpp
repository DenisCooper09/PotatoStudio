#pragma once

#include "ParameterizedDecoder.hpp"
#include "MPU6050/MPU6050_Decoder.hpp"
#include "BME280/BME280_Decoder.hpp"

namespace PotatoStudio::Decoders
{
    union EncodedDynamicsSample
    {
        struct
        {
            MPU6050::EncodedSample mpu6050;
            BME280::EncodedSample  bme280;
        };

        uint8_t data[24];
    };

    struct DecodedDynamicsSample
    {
        MPU6050::DecodedSample mpu6050;
        BME280::DecodedSample  bme280;
    };

    class DynamicsDecoder : public ParameterizedDecoder<std::vector<uint8_t>, std::vector<DecodedDynamicsSample>, CalibrationData>
    {
    public:
        void SetParameters(const CalibrationData& calibration_data) override;
        void Decode() override;

    private:
        MPU6050::MPU6050_Decoder m_MPU6050_Decoder;
        BME280::BME280_Decoder   m_BME280_Decoder;
    };
}
