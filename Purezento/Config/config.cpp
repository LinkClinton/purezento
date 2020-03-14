#include "config.hpp"

#include "../Extensions/ImGui/imgui.hpp"

purezento::config::config(const std::shared_ptr<runtime_sharing>& sharing) :
	m_runtime_sharing(sharing)
{
	m_console_window_info = window_info(
		vec2(
			m_runtime_sharing->width() * 0.8f,
			m_runtime_sharing->height() * 0.3f
		),
		true
	);

	m_config_window_info = window_info(
		vec2(
			m_runtime_sharing->width() * 0.2f,
			m_runtime_sharing->height() * 1.0f
		),
		true
	);
}

void purezento::config::update(float delta)
{
	static auto treeNodeFlags = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_Framed;

	// when we close the config window, we will render a small window to active the config window
	if (!m_config_window_info.visible) {

		ImGui::Begin("Config Small Window");
		ImGui::Checkbox("Visible", &m_config_window_info.visible);
		ImGui::End();
		
		return;
	}
	
	ImGui::Begin("Config", &m_config_window_info.visible,
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove);

	const auto width = m_config_window_info.size.x;
	const auto height = m_config_window_info.size.y;

	ImGui::SetWindowSize(ImVec2(width, height));
	ImGui::SetWindowPos(ImVec2(m_runtime_sharing->width() - width, 0));

	if (ImGui::TreeNodeEx("Console", treeNodeFlags)) {

		ImGui::SliderFloat("Height", &m_console_window_info.size.y,
			m_runtime_sharing->height() * 0.1f,
			m_runtime_sharing->height() * 0.8f);

		ImGui::Checkbox("Visible", &m_console_window_info.visible);
		
		ImGui::TreePop();
	}

	if (ImGui::TreeNodeEx("Config", treeNodeFlags)) {
		
		ImGui::Checkbox("Visible", &m_config_window_info.visible);
		
		ImGui::TreePop();
	}

	if (ImGui::TreeNodeEx("Render", treeNodeFlags)) {
		
		ImGui::SliderFloat("Thickness", &m_render_info.thickness, 1.f, 10.f);

		ImGui::InputInt("Segments", &m_render_info.circle_segments);
		
		ImGui::TreePop();
	}

	for (const auto& callback : callbacks) {
		if (ImGui::TreeNodeEx(callback.first.c_str(), treeNodeFlags)) {
			callback.second.function(shared_from_this(), callback.second.context);
			
			ImGui::TreePop();
		}
	}
	
	ImGui::End();
}
