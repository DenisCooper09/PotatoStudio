#pragma once

#include "Window.hpp"

#include <vector>
#include <memory>

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
    };

}
