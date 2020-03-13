#pragma once

namespace purezento {

	template<typename T>
	struct vec2_t {
		T x = 0, y = 0;

		vec2_t() = default;

		vec2_t(const T& x, const T& y) : x(x), y(y) {}
	};

	using vec2 = vec2_t<float>;
}
