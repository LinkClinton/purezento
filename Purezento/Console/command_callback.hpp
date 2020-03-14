#pragma once

#include <functional>
#include <vector>
#include <string>

namespace purezento {

	class console;
	
	using command_callback_function = std::function<
		void(
			const std::vector<std::string> & arguments,
			const std::shared_ptr<console>& console,
			const std::shared_ptr<void>& ctx)>;

	struct command_callback {
		command_callback_function function;

		std::shared_ptr<void> context;

		command_callback() = default;

		command_callback(
			const command_callback_function& function,
			const std::shared_ptr<void>& context) :
			function(function), context(context) {}
	};
}
