#pragma once

#include "../Shared/vector.hpp"

#include <functional>
#include <array>

namespace purezento {

	enum class draw_type : unsigned {
		rectangle_fill,
		triangle_fill,
		circle_fill,
		draw_call,
		rectangle,
		triangle,
		circle,
		line,
		nops
	};

	using draw_call_function = std::function<void(void* ctx, float delta)>;

	struct draw_call {
		draw_call_function function;

		void* context = nullptr;

		draw_call() = default;

		draw_call(const draw_call_function& function, void* context) : function(function), context(context) {}
	};
	
	struct rectangle {
		float left = 0, top = 0, right = 1, bottom = 1;

		rectangle() = default;

		rectangle(const float left, const float top, const float right, const float bottom) :
			left(left), top(top), right(right), bottom(bottom) {}
	};

	struct triangle {
		std::array<vec2, 3> points = { vec2(0,0), vec2(0,1),vec2(1,0) };

		triangle() = default;

		triangle(const std::array<vec2, 3>& points) : points(points) {}

		triangle(const vec2& p0, const vec2& p1, const vec2& p2) : points({ p0, p1, p2 }) {}
	};
	
	struct circle {
		float radius = 1;
		vec2 center = vec2(0, 0);
		
		circle() = default;

		circle(const vec2& center, const float radius) : center(center), radius(radius) {}
	};

	struct line {
		std::array<vec2, 2> points = { vec2(0,0), vec2(1,1) };

		line() = default;

		line(const std::array<vec2, 2>& points) : points(points) {}
		
		line(const vec2& p0, const vec2& p1) : points({ p0, p1 }) {}
	};
}
