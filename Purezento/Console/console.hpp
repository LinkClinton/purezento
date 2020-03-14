#pragma once

#include "../Runtime/runtime_sharing.hpp"
#include "../Interface/noncopyable.hpp"

#include "command_callback.hpp"
#include "console_text.hpp"

#include <vector>
#include <array>
#include <map>

namespace purezento {

	class console final : public noncopyable, public std::enable_shared_from_this<console> {
	public:
		explicit console(
			const std::shared_ptr<runtime_sharing>& sharing);

		~console() = default;

		void update(float delta);
	public:
		std::vector<console_text> texts;

		std::map<std::string, command_callback> callbacks;
	private:
		void execute_command(const std::string& command);
	private:
		std::shared_ptr<runtime_sharing> m_runtime_sharing;

		std::array<char, 2000> m_buffer;
		
		bool m_scroll_to_bottom = false;
	};
	
}
