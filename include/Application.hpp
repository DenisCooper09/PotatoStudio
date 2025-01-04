#pragma once

#include "Window.hpp"
#include "ImGui/Window.hpp"
#include "ImGui/DecoderWindow.hpp"
#include "ImGui/Acceleration3DGraphWindow.hpp"
#include "ImGui/AngularVelocity3DGraphWindow.hpp"
#include "ImGui/PressureAltitudeGraphWindow.hpp"

#include "Decoders/DynamicsDecoder.hpp"
#include "Decoders/CalibrationDecoder.hpp"

#include "IconsFontAwesome6.h"
#include "fa-solid-900.h"
#include "ImGuiNotify.hpp"
#include "imgui_internal.h"
#include "imgui_memory_editor.h"
#include "imfilebrowser.h"

#include <iostream>
#include <fstream>
#include <format>
#include <vector>
#include <memory>
#include <tchar.h>

namespace PotatoStudio
{

    class Application
    {
    public:
        Application();

    public:
        void Run();

    private:
        std::unique_ptr<Window> m_Window;

        MemoryEditor m_MemoryEditor;

        ImGui::FileBrowser m_FileDialog = ImGui::FileBrowser(ImGuiFileBrowserFlags_SelectDirectory | ImGuiFileBrowserFlags_EditPathString);
    };

}
