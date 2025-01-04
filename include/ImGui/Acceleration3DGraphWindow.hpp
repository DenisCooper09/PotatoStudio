#pragma once

#include "DecodedDynamicsSamplePlotterWindow.hpp"

#include <cmath>

#include "implot.h"
#include "implot3d.h"

namespace ImGui
{
    class Acceleration3DGraphWindow : public DecodedDynamicsSamplePlotterWindow
    {
    public:
        Acceleration3DGraphWindow() : DecodedDynamicsSamplePlotterWindow("Acceleration 3D View")
        {};

    protected:
        void OnRender() override;
    };
}
