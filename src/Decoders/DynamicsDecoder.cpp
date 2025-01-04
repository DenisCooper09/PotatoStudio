#include "Decoders/DynamicsDecoder.hpp"

namespace PotatoStudio::Decoders
{
    void DynamicsDecoder::SetParameters(const CalibrationData &calibration_data)
    {
        ParameterizedDecoder::SetParameters(calibration_data);
        m_BME280_Decoder.SetParameters(calibration_data);
        m_MPU6050_Decoder.SetParameters({MPU6050::AccelerometerFSR::G16, MPU6050::GyroscopeFSR::DEG500});
    }

    void DynamicsDecoder::Decode()
    {
        m_Decoded.clear();

        for (uint32_t i = 1; i < m_Encoded.size(); i += 24)
        {
            EncodedDynamicsSample encoded{};

            for (uint32_t j = i, k = 0; k < 24; ++j, ++k)
            {
                encoded.data[k] = m_Encoded[j];
            }

            m_MPU6050_Decoder.Set(encoded.mpu6050);
            m_BME280_Decoder.Set(encoded.bme280);

            m_MPU6050_Decoder.Decode();
            m_BME280_Decoder.Decode();

            DecodedDynamicsSample decoded{};

            decoded.bme280  = m_BME280_Decoder.Get();
            decoded.mpu6050 = m_MPU6050_Decoder.Get();

            m_Decoded.push_back(decoded);
        }

        Decoder::Decode();
    }
}
