#include "Application.hpp"

#define TOAST_NOTIFICATION_DELAY 6000

namespace PotatoStudio
{
    static std::vector<uint8_t> ReadBin(const std::string &path)
    {
        std::ifstream file(path, std::ios::binary | std::ios::ate);
        if (!file)
        {
            throw std::ios_base::failure("Failed to open file: " + path);
        }

        std::streamsize size = file.tellg();
        if (size < 0)
        {
            throw std::ios_base::failure("Failed to determine file size: " + path);
        }

        std::vector<uint8_t> buffer(static_cast<size_t>(size));

        file.seekg(0, std::ios::beg);
        if (!file.read(reinterpret_cast<char *>(buffer.data()), size))
        {
            throw std::ios_base::failure("Failed to read file: " + path);
        }

        return buffer;
    }

    static ImGui::DecoderWindow                m_Decoder                = ImGui::DecoderWindow();
    static ImGui::Acceleration3DGraphWindow    m_AccelerationWindow     = ImGui::Acceleration3DGraphWindow();
    static ImGui::AngularVelocity3DGraphWindow m_AngularVelocityWindow  = ImGui::AngularVelocity3DGraphWindow();
    static ImGui::PressureAltitudeGraphWindow  m_PressureAltitudeWindow = ImGui::PressureAltitudeGraphWindow();

    static std::string          s_DirectoryPath     = "D:/PotatoDynamicsData";
    static std::vector<uint8_t> s_CalibrationData;
    static std::vector<uint8_t> s_DynamicsData;
    static uint8_t              s_DynamicsFileIndex = 0;
    static bool                 Decoded             = false;

    static void Decode()
    {
        m_Decoder.OnDecode();
        m_AccelerationWindow.Set(m_Decoder.Get());
        m_AngularVelocityWindow.Set(m_Decoder.Get());
        m_PressureAltitudeWindow.Set(m_Decoder.Get());
        Decoded = true;
    }

    static void ReadDynamicsDataFile()
    {
        try
        {
            s_DynamicsData = ReadBin(s_DirectoryPath + std::format("/DYN{}.bin", s_DynamicsFileIndex));
            m_Decoder.OnDataLoad(s_DynamicsData);
            ImGui::InsertNotification(
                    {
                            ImGuiToastType::Success,
                            TOAST_NOTIFICATION_DELAY,
                            "Dynamics data read successfully!\nSize: %i bytes.\nFile: %s",
                            s_DynamicsData.size(),
                            (s_DirectoryPath + std::format("/DYN{}.bin", s_DynamicsFileIndex)).c_str()
                    });
            Decode();
        }
        catch (const std::exception &e)
        {
            ImGui::InsertNotification(
                    {
                            ImGuiToastType::Error,
                            TOAST_NOTIFICATION_DELAY,
                            e.what()
                    });
        }
    }

    static void ReadCalibrationDataFile()
    {
        try
        {
            s_CalibrationData = ReadBin(s_DirectoryPath + "/CALIB.bin");
            m_Decoder.OnCalibrationLoad(s_CalibrationData);
            ImGui::InsertNotification(
                    {
                            ImGuiToastType::Success,
                            TOAST_NOTIFICATION_DELAY,
                            "Calibration data read successfully!\nSize: %i bytes.\nFile: %s",
                            s_CalibrationData.size(),
                            (s_DirectoryPath + "/CALIB.bin").c_str()
                    });
        }
        catch (const std::exception &e)
        {
            ImGui::InsertNotification(
                    {
                            ImGuiToastType::Error,
                            TOAST_NOTIFICATION_DELAY,
                            e.what()
                    });
        }
    }

    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    Application::Application()
    {
        if (!glfwInit())
        {
            throw std::runtime_error("Failed to initialize GLFW.");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Window = std::make_unique<Window>("Potato Studio", 1720, 880);
        m_Window->SetKeyCallback(KeyCallback);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImPlot::CreateContext();
        ImPlot3D::CreateContext();

        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(m_Window->GetNativeWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 460 core");

        m_FileDialog.SetTitle("Select Data Folder");

        io.Fonts->AddFontDefault();
        float baseFontSize = 16.0f;
        float iconFontSize = baseFontSize * 2.0f / 3.0f;

        static constexpr ImWchar iconsRanges[] = {ICON_MIN_FA, ICON_MAX_16_FA, 0};
        ImFontConfig             iconsConfig;

        iconsConfig.MergeMode        = true;
        iconsConfig.PixelSnapH       = true;
        iconsConfig.GlyphMinAdvanceX = iconFontSize;

        io.Fonts->AddFontFromMemoryCompressedTTF(
                fa_solid_900_compressed_data,
                fa_solid_900_compressed_size,
                iconFontSize, &iconsConfig, iconsRanges
        );

        ReadCalibrationDataFile();
        ReadDynamicsDataFile();
    }

    void Application::Run()
    {
        ImVec4 clear_color = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);

        while (!m_Window->ShouldClose())
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

            ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), ImGuiCond_Once);
            ImGui::SetNextWindowSize({550, 550}, ImGuiCond_Once);

            if (ImGui::BeginMainMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    if (ImGui::MenuItem("Select Directory"))
                    {
                        m_FileDialog.Open();
                    }

                    if (ImGui::MenuItem("Exit"))
                    {
                        m_Window->Close();
                    }
                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Decoder (Table View)", Decoded))
                {
                    m_Decoder.RenderMenuItem();
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("MPU6050", Decoded))
                {
                    m_AccelerationWindow.RenderMenuItem();
                    m_AngularVelocityWindow.RenderMenuItem();
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("BME280", Decoded))
                {
                    m_PressureAltitudeWindow.RenderMenuItem();
                    ImGui::EndMenu();
                }

                ImGui::Text("Directory: %s | DYN%i.bin", s_DirectoryPath.c_str(), s_DynamicsFileIndex);

                ImGui::EndMainMenuBar();
            }

            m_Decoder.Render();
            m_AccelerationWindow.Render();
            m_AngularVelocityWindow.Render();
            m_PressureAltitudeWindow.Render();

            m_FileDialog.Display();

            if (m_FileDialog.HasSelected())
            {
                m_FileDialog.ClearSelected();
                s_DirectoryPath = m_FileDialog.GetSelected().string();

                ReadCalibrationDataFile();
            }

            m_MemoryEditor.DrawWindow("Calibration Data View", static_cast<void *>(s_CalibrationData.data()), s_CalibrationData.size());
            m_MemoryEditor.DrawWindow("Dynamics Data View", static_cast<void *>(s_DynamicsData.data()), s_DynamicsData.size());

            ImGui::RenderNotifications();

            ImGui::Render();

            glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);

            m_Window->Update();
        }

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImPlot3D::DestroyContext();
        ImPlot::DestroyContext();
        ImGui::DestroyContext();
    }

    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            switch (key)
            {
                case GLFW_KEY_RIGHT_BRACKET:
                {
                    s_DynamicsFileIndex++;
                    ReadDynamicsDataFile();
                    break;
                }
                case GLFW_KEY_LEFT_BRACKET:
                {
                    s_DynamicsFileIndex--;
                    ReadDynamicsDataFile();
                    break;
                }
                default:break;
            }
        }
    }
}
