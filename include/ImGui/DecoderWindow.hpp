#pragma once

#include "Window.hpp"
#include "Decoders/DynamicsDecoder.hpp"
#include "Decoders/CalibrationDecoder.hpp"

namespace ImGui
{
    class DecoderWindow : public Window
    {
    public:
        DecoderWindow() : Window("Decoder Table View")
        {};

    public:
        void OnCalibrationLoad(const std::vector<uint8_t> &raw_calibration_data);
        void OnDataLoad(const std::vector<uint8_t> &raw_data);
        void OnDecode();

        const std::vector<PotatoStudio::Decoders::DecodedDynamicsSample> &Get();

    protected:
        void OnRender() override;

    private:
        PotatoStudio::Decoders::DynamicsDecoder    m_DynamicsDecoder;
        PotatoStudio::Decoders::CalibrationDecoder m_CalibrationDecoder;
    };
}
