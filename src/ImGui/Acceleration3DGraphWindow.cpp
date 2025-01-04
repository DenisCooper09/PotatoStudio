#include "ImGui/Acceleration3DGraphWindow.hpp"

namespace ImGui
{
    void Acceleration3DGraphWindow::OnRender()
    {
        static int range = 10, time = 0;
        ImGui::SliderInt("Range", &range, 1, (int) m_DecodedDynamicsData.size() - time);
        ImGui::SliderInt("Time", &time, 0, (int) (m_DecodedDynamicsData.size() - range));
        static bool m_NeglectGravity = true;
        ImGui::Checkbox("Neglect Gravity", &m_NeglectGravity);

        float x[range], y[range], z[range];
        float vx[range], vy[range], vz[range];
        float dt = 1.0f / 500.0f;

        float vx_prev = 0.0f, vy_prev = 0.0f, vz_prev = 0.0f;

        for (uint32_t i = time; i < time + range && i < m_DecodedDynamicsData.size(); ++i)
        {
            x[i - time] = (float) m_DecodedDynamicsData[i].mpu6050.acceleration.x;
            y[i - time] = (float) m_DecodedDynamicsData[i].mpu6050.acceleration.y;
            z[i - time] = (float) m_DecodedDynamicsData[i].mpu6050.acceleration.z -
                          ((float) PotatoStudio::Decoders::MPU6050::Gravity * (float) ((int) m_NeglectGravity));

            if (i > 0)
            {
                vx[i - time] = vx_prev + 0.5f * (x[i - time] + x[i - time - 1]) * dt;
                vy[i - time] = vy_prev + 0.5f * (y[i - time] + y[i - time - 1]) * dt;
                vz[i - time] = vz_prev + 0.5f * (z[i - time] + z[i - time - 1]) * dt;

                vx_prev = vx[i - time];
                vy_prev = vy[i - time];
                vz_prev = vz[i - time];
            }
            else
            {
                vx[i - time] = vx_prev;
                vy[i - time] = vy_prev;
                vz[i - time] = vz_prev;
            }
        }

        if (ImPlot3D::BeginPlot("Acceleration/Velocity 3D", ImGui::GetWindowSize()))
        {
            ImPlot3D::PlotLine("Acceleration", x, y, z, range);
            ImPlot3D::PlotLine("Velocity", vx, vy, vz, range);
            ImPlot3D::EndPlot();
        }

        if (ImPlot::BeginPlot("Acceleration/Velocity"))
        {
            float    x_period[range];
            for (int i = 0; i < range; ++i)
                x_period[i] = dt * (float) i;

            ImPlot::PlotLine("Acceleration X", x_period, x, range);
            ImPlot::PlotLine("Acceleration Y", x_period, y, range);
            ImPlot::PlotLine("Acceleration Z", x_period, z, range);
            ImPlot::PlotLine("Velocity X", x_period, vx, range);
            ImPlot::PlotLine("Velocity Y", x_period, vy, range);
            ImPlot::PlotLine("Velocity Z", x_period, vz, range);
            ImPlot::EndPlot();
        }
    }
}
