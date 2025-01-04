#include "ImGui/AngularVelocity3DGraphWindow.hpp"

namespace ImGui
{
    void AngularVelocity3DGraphWindow::OnRender()
    {
        static int range = 10, time = 0;
        ImGui::SliderInt("Range", &range, 1, (int) m_DecodedDynamicsData.size() - time);
        ImGui::SliderInt("Time", &time, 0, (int) (m_DecodedDynamicsData.size() - range));

        float x[range], y[range], z[range];

        for (uint32_t i = time; i < time + range && i < m_DecodedDynamicsData.size(); ++i)
        {
            x[i - time] = (float) m_DecodedDynamicsData[i].mpu6050.angular_velocity.x;
            y[i - time] = (float) m_DecodedDynamicsData[i].mpu6050.angular_velocity.y;
            z[i - time] = (float) m_DecodedDynamicsData[i].mpu6050.angular_velocity.z;
        }

        if (ImPlot3D::BeginPlot("Angular Velocity", ImGui::GetWindowSize()))
        {
            ImPlot3D::PlotLine("Angular Velocity", x, y, z, (int) range);
            ImPlot3D::EndPlot();
        }
    }
}
