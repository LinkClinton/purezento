#pragma once

#include "../Extensions/CodeRed/graphics_interface.hpp"
#include "../Interface/noncopyable.hpp"
#include "../Console/console.hpp"
#include "../Render/render.hpp"
#include "../Config/config.hpp"
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

		auto console() const noexcept -> std::shared_ptr<console> { return m_console; }

		auto render() const noexcept -> std::shared_ptr<render> { return m_render; }

		auto config() const noexcept -> std::shared_ptr<config> { return m_config; }
		
		void run_loop();
		
		~runtime();
	private:
		void update(float delta);

		void render(float delta);
	private:
		friend class runtime_sharing;

		std::shared_ptr<purezento::config> m_config;

		void initialize_config();
	private:
		std::shared_ptr<CodeRed::graphics_interface> m_graphics_interface;

		std::vector<std::shared_ptr<CodeRed::GpuFrameBuffer>> m_frame_buffers;
		
		std::shared_ptr<CodeRed::GpuRenderPass> m_render_pass;
		std::shared_ptr<CodeRed::GpuSwapChain> m_swap_chain;

		std::shared_ptr<purezento::render> m_render;

		size_t m_current_frame_index = 0;
		
		void initialize_render();
	private:
		std::shared_ptr<purezento::console> m_console;

		void initialize_console();
	private:		
		std::shared_ptr<runtime_sharing> m_runtime_sharing;
		
		runtime_startup m_startup;
		
		void* m_handle = nullptr;
	};
	
}
