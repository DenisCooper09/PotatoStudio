#include <cstdio>
#include "Decoders/CalibrationDecoder.hpp"

namespace PotatoStudio::Decoders
{
    void CalibrationDecoder::Decode()
    {
        for (uint8_t i = 0; i < 33; ++i)
        {
            m_Decoded.data[i] = m_Encoded[i];
        }

        printf("dig_T1: 0x%X\n", m_Decoded.dig_T1);
        printf("dig_T2: 0x%X\n", m_Decoded.dig_T2);
        printf("dig_T3: 0x%X\n", m_Decoded.dig_T3);

        printf("dig_P1: 0x%X\n", m_Decoded.dig_P1);
        printf("dig_P2: 0x%X\n", m_Decoded.dig_P2);
        printf("dig_P3: 0x%X\n", m_Decoded.dig_P3);
        printf("dig_P4: 0x%X\n", m_Decoded.dig_P4);
        printf("dig_P5: 0x%X\n", m_Decoded.dig_P5);
        printf("dig_P6: 0x%X\n", m_Decoded.dig_P6);
        printf("dig_P7: 0x%X\n", m_Decoded.dig_P7);
        printf("dig_P8: 0x%X\n", m_Decoded.dig_P8);
        printf("dig_P9: 0x%X\n", m_Decoded.dig_P9);

        printf("dig_H1: 0x%X\n", m_Decoded.dig_H1);
        printf("dig_H2: 0x%X\n", m_Decoded.dig_H2);
        printf("dig_H3: 0x%X\n", m_Decoded.dig_H3);
        printf("dig_H4: 0x%X\n", m_Decoded.dig_H4);
        printf("dig_H5: 0x%X\n", m_Decoded.dig_H5);
        printf("dig_H6: 0x%X\n", m_Decoded.dig_H6);

        Decoder::Decode();
    }
}
