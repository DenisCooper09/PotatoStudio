#include "ImGui/DecoderWindow.hpp"

namespace ImGui
{
    void DecoderWindow::OnCalibrationLoad(const std::vector<uint8_t> &raw_calibration_data)
    {
        m_CalibrationDecoder.Set(raw_calibration_data);
        m_CalibrationDecoder.Decode();
        m_DynamicsDecoder.SetParameters(m_CalibrationDecoder.Get());
    }

    void DecoderWindow::OnDataLoad(const std::vector<uint8_t> &raw_data)
    {
        m_DynamicsDecoder.Set(raw_data);
    }

    void DecoderWindow::OnDecode()
    {
        m_DynamicsDecoder.Decode();
    }

    void DecoderWindow::OnRender()
    {
        ImGui::BeginTable("DecodedDataTable", 9, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg);

        ImGui::TableSetupColumn("Acceleration X");
        ImGui::TableSetupColumn("Acceleration Y");
        ImGui::TableSetupColumn("Acceleration Z");
        ImGui::TableSetupColumn("Angular Velocity X");
        ImGui::TableSetupColumn("Angular Velocity Y");
        ImGui::TableSetupColumn("Angular Velocity Z");
        ImGui::TableSetupColumn("Temperature");
        ImGui::TableSetupColumn("Pressure");
        ImGui::TableSetupColumn("Humidity");

        ImGui::TableHeadersRow();

        for (const auto &sample: m_DynamicsDecoder.Get())
        {
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("%f", sample.mpu6050.acceleration.x);
            ImGui::TableNextColumn();
            ImGui::Text("%f", sample.mpu6050.acceleration.y);
            ImGui::TableNextColumn();
            ImGui::Text("%f", sample.mpu6050.acceleration.z);

            ImGui::TableNextColumn();
            ImGui::Text("%f", sample.mpu6050.angular_velocity.x);
            ImGui::TableNextColumn();
            ImGui::Text("%f", sample.mpu6050.angular_velocity.y);
            ImGui::TableNextColumn();
            ImGui::Text("%f", sample.mpu6050.angular_velocity.z);

            ImGui::TableNextColumn();
            ImGui::Text("%f", sample.bme280.temperature);
            ImGui::TableNextColumn();
            ImGui::Text("%f", sample.bme280.pressure);
            ImGui::TableNextColumn();
            ImGui::Text("%f", sample.bme280.humidity);
        }

        ImGui::EndTable();
    }

    const std::vector<PotatoStudio::Decoders::DecodedDynamicsSample> &DecoderWindow::Get()
    {
        return m_DynamicsDecoder.Get();
    }
}
