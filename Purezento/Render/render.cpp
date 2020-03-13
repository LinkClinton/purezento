#include "render.hpp"

#include "../Extensions/ImGui/imgui.hpp"

#include <Extensions/ImGui/ImGuiContext.hpp>
#include <CodeRed/Core/CodeRedGraphics.hpp>

purezento::render::render(
	const std::shared_ptr<runtime_sharing>& runtime_sharing,
	const std::shared_ptr<CodeRed::GpuRenderPass>& render_pass, 
	const size_t width, const size_t height, const purezento::font& font) :
	m_runtime_sharing(runtime_sharing), m_graphics_interface(runtime_sharing->graphics_interface()),
	m_render_pass(render_pass), m_width(width), m_height(height), m_font(font)
{
	ImGui::StyleColorsLight();

	ImGui::GetIO().Fonts->AddFontFromFileTTF(m_font.name.c_str(), static_cast<float>(m_font.size));

	m_command_list = m_graphics_interface->device()->createGraphicsCommandList(
		m_graphics_interface->allocator()
	);
	
	m_imgui_context = std::make_shared<CodeRed::ImGuiContext>(
		m_graphics_interface->device(),
		m_render_pass,
		m_graphics_interface->allocator(),
		m_graphics_interface->queue());
}

auto to_im_color(const purezento::color& color) -> ImColor {
	return ImColor(
		static_cast<int>(color.red * 255),
		static_cast<int>(color.green * 255),
		static_cast<int>(color.blue * 255),
		static_cast<int>(color.alpha * 255));
}

auto to_im_vec2(const purezento::vec2& point) -> ImVec2 {
	return ImVec2(point.x, point.y);
}

void purezento::render::update(float delta) const
{	
	auto draw_list = ImGui::GetBackgroundDrawList();
	
	for (const auto element : draw_elements) {
		switch (element.type) {
		case draw_type::rectangle_fill:
		{
			draw_list->AddRectFilled(
				ImVec2(element.rectangle_data.left, element.rectangle_data.top),
				ImVec2(element.rectangle_data.right, element.rectangle_data.bottom),
				to_im_color(element.color)
			);

			break;
		}

		case draw_type::triangle_fill:
		{
			draw_list->AddTriangleFilled(
				to_im_vec2(element.triangle_data.points[0]),
				to_im_vec2(element.triangle_data.points[1]),
				to_im_vec2(element.triangle_data.points[2]),
				to_im_color(element.color)
			);
				
			break;
		}

		case draw_type::circle_fill:
		{
			draw_list->AddCircleFilled(
				to_im_vec2(element.circle_data.center),
				element.circle_data.radius,
				to_im_color(element.color),
				96
			);
				
			break;
		}

		case draw_type::rectangle:
		{
			draw_list->AddRect(
				ImVec2(element.rectangle_data.left, element.rectangle_data.top),
				ImVec2(element.rectangle_data.right, element.rectangle_data.bottom),
				to_im_color(element.color)
			);

			break;
		}

		case draw_type::triangle:
		{
			draw_list->AddTriangle(
				to_im_vec2(element.triangle_data.points[0]),
				to_im_vec2(element.triangle_data.points[1]),
				to_im_vec2(element.triangle_data.points[2]),
				to_im_color(element.color)
			);
				
			break;
		}

		case draw_type::circle:
		{
			draw_list->AddCircle(
				to_im_vec2(element.circle_data.center),
				element.circle_data.radius,
				to_im_color(element.color),
				96
			);
				
			break;
		}

		case draw_type::line:
		{
			draw_list->AddLine(
				to_im_vec2(element.line_data.points[0]),
				to_im_vec2(element.line_data.points[1]),
				to_im_color(element.color)
			);
				
			break;
		}

		case draw_type::draw_call:
		{
			element.draw_call_data.function(element.draw_call_data.context, delta);

			break;
		}

		case draw_type::nops:
		default:
			break;
		}
	}
}

auto purezento::render::execute(
	const std::shared_ptr<CodeRed::GpuFrameBuffer>& frame_buffer, float delta) const
	-> std::shared_ptr<CodeRed::GpuGraphicsCommandList>
{
	m_command_list->beginRecording();
	m_command_list->beginRenderPass(m_render_pass, frame_buffer);

	m_imgui_context->draw(m_command_list, ImGui::GetDrawData());
	
	m_command_list->endRenderPass();
	m_command_list->endRecording();

	return m_command_list;
}
