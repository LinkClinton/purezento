#pragma once

#include "../Runtime/runtime_sharing.hpp"
#include "../Interface/noncopyable.hpp"
#include "../Shared/font.hpp"

#include <memory>

namespace purezento {

	class render : public noncopyable {
	public:
		explicit render(
			const std::shared_ptr<runtime_sharing>& runtime_sharing,
			const std::shared_ptr<CodeRed::GpuRenderPass>& render_pass,
			const size_t width, const size_t height,
			const purezento::font& font);

		~render() = default;
	private:
		std::shared_ptr<runtime_sharing> m_runtime_sharing;

		std::shared_ptr<CodeRed::graphics_interface> m_graphics_interface;
		std::shared_ptr<CodeRed::GpuGraphicsCommandList> m_command_list;
		std::shared_ptr<CodeRed::GpuRenderPass> m_render_pass;

		std::shared_ptr<CodeRed::ImGuiWindows> m_imgui_windows;

		size_t m_width = 0, m_height = 0;

		font m_font;
	};
	
}
