#include "runtime.hpp"

#include "../Extensions/ImGui/imgui_impl_win32.hpp"

#include <CodeRed/Core/CodeRedGraphics.hpp>

#include <Windows.h>
#include <chrono>

using Time = std::chrono::high_resolution_clock;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT DefaultWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;

	switch (message)
	{
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	default:
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

purezento::runtime::runtime(const runtime_startup& startup) :
	m_startup(startup)
{
	const auto hInstance = GetModuleHandle(nullptr);
	const auto class_name = m_startup.name;

	// initialize runtime sharing
	m_runtime_sharing = std::make_shared<runtime_sharing>(this);

	WNDCLASS appInfo;

	appInfo.style = CS_DBLCLKS;
	appInfo.lpfnWndProc = DefaultWindowProc;
	appInfo.cbClsExtra = 0;
	appInfo.cbWndExtra = 0;
	appInfo.hInstance = hInstance;
	appInfo.hIcon = static_cast<HICON>(LoadImage(nullptr, "", IMAGE_ICON, 0, 0, LR_LOADFROMFILE));
	appInfo.hCursor = LoadCursor(nullptr, IDC_ARROW);
	appInfo.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	appInfo.lpszMenuName = nullptr;
	appInfo.lpszClassName = &class_name[0];
	
	RegisterClass(&appInfo);

	RECT rect;

	rect.top = 0;
	rect.left = 0;
	rect.right = static_cast<UINT>(m_startup.width);
	rect.bottom = static_cast<UINT>(m_startup.height);

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	m_handle = CreateWindow(&class_name[0], &class_name[0], WS_OVERLAPPEDWINDOW ^
		WS_SIZEBOX ^ WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, nullptr);

	ShowWindow(static_cast<HWND>(m_handle), SW_SHOW);
	
	ImGui::CreateContext();
	ImGui_ImplWin32_Init(m_handle);
	
	initialize_render();
	initialize_console();
}

purezento::runtime::~runtime()
{
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	m_graphics_interface->queue()->waitIdle();
}

void purezento::runtime::update(float delta)
{
	ImGui::NewFrame();

	m_console->update(delta);
	m_render->update(delta);

	ImGui::Render();
}

void purezento::runtime::render(float delta)
{
	m_graphics_interface->queue()->waitIdle();
	m_graphics_interface->allocator()->reset();

	m_graphics_interface->queue()->execute(
		{ m_render->execute(m_frame_buffers[m_current_frame_index], delta) });
	
	m_swap_chain->present();

	m_current_frame_index = (m_current_frame_index + 1) % m_swap_chain->bufferCount();
}

void purezento::runtime::initialize_render()
{
	// initialize graphics interface
	m_graphics_interface = std::make_shared<CodeRed::graphics_interface>();

	m_swap_chain = m_graphics_interface->device()->createSwapChain(
		m_graphics_interface->queue(),
		{
		m_startup.width,
		m_startup.height,
		m_handle
		},
		CodeRed::PixelFormat::BlueGreenRedAlpha8BitUnknown,
		2
	);

	for (size_t index = 0; index < m_swap_chain->bufferCount(); index++) {
		m_frame_buffers.push_back(
			m_graphics_interface->device()->createFrameBuffer(
				{ m_swap_chain->buffer(index)->reference() }
			)
		);
	}

	m_render_pass = m_graphics_interface->device()->createRenderPass(
		{ CodeRed::Attachment::RenderTarget(m_swap_chain->format()) }
	);

	m_render = std::make_shared<purezento::render>(
		m_runtime_sharing,
		m_render_pass,
		m_startup.width, m_startup.height, m_startup.font);
}

void purezento::runtime::initialize_console()
{
	m_console = std::make_shared<purezento::console>(m_runtime_sharing);
}

void purezento::runtime::run_loop()
{
	auto currentTime = Time::now();
	
	while (m_handle != nullptr) {
		MSG message;

		message.hwnd = static_cast<HWND>(m_handle);

		while (PeekMessage(&message, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);

			if (message.message == WM_QUIT) m_handle = nullptr;
		}

		if (m_handle == nullptr) break;

		auto duration = std::chrono::duration_cast<
			std::chrono::duration<float>>(Time::now() - currentTime);

		currentTime = Time::now();

		ImGui_ImplWin32_NewFrame();

		update(duration.count());
		render(duration.count());
	}
}
