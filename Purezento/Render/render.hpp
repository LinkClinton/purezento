#pragma once

#include "../Runtime/runtime_sharing.hpp"
#include "../Interface/noncopyable.hpp"
#include "../Shared/font.hpp"

#include "render_callback.hpp"
#include "draw_element.hpp"

#include <memory>
#include <map>

namespace purezento {

	class render final : public noncopyable, public std::enable_shared_from_this<render> {
	public:
		explicit render(
			const std::shared_ptr<runtime_sharing>& runtime_sharing,
			const std::shared_ptr<CodeRed::GpuRenderPass>& render_pass,
			const size_t width, const size_t height,
			const purezento::font& font);

		~render() = default;

		void update(float delta);
		
		auto execute(const std::shared_ptr<CodeRed::GpuFrameBuffer>& frame_buffer, float delta) const
			-> std::shared_ptr<CodeRed::GpuGraphicsCommandList>;
	public:
		std::map<std::string, std::vector<draw_element>> draw_elements;

		std::map<std::string, render_callback> callbacks;
	private:
		std::shared_ptr<runtime_sharing> m_runtime_sharing;

		std::shared_ptr<CodeRed::graphics_interface> m_graphics_interface;
		std::shared_ptr<CodeRed::GpuGraphicsCommandList> m_command_list;
		std::shared_ptr<CodeRed::GpuRenderPass> m_render_pass;

		std::shared_ptr<CodeRed::ImGuiContext> m_imgui_context;

		size_t m_width = 0, m_height = 0;

		font m_font;
	};
	
}
