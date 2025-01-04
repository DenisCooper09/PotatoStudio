#include "ImGui/PressureAltitudeGraphWindow.hpp"

namespace ImGui
{
    static double PressureToAltitude(double pressure, double Pb = 101325.0, double Tb = 288.15, double Lb = -0.0065, double hb = 0.0)
    {
        const double R  = 8.31432; // Universal gas constant [N·m/(mol·K)]
        const double g0 = 9.80665; // Gravitational acceleration [m/s^2]
        const double M  = 0.0289644; // Molar mass of Earth's air [kg/mol]

        if (Lb != 0.0)
        {
            return hb + Tb / Lb * (std::pow(pressure / Pb, -R * Lb / (g0 * M)) - 1.0);
        }
        else
        {
            return hb + R * Tb / (g0 * M) * std::log(Pb / pressure);
        }
    }

    void PressureAltitudeGraphWindow::OnRender()
    {
        static int range = 10, time = 0;
        ImGui::SliderInt("Range", &range, 1, (int) m_DecodedDynamicsData.size() - time);
        ImGui::SliderInt("Time", &time, 0, (int) (m_DecodedDynamicsData.size() - range));

        float press[range];
        float altitude[range];
        float temp[range];
        float dt = 1.0f / 500.0f;

        for (uint32_t i = time; i < time + range && i < m_DecodedDynamicsData.size(); ++i)
        {
            press[i - time]    = (float) m_DecodedDynamicsData[i].bme280.pressure;
            altitude[i - time] = (float) PressureToAltitude((double) press[i - time]);
            temp[i - time]     = (float) m_DecodedDynamicsData[i].bme280.temperature;
        }

        float    x_period[range];
        for (int i = 0; i < range; ++i)
            x_period[i] = dt * (float) i;

        if (ImPlot::BeginPlot("Pressure/Altitude"))
        {
            ImPlot::PlotLine("Pressure (Pa)", x_period, press, range);
            ImPlot::PlotLine("Altitude (m)", x_period, altitude, range);
            ImPlot::EndPlot();
        }

        if (ImPlot::BeginPlot("Temperature"))
        {
            ImPlot::PlotLine("Temperature (Celsius)", x_period, temp, range);
            ImPlot::EndPlot();
        }
    }
}
