#include "ImGui/Window.hpp"

namespace ImGui
{

    Window::Window(const char *name, bool open)
            : m_Name(name), m_Open(open)
    {
    }
    
    void Window::Render()
    {
        if (m_Open)
        {
            if (ImGui::Begin(m_Name, &m_Open))
            {
                OnRender();
            }
            ImGui::End();
        }
    }

    void Window::RenderMenuItem()
    {
        ImGui::MenuItem(m_Name, nullptr, &m_Open);
    }

}
