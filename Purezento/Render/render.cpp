#include "render.hpp"

#include "../Extensions/ImGui/imgui.hpp"

#include <Extensions/ImGui/ImGuiWindows.hpp>
#include <CodeRed/Core/CodeRedGraphics.hpp>

purezento::render::render(
	const std::shared_ptr<runtime_sharing>& runtime_sharing,
	const std::shared_ptr<CodeRed::GpuRenderPass>& render_pass, 
	const size_t width, const size_t height, const purezento::font& font) :
	m_runtime_sharing(runtime_sharing), m_graphics_interface(runtime_sharing->graphics_interface()),
	m_render_pass(render_pass), m_width(width), m_height(height), m_font(font)
{
	ImGui::StyleColorsLight();

	ImGui::GetIO().Fonts->AddFontFromFileTTF(m_font.name.c_str(), static_cast<float>(m_font.size));

	m_command_list = m_graphics_interface->device()->createGraphicsCommandList(
		m_graphics_interface->allocator()
	);
	
	m_imgui_windows = std::make_shared<CodeRed::ImGuiWindows>(
		m_graphics_interface->device(),
		m_render_pass,
		m_graphics_interface->allocator(),
		m_graphics_interface->queue());
}
