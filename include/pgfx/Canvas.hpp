#pragma once

#include "pgfx/pgfx.hpp"


namespace vgui
{

class Canvas
{
public:

    Canvas(HWND handle)
    {
        Create(handle);
    }

    virtual ~Canvas()
    {
        Destroy();
    }

    void Create(HWND handle)
    {
        if((m_d3d = Direct3DCreate9(D3D_SDK_VERSION)) == nullptr)
            throw ExceptionInfo << "Can't create Direct3D9.";

        ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));
        m_d3dpp.Windowed = TRUE;
        m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
        m_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
        m_d3dpp.EnableAutoDepthStencil = TRUE;
        m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
        m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
        //m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
        if(m_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, handle, D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_d3dpp, &m_d3ddevice) < 0)
            throw ExceptionInfo << "Can't create Direct3D9 device.";

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        ImGui::StyleColorsLight();

        ImGui_ImplWin32_Init(handle);
        ImGui_ImplDX9_Init(m_d3ddevice);
    }

    void Destroy()
    {
        ImGui_ImplDX9_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        if(m_d3ddevice) { m_d3ddevice->Release(); m_d3ddevice = nullptr; }
        if(m_d3d) { m_d3d->Release(); m_d3d = nullptr; }
    }

    void Reset(int width = -1, int height = -1)
    {
        if(m_d3ddevice)
        {
            ImGui_ImplDX9_InvalidateDeviceObjects();

            if(width != -1 && height != -1)
            {
                m_d3dpp.BackBufferWidth = width;
                m_d3dpp.BackBufferHeight = height;
            }

            HRESULT hr = m_d3ddevice->Reset(&m_d3dpp);
            if (hr == D3DERR_INVALIDCALL)
                throw ExceptionInfo << "Can't reset Direct3D9 device.";

            ImGui_ImplDX9_CreateDeviceObjects();
        }
    }

    void BeginFrame()
    {
        ImGui_ImplWin32_NewFrame();
        ImGui_ImplDX9_NewFrame();
        ImGui::NewFrame();
        m_drawlist = ImGui::GetBackgroundDrawList();
    }

    void EndFrame()
    {
        ImGui::EndFrame();

        if (m_d3ddevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            m_d3ddevice->EndScene();
        }

        HRESULT result = m_d3ddevice->Present(nullptr, nullptr, nullptr, nullptr);

        // Handle loss of D3D9 device
        if (result == D3DERR_DEVICELOST && m_d3ddevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            Reset();
    }

    void Clear(float R, float G, float B, float A)
    {
        ImVec4 clear_color = ImVec4(R, G, B, A);
        m_d3ddevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        m_d3ddevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        m_d3ddevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x*clear_color.w*255.0f), (int)(clear_color.y*clear_color.w*255.0f), (int)(clear_color.z*clear_color.w*255.0f), (int)(clear_color.w*255.0f));
        m_d3ddevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
    }

    auto ViewportPosition()
    {
        ImGuiViewport* view = ImGui::GetMainViewport();
        return std::make_tuple(view->WorkPos.x, view->WorkPos.y);
    }

    auto ViewportSize()
    {
        ImGuiViewport* view = ImGui::GetMainViewport();
        return std::make_tuple(view->WorkSize.x, view->WorkSize.y);
    }

private:

    LPDIRECT3D9              m_d3d = nullptr;
    LPDIRECT3DDEVICE9        m_d3ddevice = nullptr;
    D3DPRESENT_PARAMETERS    m_d3dpp = {0};
    ImDrawList* m_drawlist{nullptr};

};//class Graphics


}//namespace pgfx

