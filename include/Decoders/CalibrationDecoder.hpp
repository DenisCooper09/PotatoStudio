#pragma once

#include "Decoder.hpp"

namespace PotatoStudio::Decoders
{
    union CalibrationData
    {
        struct
        {
            uint16_t dig_T1;
            int16_t  dig_T2;
            int16_t  dig_T3;

            uint16_t dig_P1;
            int16_t  dig_P2;
            int16_t  dig_P3;
            int16_t  dig_P4;
            int16_t  dig_P5;
            int16_t  dig_P6;
            int16_t  dig_P7;
            int16_t  dig_P8;
            int16_t  dig_P9;

            uint8_t dig_H1;
            int16_t dig_H2;
            uint8_t dig_H3;
            int16_t dig_H4;
            int16_t dig_H5;
            int8_t  dig_H6;

            int32_t t_fine;
        };

        uint8_t data[33];
    };

    class CalibrationDecoder : public Decoder<std::vector<uint8_t>, CalibrationData>
    {
    public:
        void Decode() override;
    };
}
