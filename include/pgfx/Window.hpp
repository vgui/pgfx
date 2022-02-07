#pragma once

#include "Canvas.hpp"
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

    vgui::Canvas& Graphics()
    {
        return m_gfx;
    }

    virtual void OnCloseWindow()
    {
        m_gfx.Destroy();
    }

    virtual void OnDraw()
    {
        m_gfx.BeginFrame();

        ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
        ImVec2 p = {0.0, 0.0};//ImGui::GetCursorScreenPos();

        ImGuiViewport* view = ImGui::GetMainViewport();

        std::srand(std::time(nullptr));
        auto random = [](int max)
        {
          return std::rand()%max + 1;
        };

        for(size_t i = 0; i < 1500;i++)
        {
            float x = random(view->WorkSize.x+1);
            float y = random(view->WorkSize.y+1);
            ImVec2 pos = {x, y};
            ImVec2 size = {pos.x+200, pos.y+200};
            draw_list->AddRectFilled(pos, size,
                                     IM_COL32(random(255), random(255), random(255), random(255)), 10.0, ImDrawFlags_RoundCornersAll);

        }

        draw_list->AddCircleFilled(ImVec2(p.x + 200, p.y + 200), 100.0f, IM_COL32(255, 0, 0, 127), 64);
        draw_list->AddRectFilled({0.0, 0.0}, {100.0, 100.0}, IM_COL32(0, 255, 0, 255), 10.0, ImDrawFlags_RoundCornersAll);
        draw_list->AddLine(ImVec2(p.x, p.y), ImVec2(p.x + 100.0f, p.y + 100.0f), IM_COL32(255, 255, 0, 127), 0.5f);

        m_gfx.EndFrame();
    }

    virtual void OnSize(int width, int height)
    {
        m_gfx.Reset(width, height);
    }

private:

    vgui::Canvas m_gfx;
};//class Window


}//namespace vgui

