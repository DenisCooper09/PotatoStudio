#pragma once

#include "Decoders/ParameterizedDecoder.hpp"

namespace PotatoStudio::Decoders::MPU6050
{

    struct EncodedVector3
    {
        int16_t x, y, z;
    };

    struct DecodedVector3
    {
        double x, y, z;
    };

    struct EncodedSample
    {
        EncodedVector3 acceleration;
        EncodedVector3 angular_velocity;
    };

    struct DecodedSample
    {
        DecodedVector3 acceleration;
        DecodedVector3 angular_velocity;
    };

    enum AccelerometerFSR
    {
        G2  = 0,
        G4  = 1,
        G8  = 2,
        G16 = 3
    };

    enum GyroscopeFSR
    {
        DEG250  = 0,
        DEG500  = 1,
        DEG1000 = 2,
        DEG2000 = 3
    };

    constexpr double Gravity             = 9.80665;
    constexpr double AccelerometerFSRs[] = {16384, 8192, 4096, 2048};
    constexpr double GyroscopeFSRs[]     = {131, 65.5, 32.8, 16.4};

    struct Config
    {
        AccelerometerFSR accelerometer_fsr;
        GyroscopeFSR     gyroscope_fsr;
    };

    class MPU6050_Decoder : public ParameterizedDecoder<EncodedSample, DecodedSample, Config>
    {
    public:
        void Decode() override;
    };
}
