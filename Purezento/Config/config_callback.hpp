#pragma once

#include <functional>

namespace purezento {

	class config;
	
	using config_callback_function = std::function<
		void(
			const std::shared_ptr<config>&,
			const std::shared_ptr<void>& )>;
	
	struct config_callback {
		config_callback_function function;

		std::shared_ptr<void> context;

		config_callback() = default;

		config_callback(
			const config_callback_function& function,
			const std::shared_ptr<void>& context) :
			function(function), context(context) {}
	};
	
}
