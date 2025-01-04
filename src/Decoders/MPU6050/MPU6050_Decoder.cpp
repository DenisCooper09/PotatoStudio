#include "Decoders/MPU6050/MPU6050_Decoder.hpp"

namespace PotatoStudio::Decoders::MPU6050
{
    void MPU6050_Decoder::Decode()
    {
        m_Decoded.acceleration.x = (m_Encoded.acceleration.x / AccelerometerFSRs[m_Parameters.accelerometer_fsr]) * Gravity;
        m_Decoded.acceleration.y = (m_Encoded.acceleration.y / AccelerometerFSRs[m_Parameters.accelerometer_fsr]) * Gravity;
        m_Decoded.acceleration.z = (m_Encoded.acceleration.z / AccelerometerFSRs[m_Parameters.accelerometer_fsr]) * Gravity;

        m_Decoded.angular_velocity.x = (m_Encoded.angular_velocity.x / GyroscopeFSRs[m_Parameters.gyroscope_fsr]);
        m_Decoded.angular_velocity.y = (m_Encoded.angular_velocity.y / GyroscopeFSRs[m_Parameters.gyroscope_fsr]);
        m_Decoded.angular_velocity.z = (m_Encoded.angular_velocity.z / GyroscopeFSRs[m_Parameters.gyroscope_fsr]);

        Decoder::Decode();
    }
}
