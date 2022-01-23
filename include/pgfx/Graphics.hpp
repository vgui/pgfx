#pragma once

#include "pgfx/pgfx.hpp"


namespace vgui
{

class Graphics
{
public:

    Graphics(HWND handle)
    {
        CreateDeviceD3D(handle);
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        ImGui::StyleColorsLight();

        ImGui_ImplWin32_Init(handle);
        ImGui_ImplDX9_Init(m_d3ddevice);
    }

    virtual ~Graphics()
    {
        ImGui_ImplDX9_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
        CleanupDeviceD3D();
    }

private:

    void CreateDeviceD3D(HWND hWnd)
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
        if (m_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_d3dpp, &m_d3ddevice) < 0)
            throw ExceptionInfo << "Can't create Direct3D9 device.";
    }

    void CleanupDeviceD3D()
    {
        if(m_d3ddevice) { m_d3ddevice->Release(); m_d3ddevice = nullptr; }
        if(m_d3d) { m_d3d->Release(); m_d3d = nullptr; }
    }

    void ResetDeviceD3D()
    {
        ImGui_ImplDX9_InvalidateDeviceObjects();
        HRESULT hr = m_d3ddevice->Reset(&m_d3dpp);
        if (hr == D3DERR_INVALIDCALL)
            throw ExceptionInfo << "Can't rese Direct3D9 device.t";

        ImGui_ImplDX9_CreateDeviceObjects();
    }

    LPDIRECT3D9              m_d3d = nullptr;
    LPDIRECT3DDEVICE9        m_d3ddevice = nullptr;
    D3DPRESENT_PARAMETERS    m_d3dpp = {0};

};//class Graphics


}//namespace pgfx

