#pragma once

#include "DecodedDynamicsSamplePlotterWindow.hpp"

#include "implot3d.h"

namespace ImGui
{
    class AngularVelocity3DGraphWindow : public DecodedDynamicsSamplePlotterWindow
    {
    public:
        AngularVelocity3DGraphWindow() : DecodedDynamicsSamplePlotterWindow("Angular Velocity 3D View")
        {};

    protected:
        void OnRender() override;
    };
}
