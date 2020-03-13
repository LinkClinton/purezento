#pragma once

#include "../Shared/color.hpp"

#include <string>

namespace purezento {

	struct console_text {
		std::string text = "";
		color color = purezento::color(0, 0, 0, 1);

		console_text() = default;

		console_text(
			const std::string& text,
			const purezento::color& color) :
			text(text), color(color) {}
	};
	
}
