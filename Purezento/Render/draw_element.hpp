#pragma once

#include "../Shared/color.hpp"
#include "draw_type.hpp"

namespace purezento {

	struct draw_element {
		draw_type type = draw_type::nops;
		color color = purezento::color(0, 0, 0, 1);

		draw_call draw_call_data;
		rectangle rectangle_data;
		triangle triangle_data;
		polyline polyline_data;
		circle circle_data;
		line line_data;
		text text_data;

		draw_element() = default;

		static auto rectangle_fill(
			const purezento::rectangle& rectangle,
			const purezento::color& color = purezento::color::black()) -> draw_element;

		static auto triangle_fill(
			const purezento::triangle& triangle,
			const purezento::color& color = purezento::color::black()) -> draw_element;

		static auto circle_fill(
			const purezento::circle& circle,
			const purezento::color& color = purezento::color::black()) -> draw_element;

		static auto draw_call(
			const purezento::draw_call& draw_call) -> draw_element;

		static auto rectangle(
			const purezento::rectangle& rectangle,
			const purezento::color& color = purezento::color::black(),
			const bool filled = false) -> draw_element;

		static auto triangle(
			const purezento::triangle& triangle,
			const purezento::color& color = purezento::color::black(),
			const bool filled = false) -> draw_element;

		static auto polyline(
			const purezento::polyline& polyline,
			const purezento::color& color = purezento::color::black()) -> draw_element;
		
		static auto circle(
			const purezento::circle& circle,
			const purezento::color& color = purezento::color::black(),
			const bool filled = false) -> draw_element;

		static auto line(
			const purezento::line& line,
			const purezento::color& color = purezento::color::black()) -> draw_element;

		static auto text(
			const purezento::text& text,
			const purezento::color& color = purezento::color::black()) -> draw_element;
	};
	
}
