#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"
#include "implot3d.h"

#include <format>
#include <string>

namespace PotatoStudio
{

    class Window
    {
    public:
        Window(const char *name, int width, int height);
        ~Window();

    public:
        void Close();
        bool ShouldClose();
        void Update();
        GLFWwindow *GetNativeWindow();

    private:
        static void ErrorCallback(int error_code, const char *description);
        static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);

    private:
        GLFWwindow *m_NativeWindow;

        const char *m_Name;
        int        m_Width;
        int        m_Height;
    };

}
