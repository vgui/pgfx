#pragma once

#include "Graphics.hpp"
#include "Win32Window.hpp"


namespace vgui
{

class Window : public Win32Window<Window>
{
public:

    using Handle_t = HWND;

    Window(const char* title, int x, int y, int width, int height) : Win32Window<Window>(title, x, y, width, height), m_gfx(Handle())
    {}

    virtual ~Window()
    {}

    vgui::Graphics& Graphics()
    {
        return m_gfx;
    }

private:

    vgui::Graphics m_gfx;
};//class Window


}//namespace vgui

