#include "Decoders/BME280/BME280_Decoder.hpp"

namespace PotatoStudio::Decoders::BME280
{
    void BME280_Decoder::Decode()
    {
        m_Decoded.temperature = CompensateTemperature(m_Encoded.temperature);
        m_Decoded.pressure    = CompensatePressure(m_Encoded.pressure);
        m_Decoded.humidity    = CompensateHumidity(m_Encoded.humidity);

        Decoder::Decode();
    }

    double BME280_Decoder::CompensateTemperature(int32_t raw_temperature)
    {
        double var1;
        double var2;
        double temperature;
        double temperature_min = -40;
        double temperature_max = 85;

        var1 = (((double) raw_temperature) / 16384.0 - ((double) m_Parameters.dig_T1) / 1024.0);
        var1 = var1 * ((double) m_Parameters.dig_T2);
        var2 = (((double) raw_temperature) / 131072.0 - ((double) m_Parameters.dig_T1) / 8192.0);
        var2 = (var2 * var2) * ((double) m_Parameters.dig_T3);
        t_fine = (int32_t) (var1 + var2);
        temperature = (var1 + var2) / 5120.0;

        if (temperature < temperature_min)
        {
            temperature = temperature_min;
        }
        else if (temperature > temperature_max)
        {
            temperature = temperature_max;
        }

        return temperature;
    }

    double BME280_Decoder::CompensatePressure(int32_t raw_pressure)
    {
        double var1;
        double var2;
        double var3;
        double pressure;
        double pressure_min = 30000.0;
        double pressure_max = 110000.0;

        var1 = ((double) t_fine / 2.0) - 64000.0;
        var2 = var1 * var1 * ((double) m_Parameters.dig_P6) / 32768.0;
        var2 = var2 + var1 * ((double) m_Parameters.dig_P5) * 2.0;
        var2 = (var2 / 4.0) + (((double) m_Parameters.dig_P4) * 65536.0);
        var3 = ((double) m_Parameters.dig_P3) * var1 * var1 / 524288.0;
        var1 = (var3 + ((double) m_Parameters.dig_P2) * var1) / 524288.0;
        var1 = (1.0 + var1 / 32768.0) * ((double) m_Parameters.dig_P1);

        if (var1 > (0.0))
        {
            pressure = 1048576.0 - (double) raw_pressure;
            pressure = (pressure - (var2 / 4096.0)) * 6250.0 / var1;
            var1     = ((double) m_Parameters.dig_P9) * pressure * pressure / 2147483648.0;
            var2     = pressure * ((double) m_Parameters.dig_P8) / 32768.0;
            pressure = pressure + (var1 + var2 + ((double) m_Parameters.dig_P7)) / 16.0;

            if (pressure < pressure_min)
            {
                pressure = pressure_min;
            }
            else if (pressure > pressure_max)
            {
                pressure = pressure_max;
            }
        }
        else
        {
            pressure = pressure_min;
        }

        return pressure;
    }

    double BME280_Decoder::CompensateHumidity(int32_t raw_humidity)
    {
        double humidity;
        double humidity_min = 0.0;
        double humidity_max = 100.0;
        double var1;
        double var2;
        double var3;
        double var4;
        double var5;
        double var6;

        var1     = ((double) t_fine) - 76800.0;
        var2     = (((double) m_Parameters.dig_H4) * 64.0 + (((double) m_Parameters.dig_H5) / 16384.0) * var1);
        var3     = ((double) raw_humidity) - var2;
        var4     = ((double) m_Parameters.dig_H2) / 65536.0;
        var5     = (1.0 + (((double) m_Parameters.dig_H3) / 67108864.0) * var1);
        var6     = 1.0 + (((double) m_Parameters.dig_H6) / 67108864.0) * var1 * var5;
        var6     = var3 * var4 * (var5 * var6);
        humidity = var6 * (1.0 - ((double) m_Parameters.dig_H1) * var6 / 524288.0);

        if (humidity > humidity_max)
        {
            humidity = humidity_max;
        }
        else if (humidity < humidity_min)
        {
            humidity = humidity_min;
        }

        return humidity;
    }
}
