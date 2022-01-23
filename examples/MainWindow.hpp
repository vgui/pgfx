#pragma once

#include <pgfx/Window.hpp>


class MainWindow : public vgui::Window
{
public:

    MainWindow(const char* title, int x, int y, int width, int height) : vgui::Window(title, x, y, width, height)
    {
    }

    virtual void OnCloseWindow()
    {
    }

    virtual void OnDraw()
    {
    }

    virtual void OnSize(int width, int height)
    {
    }

private:

};//class Window


