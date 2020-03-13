#include "draw_element.hpp"

auto purezento::draw_element::rectangle_fill(
	const purezento::rectangle& rectangle,
	const purezento::color& color) -> draw_element
{
	return draw_element::rectangle(rectangle, color, true);
}

auto purezento::draw_element::triangle_fill(
	const purezento::triangle& triangle,
	const purezento::color& color) -> draw_element
{
	return draw_element::triangle(triangle, color, true);
}

auto purezento::draw_element::circle_fill(
	const purezento::circle& circle,
	const purezento::color& color) -> draw_element
{
	return draw_element::circle(circle, color, true);
}

auto purezento::draw_element::draw_call(const purezento::draw_call& draw_call)
	-> draw_element
{
	draw_element element;

	element.type = draw_type::draw_call;
	element.draw_call_data = draw_call;

	return element;
}

auto purezento::draw_element::rectangle(
	const purezento::rectangle& rectangle, 
	const purezento::color& color,
	const bool filled) -> draw_element
{
	draw_element element;

	element.type = filled ? draw_type::rectangle_fill : draw_type::rectangle;
	element.rectangle_data = rectangle;
	element.color = color;

	return element;
}

auto purezento::draw_element::triangle(
	const purezento::triangle& triangle, 
	const purezento::color& color,
	const bool filled) -> draw_element
{
	draw_element element;

	element.type = filled ? draw_type::triangle_fill : draw_type::triangle;
	element.triangle_data = triangle;
	element.color = color;

	return element;
}

auto purezento::draw_element::circle(
	const purezento::circle& circle, 
	const purezento::color& color,
	const bool filled) -> draw_element
{
	draw_element element;

	element.type = filled ? draw_type::circle_fill : draw_type::circle;
	element.circle_data = circle;
	element.color = color;

	return element;
}

auto purezento::draw_element::line(
	const purezento::line& line,
	const purezento::color& color) -> draw_element
{
	draw_element element;

	element.type = draw_type::line;
	element.line_data = line;
	element.color = color;

	return element;
}
