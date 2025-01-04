#pragma once

#include "Window.hpp"
#include "Decoders/DynamicsDecoder.hpp"

namespace ImGui
{
    class DecodedDynamicsSamplePlotterWindow : public Window
    {
    public:
        explicit DecodedDynamicsSamplePlotterWindow(const char *name, bool open = false) : Window(name, open)
        {}

    public:
        void Set(const std::vector<PotatoStudio::Decoders::DecodedDynamicsSample> &data)
        {
            m_DecodedDynamicsData = data;
            m_Updated             = true;
        }

    protected:
        std::vector<PotatoStudio::Decoders::DecodedDynamicsSample> m_DecodedDynamicsData;
        bool                                                       m_Updated = false;
    };
}
