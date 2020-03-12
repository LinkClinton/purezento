#pragma once

#include "../Extensions/CodeRed/graphics_interface.hpp"
#include "../Interface/noncopyable.hpp"
#include "../Render/render.hpp"
#include "../Shared/font.hpp"

#include "runtime_sharing.hpp"

#include <string>
#include <vector>

namespace purezento {

	struct runtime_startup {
		std::string name = "";

		size_t height = 1920;
		size_t width = 1080;

		font font;
		
		runtime_startup() = default;

		runtime_startup(
			const std::string& name,
			const purezento::font& font,
			const size_t width,
			const size_t height) :
			name(name), height(height), width(width), font(font) {}
	};
	
	class runtime : public noncopyable {
	public:
		explicit runtime(const runtime_startup& startup);

		auto sharing() const noexcept -> std::shared_ptr<runtime_sharing> { return m_runtime_sharing; }
		
		void run_loop();
		
		~runtime();
	private:
		friend class runtime_sharing;

		std::shared_ptr<CodeRed::graphics_interface> m_graphics_interface;

		std::vector<std::shared_ptr<CodeRed::GpuFrameBuffer>> m_frame_buffers;
		
		std::shared_ptr<CodeRed::GpuRenderPass> m_render_pass;
		std::shared_ptr<CodeRed::GpuSwapChain> m_swap_chain;

		std::shared_ptr<render> m_render;
		
		void initialize_render();
	private:		
		std::shared_ptr<runtime_sharing> m_runtime_sharing;
		
		runtime_startup m_startup;
		
		void* m_handle = nullptr;
	};
	
}
