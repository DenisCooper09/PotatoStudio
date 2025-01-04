#pragma once

#include "DecodedDynamicsSamplePlotterWindow.hpp"

#include <cmath>

#include "implot.h"

namespace ImGui
{
    class PressureAltitudeGraphWindow : public DecodedDynamicsSamplePlotterWindow
    {
    public:
        PressureAltitudeGraphWindow() : DecodedDynamicsSamplePlotterWindow("Pressure/Altitude Temperature View")
        {};

    protected:
        void OnRender() override;
    };
}
