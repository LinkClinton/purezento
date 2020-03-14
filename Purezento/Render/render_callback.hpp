#pragma once

#include <functional>

namespace purezento {

	class render;
	
	using render_callback_function = std::function<
		void(
			const std::shared_ptr<purezento::render> & render,
			const std::shared_ptr<void> & ctx)>;

	struct render_callback {
		render_callback_function function;

		std::shared_ptr<void> context;

		render_callback() = default;

		render_callback(
			const render_callback_function& function,
			const std::shared_ptr<void>& context) :
			function(function), context(context) {}
	};
}
