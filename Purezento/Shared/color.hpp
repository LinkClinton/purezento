#pragma once

namespace purezento {

	struct color {
		float red = 0, green = 0, blue = 0, alpha = 1;

		color() = default;

		color(const float red, const float green, const float blue, const float alpha = 1) :
			red(red), green(green), blue(blue), alpha(alpha) {}
	};
	
}
