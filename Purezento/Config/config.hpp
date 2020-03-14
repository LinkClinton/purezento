#pragma once

#include "../Runtime/runtime_sharing.hpp"
#include "../Interface/noncopyable.hpp"
#include "../Shared/vector.hpp"

#include "config_callback.hpp"

#include <map>

namespace purezento {

	struct window_info {
		vec2 size = vec2(1, 1);
		bool visible = true;

		window_info() = default;

		window_info(const vec2& size, const bool visible) : size(size), visible(visible) {}
	};

	struct render_info {
		float thickness = 1.0f;

		int circle_segments = 96;
		
		render_info() = default;
	};
	
	class config final : public noncopyable, public std::enable_shared_from_this<config> {
	public:
		explicit config(const std::shared_ptr<runtime_sharing>& sharing);

		~config() = default;

		auto console_window_info() const noexcept -> window_info { return m_console_window_info; }

		auto config_window_info() const noexcept -> window_info { return m_config_window_info; }

		auto render_info() const noexcept -> render_info { return m_render_info; }
		
		void update(float delta);
	public:
		std::map<std::string, config_callback> callbacks;
	private:
		friend class console;

		std::shared_ptr<runtime_sharing> m_runtime_sharing;

		window_info m_console_window_info;
		window_info m_config_window_info;

		purezento::render_info m_render_info;
	};

}
