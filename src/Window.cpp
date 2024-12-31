#include "Window.hpp"

namespace PotatoStudio
{

    Window::Window(const char *name, int width, int height)
            : m_Name(name), m_Width(width), m_Height(height)
    {
        m_NativeWindow = glfwCreateWindow(m_Width, m_Height, m_Name, nullptr, nullptr);
        if (!m_NativeWindow)
        {
            throw std::runtime_error("Failed to create GLFW window.");
        }

        glfwSetFramebufferSizeCallback(m_NativeWindow, FramebufferSizeCallback);

        glfwMakeContextCurrent(m_NativeWindow);

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        {
            throw std::runtime_error("GLAD failed to load OpenGL loader.");
        }
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_NativeWindow);
        glfwTerminate();
    }


    void Window::Close()
    {
        glfwSetWindowShouldClose(m_NativeWindow, true);
    }

    bool Window::ShouldClose()
    {
        return glfwWindowShouldClose(m_NativeWindow);
    }

    void Window::Update()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_NativeWindow);
    }

    GLFWwindow *Window::GetNativeWindow()
    {
        return m_NativeWindow;
    }


    void Window::ErrorCallback(int error_code, const char *description)
    {
        throw std::runtime_error(std::format("GLFW error: {}, {}", error_code, description));
    }

    void Window::FramebufferSizeCallback(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

}