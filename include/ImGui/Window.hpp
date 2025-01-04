#pragma once

#include "imgui.h"

#define DEF_WIN(label, name)\
namespace ImGui\
{\
class name : public Window\
{\
public:\
    name() : Window((label))\
    {};\
protected:\
    void OnRender() override;\
private: \

#define END_WIN() };}

#define IMPL_WIN(name) namespace ImGui{void name::OnRender(){

namespace ImGui
{

    class Window
    {
    public:
        explicit Window(const char *name, bool open = false);
        virtual ~Window() = default;

    public:
        void Render();
        void RenderMenuItem();

    protected:
        virtual void OnRender() = 0;

    private:
        const char *m_Name;
        bool       m_Open;
    };

}
